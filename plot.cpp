#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  // Check if the user provided the name of a CSV file
  if (argc != 2) {
    std::cerr << "Error: missing file name\n";
    return 1;
  }

  // Open the CSV file
  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Error: unable to open file\n";
    return 1;
  }

  // Read the data from the CSV file into a 2D vector
  std::vector<std::vector<double>> data;
  std::string line;
  while (std::getline(file, line)) {
    std::cout << line << std::endl;
    std::vector<double> row;
    std::stringstream ss(line);
    std::string cell;
    while (std::getline(ss, cell, ',')) {
      row.push_back(std::stod(cell));
    }
    data.push_back(row);
  }

  for (auto item : data) {
    for (auto it : item) {
      std::cout << it;
    }
    std::cout << std::endl;
  }
  // Close the file
  file.close();

  // Find the minimum and maximum values in the data
  double min_value = data[0][0];
  double max_value = data[0][0];
  for (const auto &row : data) {
    for (const auto &value : row) {
      min_value = std::min(min_value, value);
      max_value = std::max(max_value, value);
    }
  }

  // Calculate the number of rows and columns needed for the plot
  int num_rows = 30;
  int num_cols = 100;
  double row_height = (max_value - min_value) / num_rows;
  double col_width = data[0].size() / num_cols;

  // Create the plot using ASCII art
  std::vector<std::string> plot(num_rows, std::string(num_cols, ' '));
  for (int i = 0; i < num_rows; ++i) {
    plot[i][0] = '|';
  }
  for (int i = 0; i < num_cols; ++i) {
    plot[num_rows - 1][i] = '-';
  }
  plot[num_rows - 1][0] = '+';
  for (const auto &row : data) {
    for (int i = 0; i < row.size(); ++i) {
      int row_index = (row[i] - min_value) / row_height;
      int col_index = i / col_width;
      plot[num_rows - 1 - row_index][col_index] = '*';
    }
  }

  // Print the plot to the console
  for (const auto &row : plot) {
    std::cout << row << '\n';
  }

  return 0;
}
