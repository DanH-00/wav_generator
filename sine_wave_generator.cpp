#include "sine_wave_generator.h"

#include <cmath>

#include "wav_generator_defines.h"

constexpr double kPi = 3.14159265358979323846;
constexpr double kMaxGain = 0.75;
constexpr int kNumberOfRampSamples = kSampleRateHz / 100;

SineWaveGenerator::SineWaveGenerator(const std::shared_ptr<const Options>& options)
  : options_(options)
  , number_of_samples_(static_cast<int>(kSampleRateHz) * options_->GetLengthS()) {
  GenerateSineWave();
}

void SineWaveGenerator::GenerateSineWave() {
  constexpr int32_t max_amplitude = (1 << 23) - 1;
  const double angular_frequency = 2.0 * kPi * options_->GetFrequencyHz();


  for (int i = 0; i < number_of_samples_; ++i) {
    const double time = static_cast<double>(i) / kSampleRateHz;
    const double value = std::sin(angular_frequency * time) * CalculateRampGain(i);
    const int32_t sample = static_cast<int32_t>(value * max_amplitude);

    AppendSample(sample);
  }
}

double SineWaveGenerator::CalculateRampGain(const int sample_number) const {
  if (sample_number < kNumberOfRampSamples) {
    return static_cast<double>(sample_number) / kNumberOfRampSamples * kMaxGain;
  }

  if (sample_number >= number_of_samples_ - kNumberOfRampSamples) {
    return static_cast<double>(number_of_samples_ - sample_number) / kNumberOfRampSamples * kMaxGain;
  }

  return kMaxGain;
}

void SineWaveGenerator::AppendSample(const int32_t& sample) {
  sine_wave_bytes_.push_back(sample & 0xFF);
  sine_wave_bytes_.push_back((sample >> 8) & 0xFF);
  sine_wave_bytes_.push_back((sample >> 16) & 0xFF);
}

