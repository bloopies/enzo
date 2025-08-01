#include "OpDefs/GopGeometryImport.h"
#include "Engine/Operator/AttributeHandle.h"
#include "Engine/Types.h"
#include <cstdio>
#include <oneapi/tbb/parallel_for.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string/split.hpp>

GopGeometryImport::GopGeometryImport(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo)
: GeometryOpDef(network, opInfo)
{

}

void GopGeometryImport::cookOp(enzo::op::Context context)
{
    using namespace enzo;

    if(outputRequested(0))
    {
        std::string filePath = "/home/parker/Downloads/Rat_Placeholder_Polycount_12.obj";

        geo::Geometry geo;

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
                std::cout << "adding vector: " << pointPos.x() << " " << pointPos.y() << " " << pointPos.z() << "\n";
            }
            else if(firstChar=='f')
            {
                std::vector<std::string> result;
                boost::split(result, line, isspace);
                // if(result.size()<3)
                // {
                //     continue;

                // }


                // set vertex attributes
                std::cout << "connecting:";
                for(int i=1; i<result.size(); ++i)
                {
                    const int primNum = std::stoi(result[i]);
                    pointAttrHandle.addValue(primNum-1);
                    std::cout << " " << primNum;
                }
                std::cout << "\n";

                // set face attribute
                std::cout << "face size: " << result.size()-1 << "\n";
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
            std::cout << "adding point: " << pointPos.x() << " " << pointPos.y() << " " << pointPos.z() << "\n";
        }
        for(auto value : pointAttrHandle.getAllValues())
        {
            std::cout << "adding vector: " << value << "\n";
        }
        for(auto value : vertexCountHandle.getAllValues())
        {
            std::cout << "adding face: " << value << "\n";
        }
        // ----

        // set output geometry
        setOutputGeometry(0, geo);
    }

}

enzo::prm::Template GopGeometryImport::parameterList[] =
{
    enzo::prm::Template(enzo::prm::Type::FLOAT, "size", 1),
    enzo::prm::Terminator
};
