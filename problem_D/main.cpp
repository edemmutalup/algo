#include <algorithm>
#include <iostream>
#include <vector>

const int kInf = 1e9;

void Out(std::vector<int>& ans_boys, std::vector<int>& ans_girls,
         std::vector<std::pair<int, std::string>>& boys,
         std::vector<std::pair<int, std::string>>& girls);

int Taxi(std::vector<std::pair<int, std::string>>& boys,
         std::vector<std::pair<int, std::string>>& girls,
         std::vector<std::vector<int>>& dp) {
  int amount_of_boys = static_cast<int>(boys.size()) + 1;
  int amount_of_girls = static_cast<int>(girls.size()) + 1;
  dp[0][0] = 0;
  for (int i = 0; i < amount_of_boys; ++i) {
    for (int j = 0; j < amount_of_girls; ++j) {
      for (int k = 1; k < 5 && k <= i; ++k) {
        for (int idx_l = 0; idx_l < 4 && k + idx_l <= 4 && idx_l <= j;
             ++idx_l) {
          dp[i][j] = std::min(dp[i][j],
                              dp[i - k][j - idx_l] +
                                  ((idx_l != 0) ? std::max(boys[i - 1].first,
                                                           girls[j - 1].first)
                                                : boys[i - 1].first));
        }
      }
    }
  }
  return dp[amount_of_boys - 1][amount_of_girls - 1];
}

void RecAns(std::vector<std::pair<int, std::string>>& boys,
            std::vector<std::pair<int, std::string>>& girls,
            std::vector<std::vector<int>>& dp) {
  int amount_of_boys = static_cast<int>(boys.size());
  int amount_of_girls = static_cast<int>(girls.size());
  int idx_i = amount_of_boys;
  int idx_j = amount_of_girls;
  std::vector<int> ans_boys;
  std::vector<int> ans_girls;
  while (idx_i != 0 || idx_j != 0) {
    bool mark = true;
    for (int k = 1; k < 5 && mark; ++k) {
      for (int idx_l = 0;
           idx_l < 4 && k + idx_l <= 4 && idx_l <= idx_j && k <= idx_i && mark;
           ++idx_l) {
        if (dp[idx_i][idx_j] ==
            dp[idx_i - k][idx_j - idx_l] +
                ((idx_l != 0)
                     ? std::max(boys[idx_i - 1].first, girls[idx_j - 1].first)
                     : boys[idx_i - 1].first)) {
          idx_i -= k;
          idx_j -= idx_l;
          ans_boys.push_back(k);
          ans_girls.push_back(idx_l);
          mark = false;
        }
      }
    }
  }
  Out(ans_boys, ans_girls, boys, girls);
}

void Out(std::vector<int>& ans_boys, std::vector<int>& ans_girls,
         std::vector<std::pair<int, std::string>>& boys,
         std::vector<std::pair<int, std::string>>& girls) {
  int cars = static_cast<int>(ans_boys.size());
  std::cout << cars << '\n';
  int boy = 0;
  int girl = 0;
  for (int i = 0; i < cars; ++i) {
    std::cout << "Taxi " << i + 1 << ": ";
    for (int k = 0; k < ans_boys[cars - 1 - i]; ++k) {
      std::cout << boys[boy++].second;
      if (k == ans_boys[cars - 1 - i] - 1 && ans_girls[cars - 1 - i] == 0) {
        std::cout << ".\n";
      } else if (ans_boys[cars - 1 - i] - 1 - k + ans_girls[cars - 1 - i] > 1) {
        std::cout << ", ";
      } else {
        std::cout << " and ";
      }
    }
    for (int idx_l = 0; idx_l < ans_girls[cars - 1 - i]; ++idx_l) {
      std::cout << girls[girl++].second;
      if (ans_girls[cars - 1 - i] - 1 - idx_l == 0) {
        std::cout << ".\n";
      } else if (ans_girls[cars - 1 - i] - 1 - idx_l > 1) {
        std::cout << ", ";
      } else {
        std::cout << " and ";
      }
    }
  }
}

int main() {
  int amount_of_boys = 0;
  int amount_of_girls = 0;
  std::cin >> amount_of_boys;
  std::vector<std::pair<int, std::string>> boys(amount_of_boys);
  for (int i = 0; i < amount_of_boys; ++i) {
    std::cin >> boys[i].second >> boys[i].first;
  }
  std::cin >> amount_of_girls;
  std::vector<std::pair<int, std::string>> girls(amount_of_girls);
  for (int i = 0; i < amount_of_girls; ++i) {
    std::cin >> girls[i].second >> girls[i].first;
  }
  std::vector<std::vector<int>> dp(amount_of_boys + 1,
                                   std::vector<int>(amount_of_girls + 1, kInf));
  std::sort(boys.begin(), boys.end());
  std::sort(girls.begin(), girls.end());
  std::cout << Taxi(boys, girls, dp) << '\n';
  RecAns(boys, girls, dp);
  return 0;
}
