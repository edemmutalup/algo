#include <iostream>
#include <vector>

int64_t PeacefulSet(int number) {
  std::vector<std::vector<int64_t>> dp(number + 1,
                                       std::vector<int64_t>(number + 1, 0));
  dp[0][0] = 1;
  dp[1][1] = 1;
  for (int i = 1; i < number + 1; ++i) {
    for (int j = 1; j < number + 1; ++j) {
      dp[i][j] = dp[i - 1][j - 1];
      if (i > j && j % 2 == 0) {
        dp[i][j] += dp[i - j][j / 2];
      } else if (i < j) {
        dp[i][j] = 0;
      }
    }
  }
  int64_t result = 0;
  for (int i = 1; i < number + 1; ++i) {
    result += dp[number][i];
  }
  return result;
}

int main() {
  int number = 0;
  std::cin >> number;
  std::cout << PeacefulSet(number) << '\n';
}