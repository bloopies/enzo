#pragma once

#include "Engine/Network/NetworkManager.h"
#include "Engine/Types.h"
namespace enzo::op
{
class Context
{
public:
    Context(enzo::nt::OpId opId, enzo::nt::NetworkManager& networkManager);
private:
    enzo::nt::OpId opId_;
    enzo::nt::NetworkManager& networkManager_;

};
}
