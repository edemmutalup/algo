#include <vector>
#include <iostream>

const int kNegInf = -1e9;

int Knapsack(const std::vector<std::vector<int>>& weights,
              const std::vector<std::vector<int>>& costs,
              int weight) {
  int amount_of_groups = static_cast<int>(weights.size());
  std::vector<std::vector<int>> dp(weight + 1,
                                   std::vector<int>(amount_of_groups + 1, kNegInf));
  for (int i = 1; i < weight + 1; ++i) {
    dp[i][0] = 0;
  }
  for (int i = 0; i < amount_of_groups - 1; ++i) {
    int amount_of_elems = static_cast<int>(weights[i + 1].size());
    for (int j = 1; j < weight + 1; ++j) {
      for (int k = 0; i < amount_of_elems; ++k) {
        if (j + weights[i + 1][k] < weight + 1) {
          dp[j + weights[i + 1][k]][i + 1] = std::max(dp[j][i] + costs[i + 1][k],
                                                      dp[j + weights[i + 1][k]][i + 1]);
        }
      }
    }
  }
  int result = 0;
  for (int i = 1; i < weight + 1; ++i) {
    result = std::max(result, dp[amount_of_groups][i]);
  }
  return result;
}

int main() {
  int number_n = 0;
  int number_G = 0;
  int number_K = 0;
  std::cin >> number_n >> number_G >> number_K;
  std::vector<std::vector<int>> weights(number_G);
  std::vector<std::vector<int>> costs(number_G);
  int elem_k = 0;
  int elem_v = 0;
  int elem_g = 0;
  for (int i = 0; i < number_n; ++i) {
    std::cin >> elem_k >> elem_v >> elem_g;
    weights[elem_g].push_back(elem_k);
    costs[elem_g].push_back(elem_v);
  }
  std::cout << Knapsack(weights, costs, number_K) << '\n';
}
