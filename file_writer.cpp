#include "file_writer.h"

#include <iostream>

FileWriter::FileWriter(const std::string &filepath)
  : filepath_(filepath) {
  DeleteFileIfExists();
  OpenFile();
}

FileWriter::~FileWriter() {
  CloseFile();
}

void FileWriter::DeleteFileIfExists() const {
  if (std::filesystem::exists(filepath_)) {
    std::filesystem::remove(filepath_);
  }
}

void FileWriter::OpenFile() {
  output_file_.open(filepath_, std::ios::binary);

  if (!output_file_.is_open()) {
    throw std::runtime_error("Failed to open file: " + filepath_);
  }
}

void FileWriter::CloseFile() {
  output_file_.close();

  if (output_file_.good()) {
    std::cout << "File written successfully to " << filepath_ << std::endl;
  } else {
    std::cerr << "ERROR: An error occurred while writing to file." << std::endl;
  }
}

void FileWriter::Write(const std::vector<uint8_t> &byte_array) {
  if (byte_array.size() > std::numeric_limits<std::streamsize>::max()) {
    throw std::runtime_error("Byte array is too large to write to file.");
  }

  output_file_.write(reinterpret_cast<const char*>(byte_array.data()), static_cast<std::streamsize>(byte_array.size()));
}
