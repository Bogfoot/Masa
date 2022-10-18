#include "pandas.h"
struct Masa {
  int dan;
  double masa;
};

auto RollingMedian(std::vector<Masa> array, std::vector<double> &result,
                   const int dani) -> std::vector<double>;

auto main(int argc, char *argv[]) -> int {
  std::vector<Masa> array;
  std::string file = "masa.csv";
  int lines = pandas::CountLines(file);
  pandas::FillDataFromFile(array, lines, file);
  std::cout << "Broj linija u \"" << file << "\"-u = " << lines << std::endl;
  std::vector<double> result;
  const int dani = 7;
  RollingMedian(array, result, dani);
  // Create an output stream
  std::ofstream out;
  // Give a name to the file
  std::string out_file = "rolling_median.csv";
  // Save data from result to output file stream
  pandas::SaveToFile(out, result, out_file);
  std::cout << "Podaci su usrednjeni po periodima od " << dani << " dana."
            << std::endl;
  pandas::ListResults(result);
}

auto RollingMedian(std::vector<Masa> array, std::vector<double> &result,
                   const int dani) -> std::vector<double> {
  double sum = 0.0;
  int array_size = array.size();
  for (int i = 0; i < array_size; i++) {
    if (i % dani == 0 && i != 0) {
      result.push_back(sum);
      sum = 0.0;
    }
    sum += array[i].masa / dani;
  }
  sum = 0.0;
  int devidor = array.size() / dani;
  int remainder = array.size() % dani;
  if (remainder != 0) {
    for (int i = 0; i < remainder; i++) {
      sum += array[devidor * dani + i].masa / (remainder);
    }
  }
  result.push_back(sum);
  return result;
}
