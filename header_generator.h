#pragma once

#include <memory>
#include <vector>

#include "options.h"

class HeaderGenerator {
public:
  explicit HeaderGenerator(const std::shared_ptr<const Options>& options);
  [[nodiscard]] std::vector<uint8_t> GetHeader() const { return header_; }

private:
  void CreateHeader();
  void AppendString(const std::string& string);
  template <typename T>
  void AppendUnsigned(T value);

  [[nodiscard]] uint32_t CalculateChunkSize() const;
  [[nodiscard]] uint32_t CalculateDataSubChunkSize() const;
  [[nodiscard]] static uint32_t CalculateByteRate() ;
  [[nodiscard]] static uint16_t CalculateBlockAlign();

  std::shared_ptr<const Options> options_;
  std::vector<uint8_t> header_;
};
