#pragma once
#include "Engine/Parameter/Default.h"
#include "Engine/Parameter/Type.h"
#include "Engine/Types.h"

namespace enzo::prm
{

class Template
{
public:
    Template(
        enzo::prm::Type type,
        const char* name
    );
    Template(
        enzo::prm::Type type,
        const char* name,
        unsigned int vectorSize
    );
    Template(
        enzo::prm::Type type,
        const char* name,
        std::vector<prm::Default> defaults,
        unsigned int vectorSize = 1
    );
    Template(
        enzo::prm::Type type,
        const char* name,
        prm::Default theDefault,
        unsigned int vectorSize = 1
    );
    Template();
    const char* getName() const;
    const prm::Default getDefault(unsigned int index=0) const;
    const prm::Type getType() const;
    const unsigned int getSize() const;
    const unsigned int getNumDefaults() const;
    bool isValid() const;
private:
    enzo::prm::Type type_;
    std::vector<prm::Default> defaults_;
    // TODO: make a class that holds token and name
    const char* name_;
    unsigned int vectorSize_;

};

inline enzo::prm::Template Terminator = enzo::prm::Template();

}

