#include "Gui/GeometrySpreadsheetPanel/GeometrySpreadsheetModel.h"
#include "Engine/Network/NetworkManager.h"
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
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
    geometry_ = geometry;

    // get sizes
    const auto attribCount = geometry_.getNumAttributes(attributeOwner_);

    attribSizes_.clear();
    attribSizes_.reserve(attribCount);

    for(size_t i=0; i<attribCount; ++i)
    {
        if(auto attrib = geometry_.getAttributeByIndex(attributeOwner_, i).lock())
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
    switch(attributeOwner_)
    {
        case enzo::ga::AttributeOwner::POINT:
        {
            return geometry_.getNumPoints();
        }
        case enzo::ga::AttributeOwner::VERTEX:
        {
            return geometry_.getNumVerts();
        }
        case enzo::ga::AttributeOwner::PRIMITIVE:
        {
            return geometry_.getNumPrims();
        }
        case enzo::ga::AttributeOwner::GLOBAL:
        {
            return 1;
        }

    }
    return 1;
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

    // TODO: reimplement check
    // if (index.row() >= geometry_.getNumPoints())
    // {
    //     return QVariant();
    // }

    if (role == Qt::DisplayRole)
    {

        // std::cout << geometry_.getPointPos(index.row()).x() << "\n";
        int attributeIndex = indexFromSection(index.column());
        if(std::shared_ptr<const enzo::ga::Attribute> attrib = geometry_.getAttributeByIndex(attributeOwner_, attributeIndex).lock())
        {
            const unsigned int valueIndex = index.column()-attributeIndex;
            using namespace enzo::ga;

            switch(attrib->getType())
            {
                case(AttributeType::intT):
                {
                    const auto attribHandle = enzo::ga::AttributeHandleRO<enzo::bt::intT>(attrib);
                    return static_cast<float>(attribHandle.getValue(index.row()));
                }
                case(AttributeType::floatT):
                {
                    const auto attribHandle = enzo::ga::AttributeHandleRO<enzo::bt::floatT>(attrib);
                    return attribHandle.getValue(index.row());
                }
                case(AttributeType::boolT):
                {
                    const auto attribHandle = enzo::ga::AttributeHandleRO<enzo::bt::boolT>(attrib);
                    return attribHandle.getValue(index.row()) ? "true" : "false";
                }
                case(AttributeType::vectorT):
                {
                    const auto attribHandle = enzo::ga::AttributeHandleRO<enzo::bt::Vector3>(attrib);
                    return attribHandle.getValue(index.row())[valueIndex];
                }
                default:
                {
                    return "Failed";
                    break;
                }

            }
        }
        else
        {
            throw std::runtime_error("Couldn't lock attribute");
        }
        // return geometry_.getPointPos(index.row()).x();
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
        if(auto attrib = geometry_.getAttributeByIndex(attributeOwner_, indexFromSection(section)).lock())
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
