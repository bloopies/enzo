#pragma once
#include "Engine/Parameter/Type.h"
#include "Engine/Types.h"

namespace enzo::prm
{

class Template
{
public:
    Template(
        enzo::prm::Type type,
        const char* name,
        // TODO: change default to class that can store multiple types
        bt::floatT theDefault
    );
    Template();
    const char* getName() const;
    const bt::floatT getDefault() const;
    bool isValid() const;
private:
    enzo::prm::Type type_;
    bt::floatT default_;
    // TODO: make a class that holds token and name
    const char* name_;

};

inline enzo::prm::Template Terminator = enzo::prm::Template();

}

