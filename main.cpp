#include <iostream>
#include <memory>
#include <vector>

#include "file_writer.h"
#include "options.h"

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

  const std::vector<uint8_t> test_bytes = { 0x00, 0x01, 0x02, 0x03, 0x04 };
  FileWriter file_writer(options->GetOutputFilepath());
  file_writer.Write(test_bytes);
  return 0;
}
