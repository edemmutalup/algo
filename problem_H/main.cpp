#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int LCS(const std::string& seq_first, const std::string& seq_second,
        std::vector<std::pair<int, int>>& out) {
  int first_length = static_cast<int>(seq_first.size());
  int second_length = static_cast<int>(seq_second.size());
  std::vector<std::vector<int>> dp(first_length + 1,
                                   std::vector<int>(second_length + 1, 0));
  for (int i = 1; i < first_length + 1; ++i) {
    for (int j = 1; j < second_length + 1; ++j) {
      dp[i][j] = seq_first[i - 1] == seq_second[j - 1] ? dp[i - 1][j - 1] + 1
                                                       : dp[i][j];
      dp[i][j] = std::max(std::max(dp[i - 1][j], dp[i][j - 1]), dp[i][j]);
    }
  }
  for (int i = first_length, j = second_length; i != 0 || j != 0;) {
    if (i >= 1 && dp[i][j] == dp[i - 1][j]) {
      --i;
      continue;
    }
    if ((j >= 1 && i >= 1) && seq_first[i - 1] == seq_second[j - 1] &&
        dp[i][j] == dp[i - 1][j - 1] + 1) {
      out.push_back({i--, j--});
      continue;
    }
    if (j >= 1 && dp[i][j] == dp[i][j - 1]) {
      --j;
    }
  }
  return dp[first_length][second_length];
}

bool Comp(std::pair<int, int> first_elem, std::pair<int, int> second_elem) {
  return first_elem.second < second_elem.second;
}

int main() {
  std::string seq_first;
  std::string seq_second;
  std::cin >> seq_first >> seq_second;
  std::vector<std::pair<int, int>> out;
  int result = LCS(seq_first, seq_second, out);
  std::cout << result << '\n';
  std::sort(out.begin(), out.end());
  for (int i = 0; i < result; ++i) {
    std::cout << out[i].first << ' ';
  }
  std::cout << '\n';
  std::sort(out.begin(), out.end(), Comp);
  for (int i = 0; i < result; ++i) {
    std::cout << out[i].second << ' ';
  }
  std::cout << '\n';
}