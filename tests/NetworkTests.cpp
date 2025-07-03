#include <catch2/catch_test_macros.hpp>
#include "Engine/Network/NetworkManager.h"


TEST_CASE("network")
{
    enzo::nt::NetworkManager networkManager;
    networkManager.addOperator();
}

