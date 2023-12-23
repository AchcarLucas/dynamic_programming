#include <functional>
#include <iostream>
#include <ostream>
#include <utility>
#include <limits>
#include <list>

#include <stdint.h>

template <typename T>
std::ostream& operator<<( std::ostream& os, std::list<T> const &list)
{
    os << "{ ";
    for (auto const &i: list)
        os << i << " ";
    os << "}";
    return os;
}

std::list<std::pair<uint64_t, uint64_t>> mem;

uint64_t fib(uint64_t n)
{
    for(auto const &m : mem) {
        if(m.first == n)
            return m.second;
    }

    if(n <= 2) return 1;

    std::pair<uint64_t, uint64_t> result = std::make_pair(n, fib(n - 1) + fib(n - 2));
    mem.insert(mem.begin(), result);

    return result.second;
}

uint64_t minimum_coins(uint64_t money, std::list<uint64_t> coins)
{
    if(money == 0) return 0;

    for(auto const &m : mem) {
        if(m.first == money)
            return m.second;
    }

    uint64_t answer = std::numeric_limits<uint64_t>::max();

    for(auto const &coin : coins) {
        int64_t sub_p = (int64_t)(money - coin);
        if(sub_p < 0)
            continue;
        answer = std::min(answer, minimum_coins(money - coin, coins) + 1);
    }

    std::pair<uint64_t, uint64_t> result = std::make_pair(money, answer);
    mem.insert(mem.begin(), result);

    return result.second;
}

uint64_t many_ways_coins(uint64_t money, std::list<uint64_t> coins)
{
    if(money == 0) return 1;

    for(auto const &m : mem) {
        if(m.first == money)
            return m.second;
    }

    uint64_t answer = 0;

    for(auto const &coin : coins) {
        int64_t sub_p = (int64_t)(money - coin);
        if(sub_p < 0)
            continue;
        answer = answer + many_ways_coins(money - coin, coins);
    }

    std::pair<uint64_t, uint64_t> result = std::make_pair(money, answer);
    mem.insert(mem.begin(), result);

    return result.second;
}

void test_fib()
{
    mem.clear();
    uint64_t n = 50;
    std::cout << "fib(" << n << ") = " << fib(n) << std::endl;
}

void test_minimum_coins()
{
    mem.clear();
    uint64_t money = 150;
    std::list<uint64_t> coins = {1, 4, 5};
    std::cout << "minimum_coins(" << money << ", " << coins << ") = " << minimum_coins(money, coins) << std::endl;
}

void test_many_ways()
{
    mem.clear();
    uint64_t money = 87;
    std::list<uint64_t> coins = {1, 4, 5, 8};
    std::cout << "many_ways_coins(" << money << ", " << coins << ") = " << many_ways_coins(money, coins) << std::endl;
}

int main()
{
    test_fib();
    test_minimum_coins();
    test_many_ways();
    return 0;
}
