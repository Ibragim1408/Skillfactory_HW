#include <iostream>
#include <vector>
#include <future>

using namespace std;  // использую в учебных целях

void merge(vector<int>& num, int low, int mid, int high) {
  vector<int>copy(num.size());
  int h = low;
  int i = low;
  int j = mid + 1;

  while(h <= mid && j <= high) {
    if (num[h] <= num[j]) {
	    copy[i] = num[h];
	    h++;
	  } else {
	    copy[i] = num[j];
	    j++;
	  }
    i++;
  }
  if (h > mid) {
    for (int k = j; k <= high; k++) {
	    copy[i] = num[k];
	    i++;
	  }
  } else {
    for (int k = h; k <= mid; k++) {
  	  copy[i] = num[k];
	    i++;
	  }
  }
  for (int k = low; k <= high; k++) {
    swap (num[k], copy[k]);
  }
}

void merge_sort(vector<int>& num, int low, int high) {
  int mid;
  if (low < high) {
    mid = low + (high - low) / 2;
    auto future1 = async(std::launch::deferred, [&] () {merge_sort(num, low, mid); });
    auto future2 = async(std::launch::deferred, [&] () {merge_sort(num, mid + 1, high); });

    future1.get();
    future2.get();
    merge(num, low, mid, high);
  }
}

int main () {
  vector<int> nums{38, 27, 43, 3, 9, 82, 10};
  merge_sort(nums, 0, nums.size() - 1);
  for (auto x : nums) {
      cout << x << " ";
  }
  return 0;
}
