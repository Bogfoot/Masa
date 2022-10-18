#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace pandas {
// Save data from a vector to a file.
auto SaveToFile(std::ofstream &out, std::vector<double> results,
                std::string out_file) -> void {
  out.open(out_file, std::ios::out);
  for (auto i : results) {
    out << i << std::endl;
  }
  out.close();
}

// List results in a nice way
auto ListResults(std::vector<double> results) -> void {
  int j = 0;
  for (auto i : results) {
    std::cout << std::setw(3) << j + 1 << "-ti tjedan," << std::setw(10) << i
              << std::setprecision(6) << std::endl;
    j++;
  }
}

// Cita broj linija u fileu "filename"
auto CountLines(const std::string filename) -> int {
  std::ifstream fs{filename};
  if (!fs.is_open()) {
    std::cerr << "Error, file could not be opened" << std::endl;
    return 0;
  }

  int count = 0;
  std::string line;
  while (std::getline(fs, line)) {
    ++count;
  }
  fs.close();
  return count;
}

// Cita podatke iz filea "filename" i spremi ih u vektor Masa
template <class T>
auto FillDataFromFile(std::vector<T> &podaci, const int LineCount,
                      const std::string filename) -> void {
  std::ifstream fs(filename);
  podaci.resize(LineCount - 1);
  std::string line;
  std::getline(fs, line); // procita 1. red i nastavi

  int count = 0; // Treba pratiti broj podataka za podaci[count].masa
  if (fs.good()) {
    int dan; // dan
    double masa;
    char comma;

    // Cita liniju po liniju dok ne dode do kraja filea \^]
    while (std::getline(fs, line)) {
      std::stringstream ss(line);
      ss >> dan >> comma >> masa;
      // comma je ',' jer njega trebamo ignorirati
      podaci[count].dan = dan;
      podaci[count].masa = masa;
      count++;
    }
  }
}
}; // namespace pandas
