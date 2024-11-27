#include "header_generator.h"


constexpr uint32_t kChunkDescriptorSize = 12;
constexpr uint32_t kFormatSubChunkHeaderSize = 8;
constexpr uint32_t kFormatSubChunkSize = 16;
constexpr uint32_t kDataSubChunkHeaderSize = 8;

constexpr uint32_t kSampleRateHz = 48000;
constexpr uint16_t kNumChannels = 1;
constexpr uint16_t kBitsPerSample = 24;

constexpr uint16_t kPcmFormat = 1;

HeaderGenerator::HeaderGenerator(const std::shared_ptr<const Options>& options)
  : options_(options) {
  CreateHeader();
}

void HeaderGenerator::CreateHeader() {
  AppendString("RIFF");
  AppendUnsigned(CalculateChunkSize());
  AppendString("WAVE");
  AppendString("fmt ");
  AppendUnsigned(kFormatSubChunkSize);
  AppendUnsigned(kPcmFormat);
  AppendUnsigned(kNumChannels);
  AppendUnsigned(kSampleRateHz);
  AppendUnsigned(CalculateByteRate());
  AppendUnsigned(CalculateBlockAlign());
  AppendUnsigned(kBitsPerSample);

  AppendString("data");
  AppendUnsigned(CalculateDataSubChunkSize());
}

void HeaderGenerator::AppendString(const std::string& string) {
  for (const char& c : string) {
    header_.push_back(c);
  }
}

template<typename T>
void HeaderGenerator::AppendUnsigned(const T value) {
  static_assert(std::is_unsigned_v<T>, "T must be an unsigned integer type");

  for (int i = sizeof(T) - 1; i >= 0; i--) {
    uint8_t byte = (value >> (8 * i)) & 0xFF;
    header_.push_back(byte);
  }
}

uint32_t HeaderGenerator::CalculateChunkSize() const {
  const uint32_t chunk_size = kChunkDescriptorSize +
                              kFormatSubChunkHeaderSize +
                              kFormatSubChunkSize +
                              kDataSubChunkHeaderSize +
                              CalculateDataSubChunkSize();
  return chunk_size;
}

uint32_t HeaderGenerator::CalculateDataSubChunkSize() const {
  return options_->GetLengthS() * CalculateByteRate();
}

uint32_t HeaderGenerator::CalculateByteRate() {
  return kSampleRateHz * CalculateBlockAlign();
}

uint16_t HeaderGenerator::CalculateBlockAlign() {
  return kNumChannels * (kBitsPerSample / 8);
}
