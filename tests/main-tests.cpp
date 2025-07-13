#include <catch2/catch_test_macros.hpp>
#include <oneapi/tbb/parallel_for.h>
#include <iostream>
#include <boost/dll/import.hpp>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/OperatorTable.h"

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

TEST_CASE("boost dll")
{
    std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minor version
          << BOOST_VERSION % 100                // patch level
          << std::endl;


    boost::shared_ptr<std::string> cpp_var = boost::dll::import_symbol<std::string>(
            "build/src/OpDefs/libenzoOps1.so", "myVar"
        );
    std::cout << "VAR: " << *cpp_var << "\n";

    auto cpp11_func = boost::dll::import_symbol<void(void (*addOperator)(enzo::nt::opConstructor))>(
        "build/src/OpDefs/libenzoOps1.so", "newSopOperator"
    );

    cpp11_func(enzo::op::OperatorTable::addOperator);

}
