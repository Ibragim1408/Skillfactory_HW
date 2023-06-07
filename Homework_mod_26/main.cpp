#include <iostream>
#include <thread>
#include <random>
#include <vector>
#include <numeric>


int main() {
  int n, m;
  std::cout << "Enter Number of element: " << std::endl;
  std::cin >> n;
  std::vector<int> massive(n);
  std::random_device dev;
  std::mt19937 rng(dev());
  int max_value = 10;
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, max_value);
  for (size_t i = 0; i < n; ++i) {
    massive[i] = int(dist(rng)) - max_value / 2;
    std::cout << massive[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "Enter Number of thread: " << std::endl;
  std::cin >> m;
  std::vector<std::thread> threads;
  std::vector<int> subsum(m, 0);
  int range = n % m == 0 ? n / m : n / m + 1;

  auto CalcSumElement = [&massive, &range, &subsum] (int first, int i) {
    for (int j = first; j < massive.size() && j < first + range; ++j) {
      subsum[i] += massive[j];
    }
    std::cout << "Thread " << i << " have sum: " << subsum[i] << std::endl;
  };
  for (int i = 0; i < m; ++i) {
    auto first = i * range;
    std::thread t(CalcSumElement, first, i);
    threads.push_back(std::move(t));
  }
  for (int i = 0; i < m; ++i) {
    threads[i].join();
  }
  std::cout << "Sum of all element: " << std::accumulate(subsum.begin(), subsum.end(), 0) << std::endl;
  return 0;
}