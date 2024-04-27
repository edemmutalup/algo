#include <iostream>
#include <vector>

const int kMagicNumber = 17;

int BinarySearch(std::vector<std::vector<int>>& dp, int idx_i, int idx_j) {
  int left = 1;
  int right = idx_i;
  while (right - left > 1) {
    int middle = (left + right) / 2;
    if (dp[middle][idx_j - 1] > dp[idx_i - middle][idx_j]) {
      right = middle;
    } else {
      left = middle;
    }
  }
  return left;
}

int64_t GTA(int height, int planes) {
  if (height == 1) {
    return 0;
  }
  if (planes == 0) {
    return -1;
  }
  if (planes > kMagicNumber) {
    planes = kMagicNumber;
  }
  std::vector<std::vector<int>> dp(height + 1, std::vector<int>(planes + 1, 0));
  for (int i = 1; i < height + 1; ++i) {
    dp[i][1] = i - 1;
  }
  for (int i = 2; i < height + 1; ++i) {
    for (int j = 2; j < planes + 1; ++j) {
      int index = BinarySearch(dp, i, j);
      dp[i][j] = 1 + std::max(dp[index][j - 1], dp[i - index][j]);
    }
  }
  return dp[height][planes];
}

int main() {
  int height = 0;
  int planes = 0;
  std::cin >> height >> planes;
  std::cout << GTA(height, planes) << '\n';
  return 0;
}
