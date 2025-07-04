#pragma once
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Types.h"
#include <memory>
#include <unordered_map>

namespace enzo::nt {
class NetworkManager
{
public:
    OpId addOperator();
    // delete copy constructor
    NetworkManager(const NetworkManager& obj) = delete;

    static NetworkManager* getInstance();

    bool isValidOp(nt::OpId opId);
    GeometryOperator& getGeoOperator(nt::OpId opId);

private:
    static NetworkManager* instancePtr_;
    NetworkManager() {};

    std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> gopStore_;
    enzo::nt::OpId maxOpId_=0;

};
}
