#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>


std::vector<int> randomVector(size_t n = 100, size_t max_val = 10000) {

    std::vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = std::rand()%max_val;
    }
    return res;
}

bool sorted(std::vector<int>& v) {
    for (int i = 1; i < v.size(); ++i) {
        if (v[i-1] > v[i])  return false;
    }
    return true;
}

void balanceHeap(int* beg, size_t n, size_t index) {
    for (size_t i = index; i*2 + 1 < n;) {
        auto ch_idx = i*2 + 1;

        if (ch_idx + 1 < n && beg[ch_idx] < beg[ch_idx + 1]) {
            ch_idx += 1;
        }
        if (beg[i] < beg[ch_idx]) {
            std::swap(beg[i],beg[ch_idx]);
            i = ch_idx;
        } else {
            break;
        }
    }

}
void makeHeap(int* beg, size_t n, size_t index) {
    for (size_t _idx_ = n/2; _idx_ > 0; --_idx_) {
        auto index = _idx_ - 1;
        balanceHeap(beg,n,index);
    }
}

void heapSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    auto beg = &arr[0];
    makeHeap(beg, arr.size(), 0);
    std::swap(beg[arr.size() - 1], beg[0]);

    for (size_t i = arr.size(); i > 0; --i)
    {
        balanceHeap(beg, i-1, 0);
        std::swap(beg[i - 1], beg[0]);
    }
}


void quickSortImpl(int* beg, size_t n) {
    if (n < 2) return;

    if (n == 2) {
        if (beg[0] > beg[1]) {
            std::swap(beg[0], beg[1]);
        }
        return;
    }

    auto mid_idx = n/2;
//    auto mid_idx = (n/2 + rand()%n) / 2;

    auto l = beg;
    auto r = beg + n - 1;
    auto m = beg + mid_idx;

    while (1) {

        while (l < m && *l <= *m) { ++l; }
        while (r > m && *r >= *m) { --r; }

        if (l == m && m == r) {
            break;
        }
        if (l == m || r == m) {
            auto n = r - l + (l == m);
            auto m2 = n / 2 + l;
            std::swap(*m, *m2);
            m = m2;
        } else {
            std::swap(*l++, *r--);
        }
    }

    quickSortImpl(beg, m - beg);
    quickSortImpl(m + 1, beg + n - m - 1);
}


void quickSort(std::vector<int>& arr) {
    if (arr.empty()) return;
    auto beg = &arr[0];
    quickSortImpl(beg, arr.size());
}


int main() {


    using namespace std::chrono;

    auto r = randomVector(10000000);

    auto beg = system_clock::now();
//    heapSort(r);
    quickSort(r);
//    std::sort(r.begin(), r.end());
    auto elapsed = duration_cast<microseconds>(system_clock::now() - beg).count();
    std::cout << elapsed / 1000.0 << std::endl;
//    for (auto&a : r) {
//        std::cout << " " << a;
//    }
    std::cout << '\n' << sorted(r) << std::endl;
    return 0;
}