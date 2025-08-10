#pragma once

#include <QAbstractListModel>
#include "Engine/Types.h"
#include "Engine/Operator/Geometry.h"

class GeometrySpreadsheetModel : public QAbstractListModel
{
    Q_OBJECT

public:
    GeometrySpreadsheetModel(const QStringList &strings, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    int indexFromSection(unsigned int section) const;

    void geometryChanged(enzo::geo::Geometry& geometry);


private:
    QStringList stringList;
    enzo::nt::OpId opId_;
    enzo::geo::Geometry geometry_;
    std::vector<unsigned int> attribSizes_;
    std::vector<unsigned int> sectionAttribMap_;
    enzo::ga::AttributeOwner attributeOwner_=enzo::ga::AttributeOwner::PRIMITIVE;

};
