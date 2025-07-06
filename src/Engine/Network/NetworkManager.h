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
    void setDisplayOp(OpId opId);
    std::optional<OpId> getDisplayOp();
    // delete copy constructor
    NetworkManager(const NetworkManager& obj) = delete;

    static NetworkManager* getInstance();

    bool isValidOp(nt::OpId opId);
    GeometryOperator& getGeoOperator(nt::OpId opId);

private:
    static NetworkManager* instancePtr_;
    NetworkManager() {};

    std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> gopStore_;

    void cookOp(enzo::nt::OpId opId);
    std::vector<enzo::nt::OpId> getTraversalGraph(enzo::nt::OpId opId);

    // the highest operator id currently stored
    enzo::nt::OpId maxOpId_=0;

    std::optional<OpId> displayOp_=std::nullopt;

};
}
