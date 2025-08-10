#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/Geometry.h"
#include "Engine/Types.h"
#include <icecream.hpp>
#include <memory>
#include <stdexcept>


GeometrySpreadsheetModel::GeometrySpreadsheetModel(const QStringList &strings, QObject *parent)
: QAbstractListModel(parent), stringList(strings)
{

}

void GeometrySpreadsheetModel::geometryChanged(enzo::geo::Geometry& geometry)
{
    beginResetModel();
    // enzo::nt::NetworkManager& nm = enzo::nt::nm();
    IC();
    geometry_ = geometry;

    // get sizes
    const auto attribCount = geometry_.getNumAttributes(enzo::ga::AttributeOwner::POINT);

    attribSizes_.clear();
    attribSizes_.reserve(attribCount);

    for(size_t i=0; i<attribCount; ++i)
    {
        if(auto attrib = geometry_.getAttributeByIndex(enzo::ga::AttributeOwner::POINT, i).lock())
        {
            const auto size = attrib->getTypeSize();
            attribSizes_.push_back(size);

            for(size_t j=0; j<size; ++j)
            {
                sectionAttribMap_.push_back(i);
            }
        }

    }


    endResetModel();
}

int GeometrySpreadsheetModel::rowCount(const QModelIndex &parent) const
{
    return geometry_.getNumPoints();
}

int GeometrySpreadsheetModel::columnCount(const QModelIndex &parent) const
{

    int columnCount = 0;
    for(auto size : attribSizes_)
    {
        columnCount += size;
    }

    return columnCount;
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

int GeometrySpreadsheetModel::indexFromSection(unsigned int section) const
{
    if(section>=sectionAttribMap_.size())
    {
        throw std::out_of_range("Section is out of range of sectionAttributMap_");
    }
    IC(sectionAttribMap_);
    return sectionAttribMap_[section];
}


QVariant GeometrySpreadsheetModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        if(auto attrib = geometry_.getAttributeByIndex(enzo::ga::AttributeOwner::POINT, indexFromSection(section)).lock())
        {
            return QString::fromStdString(attrib->getName());
        }
        else
        {
            throw std::runtime_error("failed to lock attriubte index");
        }

    }
    else
    {
        return QStringLiteral("Row %1").arg(section);
    }
}
