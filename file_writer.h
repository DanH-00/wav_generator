#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class FileWriter {
public:
  explicit FileWriter(const std::string& filepath);
  ~FileWriter();
  void Write(const std::vector<uint8_t>& byte_array);

private:
  void DeleteFileIfExists() const;
  void OpenFile();
  void CloseFile();

  const std::string filepath_;
  std::ofstream output_file_;
};
