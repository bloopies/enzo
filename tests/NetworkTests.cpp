#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include "Engine/Operator/GOP_test.h"
#include <iostream>

struct NMReset 
{
    NMReset()
    {
        enzo::nt::NetworkManager::_reset();
    }
    ~NMReset()
    {
        enzo::nt::NetworkManager::_reset();
    }

};

TEST_CASE_METHOD(NMReset, "network fixture separation start")
{
    using namespace enzo;
    nt::OpId newOpId = nt::NetworkManager::addOperator(GOP_test::ctor);
    REQUIRE(newOpId==1);
    REQUIRE(nt::NetworkManager::isValidOp(1));
    
}

TEST_CASE_METHOD(NMReset, "network fixture separation end")
{
    using namespace enzo;
    REQUIRE_FALSE(nt::NetworkManager::isValidOp(1));

}

TEST_CASE_METHOD(NMReset, "network")
{
    using namespace enzo;
    nt::OpId newOpId = nt::NetworkManager::addOperator(GOP_test::ctor);
    nt::OpId newOpId2 = nt::NetworkManager::addOperator(GOP_test::ctor);

    REQUIRE(nt::NetworkManager::isValidOp(newOpId));
    if(nt::NetworkManager::isValidOp(newOpId))
    {
        auto newConnection = std::make_shared<nt::GeometryConnection>(newOpId, 1, newOpId2, 3); 

        auto& inputOp = nt::NetworkManager::getGeoOperator(newOpId);
        auto& outputOp = nt::NetworkManager::getGeoOperator(newOpId2);

        // set output on the upper operator
        outputOp.addOutputConnection(newConnection);

        // set input on the lower operator
        inputOp.addInputConnection(newConnection);

    }
}

TEST_CASE_METHOD(NMReset, "reset")
{
    using namespace enzo;
    nt::OpId newOpId = nt::NetworkManager::addOperator(GOP_test::ctor);

    nt::NetworkManager::_reset();

    REQUIRE_FALSE(nt::NetworkManager::isValidOp(newOpId));

    nt::OpId newOpId2 = nt::NetworkManager::addOperator(GOP_test::ctor);
    REQUIRE(nt::NetworkManager::isValidOp(newOpId2));


}

