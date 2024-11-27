#include <iostream>
#include <memory>

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
  return 0;
}
