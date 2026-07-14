// SPDX-License-Identifier: GPL-3.0-only
#include "bounce/scenario/calibration_loader.hpp"

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

namespace {

constexpr const char* kManifestPath = BOUNCE_SOURCE_DIR "/data/scenarios/heldout/MANIFEST.json";

bool load_manifest_ids(std::vector<std::string>& ids) {
  std::ifstream in(kManifestPath);
  if (!in) {
    return false;
  }
  std::string json((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  std::size_t pos = 0;
  while ((pos = json.find("\"scenario_id\"", pos)) != std::string::npos) {
    pos = json.find(':', pos);
    if (pos == std::string::npos) {
      break;
    }
    ++pos;
    while (pos < json.size() && json[pos] != '"') {
      ++pos;
    }
    if (pos >= json.size()) {
      break;
    }
    ++pos;
    const std::size_t start = pos;
    while (pos < json.size() && json[pos] != '"') {
      ++pos;
    }
    ids.emplace_back(json.substr(start, pos - start));
  }
  return !ids.empty();
}

} // namespace

int main() {
  std::vector<std::string> ids;
  if (!load_manifest_ids(ids)) {
    std::fprintf(stderr, "survey-heldout-load-FAILED: manifest\n");
    return 1;
  }
  int load_ok = 0;
  for (const std::string& id : ids) {
    const std::string path =
        std::string(BOUNCE_SOURCE_DIR) + "/data/scenarios/heldout/" + id + ".json";
    bounce::core::scenario::CalibrationScenario scenario{};
    const bool ok = bounce::core::scenario::load_calibration_scenario(path.c_str(), scenario);
    std::printf("%s,%s\n", id.c_str(), ok ? "True" : "False");
    if (ok) {
      ++load_ok;
    }
  }
  std::printf("load_ok %d / %zu\n", load_ok, ids.size());
  return load_ok == static_cast<int>(ids.size()) ? 0 : 1;
}
