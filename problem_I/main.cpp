#include <iostream>
#include <vector>

int LCIS(std::vector<int>& first_seq, std::vector<int>& second_seq) {
  int first_length = static_cast<int>(first_seq.size());
  int second_length = static_cast<int>(second_seq.size());
  std::vector<std::vector<int>> dp(first_length + 1,
                                   std::vector<int>(second_length + 1, 0));
  for (int i = 1; i < first_length + 1; ++i) {
    int best = 0;
    for (int j = 1; j < second_length + 1; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (first_seq[i - 1] == second_seq[j - 1] && dp[i][j] < best + 1) {
        dp[i][j] = best + 1;
      }
      if (first_seq[i - 1] > second_seq[j - 1] && dp[i - 1][j] > best) {
        best = dp[i][j];
      }
    }
  }
  int result = 0;
  for (int i = 1; i < second_length + 1; ++i) {
    result = std::max(result, dp[first_length][i]);
  }
  return result;
}

int main() {
  int first_length = 0;
  int second_length = 0;
  std::cin >> first_length >> second_length;
  std::vector<int> first_seq(first_length);
  std::vector<int> second_seq(second_length);
  for (int i = 0; i < first_length; ++i) {
    std::cin >> first_seq[i];
  }
  for (int i = 0; i < second_length; ++i) {
    std::cin >> second_seq[i];
  }
  int result = LCIS(first_seq, second_seq);
  std::cout << result << '\n';
}