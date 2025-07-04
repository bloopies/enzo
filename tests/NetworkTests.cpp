#include <catch2/catch_test_macros.hpp>
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"


TEST_CASE("network")
{
    using namespace enzo;
    nt::NetworkManager* nm = nt::NetworkManager::getInstance();
    nt::OpId newOpId = nm->addOperator();
    nt::OpId newOpId2 = nm->addOperator();

    REQUIRE(nm->isValidOp(newOpId));
    if(nm->isValidOp(newOpId))
    {
        auto newConnection = std::make_shared<nt::GeometryConnection>(newOpId, 1, newOpId2, 3); 

        auto inputOp = nm->getGeoOperator(newOpId);
        auto outputOp = nm->getGeoOperator(newOpId2);

        // set output on the upper operator
        outputOp.addOutputConnection(newConnection);

        // set input on the lower operator
        inputOp.addInputConnection(newConnection);

    }
}

