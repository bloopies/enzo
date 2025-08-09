#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Types.h"
#include <icecream.hpp>


GeometrySpreadsheetModel::GeometrySpreadsheetModel(const QStringList &strings, QObject *parent)
: QAbstractListModel(parent), stringList(strings)
{

}

void GeometrySpreadsheetModel::selectionChanged(enzo::nt::OpId opId)
{
    beginResetModel();
    enzo::nt::NetworkManager& nm = enzo::nt::nm();
    opId_ = opId;
    IC();
    geometry_ = nm.getGeoOperator(opId).getOutputGeo(0);
    endResetModel();
}

int GeometrySpreadsheetModel::rowCount(const QModelIndex &parent) const
{
    return geometry_.getNumPoints();
}

QVariant GeometrySpreadsheetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= geometry_.getNumPoints())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        std::cout << geometry_.getPointPos(index.row()).x() << "\n";
        return geometry_.getPointPos(index.row()).x();
    }
    else
    {
        return QVariant();
    }
}

QVariant GeometrySpreadsheetModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QStringLiteral("Column %1").arg(section);
    else
        return QStringLiteral("Row %1").arg(section);
}
