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

    // functions
    static OpId addOperator(nt::opConstructor ctorFunc);
    static std::optional<OpId> getDisplayOp();
    static bool isValidOp(nt::OpId opId);
    static GeometryOperator& getGeoOperator(nt::OpId opId);
    static void setDisplayOp(OpId opId);

    #ifdef UNIT_TEST
        static void _reset();
    #endif

private:
    static NetworkManager* instancePtr_;
    NetworkManager() {};

    // functions
    static void cookOp(enzo::nt::OpId opId);
    static std::vector<enzo::nt::OpId> getDependencyGraph(enzo::nt::OpId opId);

    // variables
    // store for geometry operators
    static std::unordered_map<enzo::nt::OpId, std::unique_ptr<enzo::nt::GeometryOperator>> gopStore_;
    // the highest operator id currently stored
    inline static enzo::nt::OpId maxOpId_=0;
    // operator selected for displaying in the viewport
    inline static std::optional<OpId> displayOp_=std::nullopt;
signals:
    void updateDisplay(enzo::geo::Geometry& geometry);

};
}
