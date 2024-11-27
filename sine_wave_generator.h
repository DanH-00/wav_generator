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
  double CalculateRampGain(int sample_number) const;
  void AppendSample(const int32_t& sample);

  std::shared_ptr<const Options> options_;
  const int number_of_samples_;
  std::vector<uint8_t> sine_wave_bytes_;
};
