#include <iostream>

template <class T, class U>
int Partition(T* iter_begin, T* iter_end, const U& pivot) {
  int less_pivot = 0;
  int equal_pivot = 0;
  for (int i = 0; i < iter_end - iter_begin; ++i) {
    if (*(iter_begin + i) < pivot) {
      std::swap(*(iter_begin + i), *(iter_begin + less_pivot));
      if (equal_pivot != 0) {
        std::swap(*(iter_begin + i), *(iter_begin + less_pivot + equal_pivot));
      }
      ++less_pivot;
    } else if (!(*(iter_begin + i) < pivot) && !(pivot < *(iter_begin + i))) {
      std::swap(*(iter_begin + i), *(iter_begin + less_pivot + equal_pivot));
      ++equal_pivot;
    }
  }
  return less_pivot;
}

template <class T>
void Sort(T* iter_begin, T* iter_end) {
  if (iter_end - iter_begin <= 1) {
    return;
  }
  T pivot = *(iter_begin + (rand() % (iter_end - iter_begin)));
  int less_pivot = 0;
  less_pivot = Partition(iter_begin, iter_end, pivot);
  int equal_pivot = 0;
  for (int i = 0; i < iter_end - iter_begin; ++i) {
    if (!(*(iter_begin + i) < pivot) && !(pivot < *(iter_begin + i))) {
      ++equal_pivot;
    }
  }
  Sort(iter_begin, iter_begin + less_pivot);
  Sort(iter_begin + less_pivot + equal_pivot, iter_end);
}

int Maximum(const int* seq, int length) {
  int idx_max = 0;
  for (int i = 0; i < length; ++i) {
    if (seq[idx_max] < seq[i]) {
      idx_max = i;
    }
  }
  return idx_max;
}

int Answer(const int* costs, const int* weights, int* dest, int length,
           int limit) {
  auto** dp = new int*[length + 1];
  auto** pos = new int*[length + 1];
  int weight = 0;
  for (int i = 0; i < length; ++i) {
    weight += weights[i];
  }
  for (int i = 0; i < length + 1; ++i) {
    dp[i] = new int[weight + 1]();
    pos[i] = new int[weight + 1]();
  }
  for (int i = 0; i < length; ++i) {
    for (int j = 0; j < weight + 1 - weights[i]; ++j) {
      dp[i + 1][j] = std::max(dp[i + 1][j], dp[i][j]);
      dp[i + 1][j + weights[i]] =
          std::max(dp[i + 1][j + weights[i]], dp[i][j] + costs[i]);
    }
  }
  int idx = Maximum(dp[length], std::min(limit + 1, weight + 1));
  for (int i = 1; i < length + 1; ++i) {
    for (int j = 0; j < weight + 1; ++j) {
      if (dp[i][j] == dp[i - 1][j]) {
        pos[i][j] = 0;
      } else if (j - weights[i - 1] >= 0 &&
                 dp[i - 1][j - weights[i - 1]] + costs[i - 1] == dp[i][j]) {
        pos[i][j] = 1;
      }
    }
  }
  int idx_i = length;
  int idx_j = idx;
  int index = 0;
  while (dp[idx_i][idx_j] != 0 && (idx_i >= 1 && idx_j >= 0)) {
    if (pos[idx_i][idx_j] == 0) {
      --idx_i;
    } else if (pos[idx_i][idx_j] == 1) {
      --idx_i;
      dest[index++] = idx_i + 1;
      idx_j -= weights[idx_i];
    }
  }
  for (int i = 0; i < length + 1; ++i) {
    delete[] dp[i];
    delete[] pos[i];
  }
  delete[] pos;
  delete[] dp;
  return index;
}

int main() {
  int number = 0;
  int limit = 0;
  std::cin >> number >> limit;
  auto* costs = new int[number];
  auto* weights = new int[number];
  auto* dest = new int[number];
  for (int i = 0; i < number; ++i) {
    std::cin >> weights[i];
  }
  for (int i = 0; i < number; ++i) {
    std::cin >> costs[i];
  }
  int length = Answer(costs, weights, dest, number, limit);
  Sort(dest, dest + length);
  for (int i = 0; i < length; ++i) {
    std::cout << dest[i] << ' ';
  }
  std::cout << '\n';
  delete[] dest;
  delete[] costs;
  delete[] weights;
  return 0;
}
