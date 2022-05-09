#include <fstream>
#include <iostream>
#include <sstream>
/* #include <math.h> */
#include <vector>
struct Masa {
  int dan;
  double masa;
};
auto CountLines(std::string filename) -> int {
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

auto FillDataFromFile(std::vector<Masa> &podaci, int LineCount,
                      std::string filename) -> void {
  std::ifstream fs(filename);
  podaci.resize(LineCount);
  std::string line;
  std::getline(fs, line);

  int count = 0;
  if (fs.good()) {
    // Push items into a vector
    int movement;
    double step;

    while (std::getline(fs, line)) {
      std::stringstream ss(line);
      ss >> movement >> step;
      podaci[count].dan = movement;
      podaci[count].masa = step;
      count++;
    }
  }
}

auto rolling_median(std::vector<Masa> array, std::vector<double> &result)
    -> std::vector<double> {
  double sum = 0.0;
  int devidor = array.size() / 5;
  for (int i = 0; i < array.size(); i++) {
    sum += array[i].masa / 5;
    if (i % 5 == 0) {
      sum = sum;
      result.push_back(sum);
      sum = 0.0;
    }
  }
  if (array.size() % 5 != 0) {
    for (int i = 0; i < array.size() % 5; i++) {
      sum += array[devidor * 5 + i].masa / array.size();
    }
  }
  return result;
}
auto Read_from_CSV(std::istream &_infile) -> void;

auto main() -> int {
  /* std::vector<double> array{ */
  /*     115.4, 114.1, 113.6, 112.3, 112.0, 111.8, 111.6, 111.7, 111.5, 111.4,
   */
  /*     111.4, 111.4, 111.5, 112.1, 111.8, 111.2, 111.1, 110.7, 110.3, 109.8,
   */
  /*     109.1, 108.5, 109.1, 108.4, 108.2, 108.2, 107.7, 107.7, 107.5, 107.8,
   */
  /*     107.7, 106.1, 106.7, 107.0, 107.0, 106.6, 107.7, 106.9, 106.3, 106.3,
   */
  /*     106.3, 105.3, 105.4, 105.1, 104.8, 104.5, 104.6, 105.3, 105.5, 105.5,
   */
  /*     105.0, 105.0, 105.4, 104.8, 104.6, 104.5, 104.4, 104.3, 104.3, 104.2,
   */
  /*     104.0, 103.8, 103.5, 103.9, 103.0, 104.0, 103.5, 103.0, 102.8, 102.2,
   */
  /*     102.0, 102.9, 102.6, 102.4, 102.1, 101.8, 101.5, 101.3, 101.2, 101.2,
   */
  /*     100.2, 100.5, 100.7, 101.1, 100.8, 100.6, 100.5, 100.2, 99.8,  99.6, */
  /*     99.8, */
  /* }, */
  /* result; */
  std::vector<Masa> array;
  std::string file = "masa.csv";

  int lines = CountLines(file);
  FillDataFromFile(array, lines, file);
  std::vector<double> result;
  rolling_median(array, result);
  for (auto i : result) {
    std::cout << i << std::endl;
  }
  std::cout << "Broj točaka: " << result.size() << std::endl;
}
