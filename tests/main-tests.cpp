#include <catch2/catch_test_macros.hpp>
#include <oneapi/tbb/parallel_for.h>
#include <iostream>

TEST_CASE("foo")
{
    REQUIRE(1==1);
}

TEST_CASE("tbb")
{
    constexpr int N = 100;

    oneapi::tbb::parallel_for(0, N, [](int i) {
        std::cout << "Iteration " << i
                  << " is running on thread "
                  << std::this_thread::get_id() << std::endl;
    });
}
