#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <span>
#include <thread>
#include <vector>

auto count_5s(std::span<int> s, std::atomic<int>& count)
{
  for (auto&& e : s) {
    if (e == 5) {
      ++count;
    }
  }
}

auto generate(int n, int n_of_5s)
{
  assert(n_of_5s <= n);
  std::vector<int> v(n);
  std::fill_n(v.begin(), n_of_5s, 5);
  std::default_random_engine eng;
  std::shuffle(v.begin(), v.end(), eng);
  return v;
}

int main()
{
  int const n = 100'000'000;
  std::cout << "Generating... " << std::flush;
  auto v = generate(n, n / 4);
  std::cout << "done\n";

  auto mid_it = std::next(v.begin(), v.size() / 2);

  std::vector<std::thread> vth;
  vth.reserve(2);

  std::atomic<int> count{0};
  auto t0 = std::chrono::system_clock::now();

  vth.emplace_back(std::thread{[&, s = std::span{v.begin(), mid_it}] { count_5s(s, count); }});
  vth.emplace_back(std::thread{[&, s = std::span{mid_it, v.end()}] { count_5s(s, count); }});

  for (auto&& th : vth) {
    th.join();
  }

  auto t1 = std::chrono::system_clock::now();

  std::cout << "#5 " << count << " in " << std::chrono::duration<double>{t1 - t0}.count() << " s\n";
}