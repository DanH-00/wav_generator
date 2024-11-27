#include <iostream>
#include <memory>
#include <vector>

#include "file_writer.h"
#include "header_generator.h"
#include "options.h"

void AppendVector(std::vector<uint8_t>& dest, const std::vector<uint8_t>& src) {
  dest.insert(dest.end(), src.begin(), src.end());
}

int main(int argc, char* argv[]) {
  std::shared_ptr<const Options>options;

  try {
    options = std::make_shared<Options>(argc, argv);
  } catch (const std::exception& error) {
    std::cerr << "Error parsing options: " << error.what() << std::endl;
    return -1;
  }

  std::cout << "Writing a " << options->GetLengthS() << " second WAV file with a sine wave of frequency "
            << options->GetFrequencyHz() << " Hz to \"" << options->GetOutputFilepath() << "\""  << std::endl;

  std::vector<uint8_t> output_bytes;

  const HeaderGenerator header_generator(options);
  AppendVector(output_bytes, header_generator.GetHeader());


  FileWriter file_writer(options->GetOutputFilepath());
  file_writer.Write(output_bytes);
  return 0;
}
