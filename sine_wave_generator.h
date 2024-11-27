#pragma once

#include <memory>
#include <vector>

#include "options.h"

class SineWaveGenerator  {
public:
  explicit SineWaveGenerator(const std::shared_ptr<const Options>& options);
  [[nodiscard]] std::vector<uint8_t> GetSineWave() const { return sine_wave_bytes_; }

private:
  void GenerateSineWave();
  void AppendSample(const int32_t& sample);

  std::vector<uint8_t> sine_wave_bytes_;
  std::shared_ptr<const Options> options_;
};
