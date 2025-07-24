#pragma once
#include "Engine/Operator/GeometryOperator.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Types.h"
#include <memory>
#include <unordered_map>
#include <QObject>

namespace enzo::nt {
class NetworkManager
: public QObject
{
    Q_OBJECT
public:
    // delete copy constructor
    NetworkManager(const NetworkManager& obj) = delete;

    static NetworkManager& getInstance();

    // functions
    OpId addOperator(op::OpInfo opInfo);
    std::optional<OpId> getDisplayOp();
    bool isValidOp(nt::OpId opId);
    GeometryOperator& getGeoOperator(nt::OpId opId);
    void setDisplayOp(OpId opId);

    #ifdef UNIT_TEST
        void _reset();
    #endif

private:
    NetworkManager() {};

    // functions
    void cookOp(enzo::nt::OpId opId);
    std::vector<enzo::nt::OpId> getDependencyGraph(enzo::nt::OpId opId);

    // variables
    // store for geometry operators
    std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> gopStore_;
    // the highest operator id currently stored
    enzo::nt::OpId maxOpId_=0;
    // operator selected for displaying in the viewport
    std::optional<OpId> displayOp_=std::nullopt;
Q_SIGNALS:
    void updateDisplay(enzo::geo::Geometry& geometry);

};

inline enzo::nt::NetworkManager& nm() {
    return enzo::nt::NetworkManager::getInstance();
}
}
