#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include <iostream>

TEST_CASE("network")
{
    using namespace enzo;
    nt::NetworkManager::_reset();
    nt::OpId newOpId = nt::NetworkManager::addOperator();
    nt::OpId newOpId2 = nt::NetworkManager::addOperator();

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

TEST_CASE("reset")
{
    using namespace enzo;
    nt::OpId newOpId = nt::NetworkManager::addOperator();
    nt::NetworkManager::_reset();
    nt::OpId newOpId2 = nt::NetworkManager::addOperator();


    REQUIRE_FALSE(nt::NetworkManager::isValidOp(newOpId));
    REQUIRE(nt::NetworkManager::isValidOp(newOpId2));
}

