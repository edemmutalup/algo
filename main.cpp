#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

const int kPosInf = 2'147'483'647;

int LIS(const std::vector<int>& seq, std::stack<int>& dest, int number) {
  std::vector<int> dp(number, kPosInf);
  std::vector<std::pair<int, int>> cache;
  for (int i = 0; i < number; ++i) {
    int pos = std::upper_bound(dp.begin(), dp.end(), seq[i]) - dp.begin();
    if (pos <= number) {
      dp[pos] = seq[i];
      cache.push_back({i, pos});
    }
  }
  int length = static_cast<int>(cache.size());
  int counter = std::lower_bound(dp.begin(), dp.end(), kPosInf) - dp.begin();
  int result = counter;
  for (int i = length - 1; i >= 0 && counter >= 0; --i) {
    if (cache[i].second + 1 == counter) {
      dest.push(cache[i].first);
      --counter;
    }
  }
  return result;
}

int main() {
  int number = 0;
  std::cin >> number;
  std::vector<int> seq(number);
  for (int i = 0; i < number; ++i) {
    int x = 0;
    std::cin >> x;
    seq[i] = (-1) * x;
  }
  std::stack<int> dest;
  int result = LIS(seq, dest, number);
  std::cout << result << '\n';
  for (int i = 0; i < result; ++i) {
    std::cout << dest.top() + 1 << ' ';
    dest.pop();
  }
  std::cout << '\n';
}