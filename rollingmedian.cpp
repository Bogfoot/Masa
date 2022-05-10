#include <fstream>
#include <iostream>
#include <sstream>
/* #include <math.h> */
#include <vector>
struct Masa {
  int dan;
  double masa;
};
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
auto FillDataFromFile(std::vector<Masa> &podaci, const int LineCount,
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

auto RollingMedian(std::vector<Masa> array, std::vector<double> &result)
    -> std::vector<double> {
  double sum = 0.0;
  for (int i = 0; i < array.size(); i++) {
    if (i % 5 == 0 && i != 0) {
      result.push_back(sum);
      sum = 0.0;
    }
    sum += array[i].masa / 5;
  }

  sum = 0.0;
  int devidor = array.size() / 5;
  int remainder = array.size() % 5;
  if (remainder != 0) {
    for (int i = 0; i < remainder; i++) {
      sum += array[devidor * 5 + i].masa / (remainder);
      result.push_back(sum);
    }
  }
  return result;
}

auto SaveToFile(std::ofstream &out, std::vector<double> results,
                std::string out_file) -> void {
  out.open(out_file, std::ios::out);
  for (auto i : results) {
    out << i << std::endl;
  }
  out.close();
}

auto ListResults(std::vector<double> results) -> void {
  for (auto i : results) {
    std::cout << i << std::endl;
  }
}
auto main() -> int {
  std::vector<Masa> array;
  std::string file = "masa.csv";

  int lines = CountLines(file);

  FillDataFromFile(array, lines, file);

  std::cout << "Broj linija u \"" << file << "\"-u = " << lines << std::endl;

  std::vector<double> result;

  RollingMedian(array, result);

  // Create an output stream
  std::ofstream out;
  // Give a name to the file
  std::string out_file = "rolling_median.csv";
  // Save data from result to output file stream
  SaveToFile(out, result, out_file);
  ListResults(result);
}
