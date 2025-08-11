#include "Engine/Parameter/Template.h"
#include "Engine/Parameter/Default.h"
#include "Engine/Parameter/Range.h"
#include "Engine/Parameter/Type.h"

enzo::prm::Template::Template(enzo::prm::Type type, const char* name)
: Template(type, name, prm::Default())
{

}

enzo::prm::Template::Template(enzo::prm::Type type, const char* name, unsigned int vectorSize)
: Template(type, name, prm::Default(), vectorSize)
{

}

enzo::prm::Template::Template(enzo::prm::Type type, const char* name, std::vector<prm::Default> defaults, unsigned int vectorSize, std::vector<prm::Range> ranges)
: type_{type}, name_{name}, defaults_{defaults}, vectorSize_(vectorSize)
{
    ranges.resize(vectorSize);
    ranges_ = ranges;
}

enzo::prm::Template::Template(enzo::prm::Type type, const char* name, prm::Default theDefault, unsigned int vectorSize, Range range)
: type_{type}, name_{name}, vectorSize_(vectorSize)
{
    defaults_.push_back(theDefault);
    ranges_.push_back(range);
}

enzo::prm::Template::Template()
{
    
}

bool enzo::prm::Template::isValid() const
{
    return name_!=nullptr;

}

const enzo::prm::Type enzo::prm::Template::getType() const
{
    return type_;
}

const unsigned int enzo::prm::Template::getSize() const
{
    return vectorSize_;
}



const enzo::prm::Default enzo::prm::Template::getDefault(unsigned int index) const
{
    return defaults_.at(index);
}

const enzo::prm::Range& enzo::prm::Template::getRange(unsigned int index) const
{
    return ranges_.at(index);
}

const unsigned int enzo::prm::Template::getNumDefaults() const
{
    return defaults_.size();
}


const char* enzo::prm::Template::getName() const
{
    return name_;
}

