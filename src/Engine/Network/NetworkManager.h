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

    static NetworkManager* getInstance();

    static OpId addOperator();
    void setDisplayOp(OpId opId);
    static std::optional<OpId> getDisplayOp();
    static bool isValidOp(nt::OpId opId);
    static GeometryOperator& getGeoOperator(nt::OpId opId);

private:
    static NetworkManager* instancePtr_;
    NetworkManager() {};

    static std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> gopStore_;

    static void cookOp(enzo::nt::OpId opId);
    static std::vector<enzo::nt::OpId> getDependencyGraph(enzo::nt::OpId opId);

    // the highest operator id currently stored
    inline static enzo::nt::OpId maxOpId_=0;

    inline static std::optional<OpId> displayOp_=std::nullopt;
signals:
    void updateDisplay(enzo::geo::Geometry& geometry);

};
}
