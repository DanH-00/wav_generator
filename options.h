#pragma once

#include <string>

class Options {
public:
  Options(int argc, char** argv);
  [[nodiscard]] std::string GetOutputFilepath() const { return output_filepath_; }
  [[nodiscard]] double GetFrequencyHz() const { return frequency_hz_; }
  [[nodiscard]] int GetLengthS() const { return length_s_; }

private:
  void ParseOptions(int argc, char** argv);

  std::string output_filepath_;
  double frequency_hz_ = 0;
  int length_s_ = 0;
};
