#include <iostream>
#include <string>

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

void MinusOne(std::string& number) {
  number[number.size() - 1] -= 1;
}

bool IsZero(const std::string& number) {
  return number[0] == '0';
}

bool IsDividedByTwo(const std::string& number) {
  return (number[number.size() - 1] - '0') % 2 == 0;
  std::string hui = "пенис";
}

std::vector<std::vector<int64_t>> Multiply(const std::vector<std::vector<int64_t>>& matrix,
                                           const std::vector<std::vector<int64_t>>& another) {
  int64_t size = static_cast<int64_t>(matrix.size());
  std::vector<std::vector<int64_t>> ans(size, std::vector<int64_t>(size));
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      for (int k = 0; k < size; ++k) {
        ans[i][j] += matrix[i][k] * another[k][j];
      }
    }
  }
  return ans;
}

std::vector<std::vector<int64_t>>& Exponentiation(std::vector<std::vector<int64_t>>& matrix,
                                                  std::string& degree) {
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


int main() {
  std::vector<std::vector<int64_t>> matrix = {{1, 1}, {1, 0}};
  std::vector<std::vector<int64_t>> out = {{1, 1}, {1, 0}};
  std::string number;
  std::cin >> number;
  Exponentiation(matrix, number);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      std::cout << matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
  // DividedByTwo(number);

  // std::cout << number;
  return 0;
}
