#include <catch2/catch_test_macros.hpp>
#include "Engine/Operator/Attribute.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
// #include "Engine/Operator/Primitive.h"


TEST_CASE("attrHandleInt")
{
    using namespace enzo;

    ga::Attribute myAttrib("test", ga::AttrType::intT);
    ga::AttributeHandleInt myHandle(myAttrib);
    myHandle.addValue(5);
    myHandle.addValue(6);
    REQUIRE(myHandle.getValue(0)==5);
    REQUIRE(myHandle.getValue(1)==6);
}

TEST_CASE("attrHandleFloat")
{
    using namespace enzo;

    ga::Attribute myAttrib("test", ga::AttrType::floatT);
    ga::AttributeHandleFloat myHandle(myAttrib);
    myHandle.addValue(5.3f);
    myHandle.addValue(6.9f);
    REQUIRE(myHandle.getValue(0)==5.3f);
    REQUIRE(myHandle.getValue(1)==6.9f);
}

TEST_CASE("Attribute Type")
{
    using namespace enzo;
    REQUIRE(ga::AttributeType::intT ==      ga::AttributeType::intT);
    REQUIRE(ga::AttributeType::intT !=      ga::AttributeType::floatT);
    REQUIRE(ga::AttributeType::floatT ==    ga::AttributeType::floatT);
    REQUIRE(ga::AttributeType::listT ==     ga::AttributeType::listT);
    REQUIRE(ga::AttributeType::vectorT ==   ga::AttributeType::vectorT);

}
