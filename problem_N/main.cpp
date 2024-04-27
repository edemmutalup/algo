#include <iostream>
#include <vector>

const int kMod = 1e9 + 7;

bool Bit(int number, int64_t idx) { return ((1 << idx) & number) != 0; }

bool Checker(int mask, std::vector<std::vector<int>>& field, int number_n,
             int number_m) {
  for (int i = 0; i < number_n; ++i) {
    if (field[number_n - 1 - i][number_m] != -1 &&
        field[number_n - 1 - i][number_m] != static_cast<int>(Bit(mask, i))) {
      return false;
    }
  }
  return true;
}

bool CheckDig(int mask, int number_n) {
  for (int i = 1; i < number_n; ++i) {
    if (Bit(mask, i) == Bit(mask, i - 1)) {
      return false;
    }
  }
  return true;
}

int Answer(std::vector<std::vector<int>>& field, int number_n, int number_m) {
  std::vector<std::vector<int>> dp((1 << number_n), std::vector<int>(number_m));
  for (int i = 0; i < (1 << number_n); ++i) {
    if (Checker(i, field, number_n, 0)) {
      dp[i][0] = 1;
    }
  }
  for (int j = 1; j < number_m; ++j) {
    for (int i = 0; i < (1 << number_n); ++i) {
      if (Checker(i, field, number_n, j)) {
        dp[i][j] = (dp[i][j] + dp[(1 << number_n) - 1 - i][j - 1]) % kMod;
        if (CheckDig(i, number_n)) {
          dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % kMod;
        }
      } else {
        dp[i][j] = 0;
      }
    }
  }
  int result = 0;
  for (int i = 0; i < (1 << number_n); ++i) {
    result = (result + dp[i][number_m - 1]) % kMod;
  }
  return result;
}

int main() {
  int number_n = 0;
  int number_m = 0;
  std::cin >> number_n >> number_m;
  std::vector<std::vector<int>> field(number_n, std::vector<int>(number_m));
  char pos;
  for (int i = 0; i < number_n; ++i) {
    for (int j = 0; j < number_m; ++j) {
      std::cin >> pos;
      if (pos == '+') {
        field[i][j] = 1;
      } else if (pos == '-') {
        field[i][j] = 0;
      } else {
        field[i][j] = -1;
      }
    }
  }
  std::cout << Answer(field, number_n, number_m) << '\n';
  return 0;
}
