#include <iostream>
#include <vector>

int ZigZag(const std::vector<int>& seq, std::vector<int>& dest) {
  int number = static_cast<int>(seq.size());
  std::vector<std::pair<int, int>> dp(number, {1, 1});
  std::vector<std::pair<int, int>> pos(number, {0, 0});
  dp[0] = {1, 1};
  int max_up = 0;
  int max_down = 0;
  for (int i = 1; i < number; ++i) {
    for (int j = 0; j < i; ++j) {
      if (seq[j] < seq[i] && dp[j].second + 1 > dp[i].first) {
        dp[i].first = dp[j].second + 1;
        pos[i].first = j;
        continue;
      }
      if (seq[j] > seq[i] && dp[j].first + 1 > dp[i].second) {
        dp[i].second = dp[j].first + 1;
        pos[i].second = j;
        continue;
      }
    }
    if (dp[max_up].first < dp[i].first) {
      max_up = i;
    }
    if (dp[max_down].second < dp[i].second) {
      max_down = i;
    }
  }
  bool mark = dp[max_up].first > dp[max_down].second;
  int result = mark ? dp[max_up].first : dp[max_down].second;
  int idx = mark ? max_up : max_down;
  for (int i = 0; i < result; ++i) {
    if (mark) {
      mark = false;
      dest.push_back(seq[idx]);
      idx = pos[idx].first;
    } else {
      mark = true;
      dest.push_back(seq[idx]);
      idx = pos[idx].second;
    }
  }
  return result;
}

int main() {
  int number = 0;
  std::cin >> number;
  std::vector<int> seq(number, 0);
  std::vector<int> dest;
  for (int i = 0; i < number; ++i) {
    std::cin >> seq[i];
  }
  int result = ZigZag(seq, dest);
  std::cout << result << '\n';
  for (int i = result - 1; i >= 0; --i) {
    std::cout << dest[i] << ' ';
  }
  std::cout << '\n';
}