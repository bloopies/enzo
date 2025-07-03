#include <catch2/catch_test_macros.hpp>
#include "Engine/Network/NetworkManager.h"


TEST_CASE("network")
{
    using namespace enzo;
    nt::NetworkManager* nm = nt::NetworkManager::getInstance();
    nm->addOperator();
}

