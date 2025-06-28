#pragma once
#include <stdexcept>
#include <string>
#include <optional>
#include <vector>
#include "Engine/Operator/Attribute.h"

#include <iostream>


namespace enzo::ga{

template <typename T>
class AttributeHandle
{
public:
    ga::AttributeType type_;

    AttributeHandle(Attribute& attribute)
    {
        type_ = attribute.getType();
        // get attribute data pointer
        // TODO: check types match
        // TODO: add the other types
        if constexpr (std::is_same<int, T>::value)
        {
            data_=attribute.intStore_;
        }
        else if constexpr (std::is_same<float, T>::value)
        {
            data_=attribute.floatStore_;
        }
        else
        {
                throw std::runtime_error("Type " + std::to_string(static_cast<int>(type_)) + " was not accounted for");
        }
        // switch(type_)
        // {
        //     case(AttrType::intT):
        //     {
        //         data_=attribute.intStore_;
        //         break;
        //     }
        //     case(AttrType::floatT):
        //     {
        //         data_=attribute.floatStore_;
        //         break;
        //     }
        //     default:
        //         throw std::runtime_error("Type " + std::to_string(static_cast<int>(type_)) + " was not accounted for");

        // }

    }
    void addValue(T value)
    {
        // TODO:make this private (primitive friend classes only)
        data_->push_back(value);
    }
    T getValue(uint pos)
    {
        // TODO:protect against invalid positions
        // TODO: cast types
        return data_->at(pos);
    }
    std::string getName()
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

}
