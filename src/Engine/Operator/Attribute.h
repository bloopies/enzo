#pragma once
#include <string>
#include <optional>
#include <string_view>
#include <vector>
#include "Engine/Types.h"
#include <memory>


namespace enzo{
    namespace ga{

        template <typename T>
        class AttributeHandle;

        class Attribute
        {
        public:
            Attribute(std::string name, ga::AttributeType type);
            AttributeType getType();
            std::string getName();



            template <typename T>
            friend class AttributeHandle;

        private:
            // private attributes are attributes that are hidden from the user
            // for internal use
            bool private_=false;
            // hidden attributes are user accessible attributes that the user may
            // or may want to use
            bool hidden_=false;
            // allows the user to read the attribute but not modify it
            bool readOnly_=false;

            ga::AttributeType type_;

            std::string name_;

            void* data_;


            // data stores
            std::shared_ptr<std::vector<int>> intStore_;
            std::shared_ptr<std::vector<float>> floatStore_;
        };


    }
}
