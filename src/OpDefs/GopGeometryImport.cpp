#include "OpDefs/GopGeometryImport.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include <cstdio>
#include <oneapi/tbb/parallel_for.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>

GopGeometryImport::GopGeometryImport(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo)
: GeometryOpDef(network, opInfo)
{

}

void GopGeometryImport::cookOp(enzo::op::Context context)
{
    using namespace enzo;

    if(outputRequested(0))
    {
        geo::Geometry geo;

        bt::String filePath = context.evalStringParm("filePath");
        boost::trim(filePath);
        if(filePath.size()<4)
        {
            throwError("file path too small");
            setOutputGeometry(0, geo);
            return;
        }

        std::string fileExt = filePath.substr(filePath.size()-4, filePath.size());

        if(fileExt!=".obj")
        {
            throwError("File path not accepted: " + fileExt);
            setOutputGeometry(0, geo);
            return;
        }


        auto PAttr = geo.getAttribByName(ga::AttrOwner::POINT, "P");
        ga::AttributeHandleVector3 PAttrHandle(PAttr);

        auto pointAttr = geo.getAttribByName(ga::AttrOwner::VERTEX, "point");
        ga::AttributeHandleInt pointAttrHandle(pointAttr);

        auto vertexCountAttr = geo.getAttribByName(ga::AttrOwner::PRIMITIVE, "vertexCount");
        ga::AttributeHandleInt vertexCountHandle(vertexCountAttr);

        std::ifstream file(filePath);
        if(!file.is_open())
        {
            std::cerr << "Failed to open file " << filePath << "\n";
            setOutputGeometry(0, geo);
            return;
        }

        std::string line;
        while(std::getline(file, line))
        {
            if(line.size()==0)
            {
                continue;
            }

            char firstChar = line[0];
            if(firstChar=='v')
            {
                std::vector<std::string> result;
                boost::split(result, line, isspace);
                if(result.size()!=4)
                {
                    continue;

                }
                const bt::Vector3 pointPos = {std::stod(result[1]), std::stod(result[2]), std::stod(result[3])};
                PAttrHandle.addValue(pointPos);
            }
            else if(firstChar=='f' || firstChar=='l')
            {
                std::vector<std::string> result;
                boost::split(result, line, isspace);
                if(result.size()<3)
                {
                    continue;

                }


                // set vertex attributes
                for(int i=1; i<result.size(); ++i)
                {
                    const int primNum = std::stoi(result[i]);
                    pointAttrHandle.addValue(primNum-1);
                }

                // set face attribute
                vertexCountHandle.addValue(result.size()-1);

            }
        }
        


        // scale
        const float scale = context.evalFloatParm("size");
        for(int i=0; i<PAttrHandle.getSize(); ++i)
        {
            enzo::bt::Vector3 pointPos = PAttrHandle.getValue(i);
            pointPos*=scale;
            PAttrHandle.setValue(i, pointPos);
        }
        // ----

        // set output geometry
        setOutputGeometry(0, geo);
    }

}

enzo::prm::Template GopGeometryImport::parameterList[] =
{
    enzo::prm::Template(enzo::prm::Type::STRING, "filePath"),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "size", enzo::prm::Default(1)),
    enzo::prm::Terminator
};
