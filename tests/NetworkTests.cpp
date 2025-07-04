#include <catch2/catch_test_macros.hpp>
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
        nt::GeometryOperator& newOp = nm->getGeoOperator(newOpId); 
        REQUIRE(newOp.setInput(0, newOpId2));

        std::optional<nt::OpId> returnOpId = newOp.getInput(0);
        REQUIRE(returnOpId.has_value());
        REQUIRE(*returnOpId==newOpId2);
    }
}

