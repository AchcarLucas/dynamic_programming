#include <functional>
#include <iostream>
#include <ostream>
#include <utility>
#include <limits>
#include <list>
#include <cassert>

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

template <typename T>
std::ostream& operator<<( std::ostream& os, std::vector<T> const &list)
{
    os << "{ ";
    for (auto const &i: list)
        os << i << " ";
    os << "}";
    return os;
}

std::list<std::pair<uint64_t, uint64_t>> mem_linear;
std::list<std::pair<std::pair<uint64_t, uint64_t>, uint64_t>> mem_quad;

uint64_t fib(uint64_t n)
{
    if(n <= 2) return 1;

    for(auto const &m : mem_linear) {
        if(m.first == n)
            return m.second;
    }

    std::pair<uint64_t, uint64_t> result = std::make_pair(n, fib(n - 1) + fib(n - 2));
    mem_linear.insert(mem_linear.begin(), result);

    return result.second;
}

uint64_t minimum_coins(uint64_t money, std::list<uint64_t> coins)
{
    if(money == 0) return 0;

    for(auto const &m : mem_linear) {
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
    mem_linear.insert(mem_linear.begin(), result);

    return result.second;
}

uint64_t many_ways_coins(uint64_t money, std::list<uint64_t> coins)
{
    if(money == 0) return 1;

    for(auto const &m : mem_linear) {
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
    mem_linear.insert(mem_linear.begin(), result);

    return result.second;
}

uint64_t maze_problem(uint64_t _n, uint64_t _m)
{
    if(_m == 1 || _n == 1) return 1;

    for(auto const &m : mem_quad) {
        std::pair<uint64_t, uint64_t> grid = m.first;
        if(grid.first == _n && grid.second == _m)
            return m.second;
    }

    std::pair<std::pair<uint64_t, uint64_t>, uint64_t> result = std::make_pair(std::make_pair(_n, _m), maze_problem(_n - 1, _m) + maze_problem(_n, _m - 1));
    mem_quad.insert(mem_quad.begin(), result);

    return result.second;
}

uint64_t longest_common_subsequence(uint64_t _n, uint64_t _m, std::vector<uint64_t> a, std::vector<uint64_t> b)
{
    if(_n == 0 || _m == 0) return 0;

    for(auto const &m : mem_quad) {
        std::pair<uint64_t, uint64_t> grid = m.first;
        if(grid.first == _n && grid.second == _m)
            return m.second;
    }

    uint64_t r;

    if(a[_n - 1] == b[_m - 1])
        r = 1 + longest_common_subsequence(_n - 1, _m - 1, a, b);
    else
        r = std::max(longest_common_subsequence(_n - 1, _m, a, b), longest_common_subsequence(_n, _m - 1, a, b));

    std::pair<std::pair<uint64_t, uint64_t>, uint64_t> result = std::make_pair(std::make_pair(_n, _m), r);
    mem_quad.insert(mem_quad.begin(), result);

    return result.second;
}

void test_fib()
{
    mem_linear.clear();
    uint64_t n = 50;
    std::cout << "fib(" << n << ") = " << fib(n) << std::endl;
}

void test_minimum_coins()
{
    mem_linear.clear();
    uint64_t money = 150;
    std::list<uint64_t> coins = {1, 4, 5};
    std::cout << "minimum_coins(" << money << ", " << coins << ") = " << minimum_coins(money, coins) << std::endl;
}

void test_many_ways()
{
    mem_linear.clear();
    uint64_t money = 87;
    std::list<uint64_t> coins = {1, 4, 5, 8};
    std::cout << "many_ways_coins(" << money << ", " << coins << ") = " << many_ways_coins(money, coins) << std::endl;
}

void test_maze_problem()
{
    mem_quad.clear();
    uint64_t n = 75;
    uint64_t m = 19;
    std::cout << "maze_problem(" << n << ", " << m << ") = " << maze_problem(n, m) << std::endl;
}

void test_longest_common_subsequence()
{
    {
        mem_quad.clear();
        std::vector<uint64_t> a = {6, 4, 5, 9, 11};
        std::vector<uint64_t> b = {1, 15, 4, 5, 6, 9, 10, 11};
        uint64_t r = longest_common_subsequence(a.size(), b.size(), a, b);
        assert(r == 4);
        std::cout << "longest_common_subsequence(" << a.size() << ", " << b.size() << ", " << a << ", " << b << ") = " << r << std::endl;
    }

    {
        mem_quad.clear();
        std::vector<uint64_t> a = {};
        std::vector<uint64_t> b = {1, 15, 4, 5, 6, 9, 10, 11};
        uint64_t r = longest_common_subsequence(a.size(), b.size(), a, b);
        assert(r == 0);
        std::cout << "longest_common_subsequence(" << a.size() << ", " << b.size() << ", " << a << ", " << b << ") = " << r << std::endl;
    }

    {
        mem_quad.clear();
        std::vector<uint64_t> a = {};
        std::vector<uint64_t> b = {};
        uint64_t r = longest_common_subsequence(a.size(), b.size(), a, b);
        assert(r == 0);
        std::cout << "longest_common_subsequence(" << a.size() << ", " << b.size() << ", " << a << ", " << b << ") = " << r << std::endl;
    }

    {
        mem_quad.clear();
        std::vector<uint64_t> a = {1, 2, 3, 4, 5};
        std::vector<uint64_t> b = {1, 2, 3, 4, 5};
        uint64_t r = longest_common_subsequence(a.size(), b.size(), a, b);
        assert(r == 5);
        std::cout << "longest_common_subsequence(" << a.size() << ", " << b.size() << ", " << a << ", " << b << ") = " << r << std::endl;
    }
}

int main()
{
    test_fib();
    test_minimum_coins();
    test_many_ways();
    test_maze_problem();
    test_longest_common_subsequence();
    return 0;
}
