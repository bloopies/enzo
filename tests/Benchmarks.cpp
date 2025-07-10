#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <memory>
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
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

TEST_CASE_METHOD(NMReset, "Network Manager")
{
    using namespace enzo;
    nt::OpId prevOp = 0;
    for(int i=0; i<100; ++i){
        nt::OpId newOp = nt::NetworkManager::addOperator();
        if(prevOp!=0)
        {
            nt::connectOperators(newOp, 0, prevOp, 0);
        }

        prevOp = newOp;
    }

    nt::NetworkManager* nm = nt::NetworkManager::getInstance();
    BENCHMARK("Cook 100 Ops")
    {
        nm->setDisplayOp(prevOp);
    };
    

}
