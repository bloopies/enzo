#pragma once
#include <memory>
#include <stdexcept>
#include <string>
#include <optional>
#include <vector>
#include "Engine/Operator/Attribute.h"
#include "Engine/Types.h"

#include <iostream>


namespace enzo::ga{

template <typename T>
class AttributeHandle
{
public:
    ga::AttributeType type_;

    AttributeHandle(std::shared_ptr<Attribute> attribute)
    {
        type_ = attribute->getType();
        // get attribute data pointer
        // TODO: check types match
        // TODO: add the other types

        // int
        if constexpr (std::is_same<int, T>::value)
        {
            data_=attribute->intStore_;
        }

        // float
        else if constexpr (std::is_same<float, T>::value)
        {
            data_=attribute->floatStore_;
        }

        // vector 3
        else if constexpr (std::is_same<enzo::bt::Vector3, T>::value)
        {
            data_=attribute->vector3Store_;
        }
        else
        {
                throw std::runtime_error("Type " + std::to_string(static_cast<int>(type_)) + " was not properly accounted for");
        }

    }
    void addValue(T value)
    {
        // TODO:make this private (primitive friend classes only)
        data_->push_back(value);
    }

    std::vector<T> getAllValues() const
    {
        return *data_;
    }

    T getValue(size_t pos) const
    {
        // TODO:protect against invalid positions
        // TODO: cast types
        return data_->at(pos);
    }

    void setValue(size_t pos, const T& value)
    {
        // TODO:protect against invalid positions
        // TODO: cast types
        (*data_)[pos] = value;
    }
    std::string getName() const
    {
        return name_;
    }



private:
    // private attributes are attributes that are hidden from the user
    // for internal use
    bool private_=false;
    // hidden attributes are user accessible attributes that the user may
    // or may want to use
    bool hidden_=false;
    // allows the user to read the attributeHandle but not modify it
    bool readOnly_=false;

    std::string name_="";

    std::shared_ptr<std::vector<T>> data_;

    // int typeID_;

};

using AttributeHandleInt = AttributeHandle<int>;
using AttributeHandleFloat = AttributeHandle<float>;
using AttributeHandleVector3 = AttributeHandle<enzo::bt::Vector3>;

}
