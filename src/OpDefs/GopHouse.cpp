#include "OpDefs/GopHouse.h"
#include "Engine/Operator/AttributeHandle.h"
#include <oneapi/tbb/parallel_for.h>

GOP_house::GOP_house(enzo::nt::OpId opId)
: enzo::nt::GeometryOpDef(opId)
{

}

void GOP_house::cookOp(enzo::op::Context context)
{
    using namespace enzo;
    // std::cout << "COOKING\n";

    if(outputRequested(0))
    {
        // copy input geometry
        geo::Geometry geo = context.cloneInputGeo(0);

        // ----
        // create geometry start
        // ----
        auto PAttr = geo.getAttribByName(ga::AttrOwner::POINT, "P");
        ga::AttributeHandleVector3 PAttrHandle(PAttr);
        int startPt = PAttrHandle.getSize();
        std::vector<bt::Vector3> pts = {
            {-1,-1,-1},{1,-1,-1},{1,-1,1},{-1,-1,1},
            {-1,1,-1},{1,1,-1},{1,1,1},{-1,1,1},
            {0,2,-1},{0,2,1}
        };
        for (auto& p : pts) PAttrHandle.addValue(p);

        auto pointAttr = geo.getAttribByName(ga::AttrOwner::VERTEX, "point");
        ga::AttributeHandleInt pointAttrHandle(pointAttr);
        std::vector<std::vector<int>> faces = {
            {3,2,6,9,7},{0,1,5,8,4},{0,3,7,4},{1,2,6,5},
            {0,1,2,3},{4,7,9},{4,9,8},{5,6,9},{5,9,8}
        };
        for (auto& f : faces) for (int i : f) pointAttrHandle.addValue(startPt + i);

        auto vertexCountAttr = geo.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
        ga::AttributeHandleInt vertexCountHandle(vertexCountAttr);
        for (auto& f : faces) vertexCountHandle.addValue(f.size());

        // --------

        for(int i=0; i<PAttrHandle.getAllValues().size(); ++i)
        {
            enzo::bt::Vector3 vector = PAttrHandle.getValue(i);
            vector.x()+=2.5;
            PAttrHandle.setValue(i, vector);
        }
        // ----

        constexpr int N = 10000;
        std::vector<double> results(N);

        oneapi::tbb::parallel_for(0, N, [&](int i) {
            double val = 0;
            for (int j = 0; j < 100; ++j) {
                val += std::sin(i + j);
            }
            results[i] = val;
        });


        // set output geometry
        setOutputGeometry(0, geo);
    }

    // if(outputRequested(1))
    // {
    //     // create new geometry
    //     const geo::Geometry& geo1 = getInputGeoView(0);
    //     geo::Geometry geo2;

    //     setOutputGeometry(1, geo2);
    // }
}

enzo::prm::Template GOP_house::parameterList[] =
{
    enzo::prm::Template(enzo::prm::Type::FLOAT, "Size"),
    enzo::prm::Terminator
};
