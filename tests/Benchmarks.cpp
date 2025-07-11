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

TEST_CASE_METHOD(NMReset, "Network Manager")
{
    using namespace enzo;
    nt::OpId startOp = nt::NetworkManager::addOperator(&GOP_test::ctor);
    nt::OpId prevOp = startOp;
    std::vector<nt::OpId> prevOps;

    for(int k=0; k<10; k++)
    {
        for(int i=0; i<4; ++i)
        {
            nt::OpId newOp = nt::NetworkManager::addOperator(&GOP_test::ctor);
            prevOps.push_back(newOp);
            nt::connectOperators(newOp, i, prevOp, 0);
        }
        for(int j=0; j<10; j++)
        {
            std::vector<nt::OpId> prevOpsBuffer = prevOps;
            for(int i=0; i<size(prevOpsBuffer); ++i)
            {
                prevOps.clear();
                nt::OpId newOp = nt::NetworkManager::addOperator(GOP_test::ctor);
                prevOps.push_back(newOp);
                nt::connectOperators(newOp, 0, prevOpsBuffer[i], 0);

                
            }
        }
    }

    nt::NetworkManager* nm = nt::NetworkManager::getInstance();
    BENCHMARK("Cook 100 Ops")
    {
        nm->setDisplayOp(startOp);
    };
    

}
