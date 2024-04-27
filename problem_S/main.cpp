#include <iostream>
#include <string>
#include <vector>

const int64_t kMod = 1e18;

void DividedByTwo(std::string& number) {
  int length = static_cast<int>(number.size());
  std::string ans;
  int ones = 0;
  for (int i = 0; i < length; ++i) {
    if (i == 0 && number[i] == '1') {
      ones = 5;
      continue;
    }
    if ((number[i] - '0') % 2 == 0) {
      ans += (number[i] - '0') / 2 + ones + '0';
      ones = 0;
    } else {
      ans += (number[i] - '0') / 2 + ones + '0';
      ones = 5;
    }
  }
  number = ans;
}

void MinusOne(std::string& number) { number[number.size() - 1] -= 1; }

bool IsDividedByTwo(const std::string& number) {
  return (number[number.size() - 1] - '0') % 2 == 0;
}

std::vector<std::vector<int64_t>> Multiply(
    const std::vector<std::vector<int64_t>>& matrix,
    const std::vector<std::vector<int64_t>>& another) {
  int64_t size = static_cast<int64_t>(matrix.size());
  std::vector<std::vector<int64_t>> ans(size, std::vector<int64_t>(size));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        ans[i][j] = (ans[i][j] + (matrix[i][k] * another[k][j]) % kMod) % kMod;
      }
    }
  }
  return ans;
}

std::vector<std::vector<int64_t>> Exponentiation(
    std::vector<std::vector<int64_t>> matrix, std::string& degree) {
  if (degree == "1") {
    return matrix;
  }
  if (IsDividedByTwo(degree)) {
    DividedByTwo(degree);
    std::vector<std::vector<int64_t>> mult = Exponentiation(matrix, degree);
    matrix = Multiply(mult, mult);
  } else {
    MinusOne(degree);
    matrix = Multiply(Exponentiation(matrix, degree), matrix);
  }
  return matrix;
}

bool Bit(int64_t number, int64_t idx) {
  return ((1 << idx) & static_cast<int>(number)) != 0;
}

int main() {
  int number = 0;
  std::cin >> number;
  int number_m = 0;
  std::cin >> number_m;
  if (number_m > number) {
    std::swap(number, number_m);
  }
  std::string number_n = std::to_string(number);
  MinusOne(number_n);
  int64_t size = 1 << number_m;
  std::vector<std::vector<int64_t>> graph(size, std::vector<int64_t>(size));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      bool mark = true;
      for (int k = 0; k < number_m - 1; ++k) {
        if ((Bit(i, k) == Bit(j, k)) && (Bit(i, k + 1) == Bit(j, k + 1)) &&
            (Bit(i, k) == Bit(i, k + 1))) {
          mark = false;
          break;
        }
      }
      if (mark) {
        graph[i][j] = 1;
      } else {
        graph[i][j] = 0;
      }
    }
  }
  int64_t result = 0;
  // std::cin >> kMod;
  if (number_n == "0") {
    std::cout << (1 << number_m) % kMod << '\n';
    return 0;
  }
  graph = Exponentiation(graph, number_n);
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      result = (result + graph[i][j]) % kMod;
    }
  }
  std::cout << result << '\n';
  return 0;
}
