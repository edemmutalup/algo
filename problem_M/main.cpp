#include <iostream>
#include <vector>

const int64_t kMagicNumber = 1e9 + 9;

int64_t GetMod(int64_t number) {
  number = number % kMagicNumber;
  if (number < 0) {
    number += kMagicNumber;
  }
  return number;
}

void Multiply(const std::vector<std::vector<int64_t>>& first,
              const std::vector<std::vector<int64_t>>& second,
              std::vector<std::vector<int64_t>>& out) {
  std::vector<std::vector<int64_t>> matrix_first = first;
  std::vector<std::vector<int64_t>> matrix_second = second;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      out[i][j] = 0;
    }
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      for (int k = 0; k < 2; ++k) {
        out[i][j] = GetMod(out[i][j] +
                           GetMod(matrix_first[i][k] * matrix_second[k][j]));
      }
    }
  }
}

void MatrixExponentiation(const std::vector<std::vector<int64_t>>& matrix,
                          int64_t degree,
                          std::vector<std::vector<int64_t>>& out) {
  if (degree == 1) {
    return;
  }
  if (degree % 2 == 0) {
    MatrixExponentiation(matrix, degree / 2, out);
    Multiply(out, out, out);
  }
  if (degree % 2 == 1) {
    MatrixExponentiation(matrix, degree - 1, out);
    Multiply(matrix, out, out);
  }
}

int main() {
  std::vector<std::vector<int64_t>> matrix = {{1, 1}, {1, 0}};
  std::vector<std::vector<int64_t>> out = {{1, 1}, {1, 0}};
  int64_t number_n = 0;
  int64_t number_q = 0;
  std::cin >> number_n >> number_q;
  std::vector<std::vector<int64_t>> terminals(number_n,
                                              std::vector<int64_t>(3));
  std::vector<int64_t> diags(number_q);
  for (int i = 0; i < number_n; ++i) {
    std::cin >> terminals[i][0] >> terminals[i][1] >> terminals[i][2];
    terminals[i][2] = GetMod(terminals[i][2]);
  }
  for (int i = 0; i < number_q; ++i) {
    std::cin >> diags[i];
  }
  for (int i = 0; i < number_q; ++i) {
    int64_t result = 0;
    for (int j = 0; j < number_n; ++j) {
      int64_t deg = terminals[j][1] - terminals[j][0] - diags[i];
      if (deg < 0) {
        continue;
      }
      if (deg == 0) {
        result = GetMod(result + terminals[j][2]);
        out = {{1, 1}, {1, 0}};
        continue;
      }
      MatrixExponentiation(matrix, deg, out);
      result = GetMod(result + GetMod(terminals[j][2] * out[0][0]));
      out = {{1, 1}, {1, 0}};
    }
    std::cout << result << '\n';
  }
  return 0;
}
