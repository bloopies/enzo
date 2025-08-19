#pragma once

#include "Engine/Types.h"
#include <boost/signals2.hpp>

namespace enzo::nt
{
class GeometryOperator;
class GeometryConnection
{
public:
    // input and output are in relation to data flow
    // the input node is the node the data flows from
    // the output node is the node the data flows to
    GeometryConnection(enzo::nt::OpId inputOpId, unsigned int inputIndex, enzo::nt::OpId outputOpId, unsigned int outputIndex);
    
    enzo::nt::OpId getInputOpId() const;
    enzo::nt::OpId getOutputOpId() const;
    unsigned int getInputIndex() const;
    unsigned int getOutputIndex() const;
    friend std::ostream& operator<<(std::ostream& os, const GeometryConnection& p)
    {
        return os << p.inputOperatorId_ << ":" << p.inputIndex_ << " -> " << p.outputOperatorId_ << ":" << p.outputIndex_ << "\n";
    }

    boost::signals2::signal<void ()> removed;
    void remove();
    // bool isValid();
private:
    enzo::nt::OpId inputOperatorId_;
    enzo::nt::OpId outputOperatorId_;
    unsigned int inputIndex_;
    unsigned int outputIndex_;
};
}
