#include <iostream>
#include <map>
#include <vector>

const int kMagicNumber = 1e9 + 7;

int GetMod(int number) {
  number = number % kMagicNumber;
  if (number < 0) {
    number += kMagicNumber;
  }
  if (number == 0) {
    number = kMagicNumber;
  }
  return number;
}

int AmontOfSubseq(std::vector<int>& seq) {
  int length = static_cast<int>(seq.size());
  std::vector<int> dp(length + 1, 1);
  std::map<int, int> met;
  for (int i = 1; i < length + 1; ++i) {
    dp[i] = GetMod(2 * dp[i - 1] - met[seq[i - 1]]);
    met[seq[i - 1]] = dp[i - 1];
  }
  return dp[length];
}

int main() {
  int number = 0;
  std::cin >> number;
  std::vector<int> seq(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> seq[i];
  }
  std::cout << AmontOfSubseq(seq) - 1 << '\n';
}