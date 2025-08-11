#include "OpDefs/GopGrid.h"
#include "Engine/Types.h"
#include <cmath>
#include <cstdio>
#include <oneapi/tbb/parallel_for.h>
#include <fstream>
#include <string>
#include <boost/algorithm/string.hpp>

GopGrid::GopGrid(enzo::nt::NetworkManager* network, enzo::op::OpInfo opInfo)
: GeometryOpDef(network, opInfo)
{

}

void GopGrid::cookOp(enzo::op::Context context)
{
    using namespace enzo;

    if(outputRequested(0))
    {
        geo::Geometry geo;
        bt::floatT width = context.evalFloatParm("width");
        bt::floatT height = context.evalFloatParm("height");

        const bt::intT columns = context.evalFloatParm("columns");
        const bt::intT rows = context.evalFloatParm("rows");
        if(columns==0 || rows==0)
        {
            setOutputGeometry(0, geo);
            return;
        }
        
        const bt::floatT centerOffsetX = (columns-1)*width/2.0;
        const bt::floatT centerOffsetY = (rows-1)*height/2.0;

        for(int i=0;i<columns;i++)
        {
            for(int j=0;j<rows;++j)
            {
                geo.addPoint(bt::Vector3(i*width-centerOffsetX, sin(i+j), j*height-centerOffsetY));
            }
        }

        for(int i=0;i<std::floor((columns-1)*(rows)-1);i++)
        {
            const int endOffset = (i+1)%rows==0;
            const ga::Offset startPt = i+endOffset; 
            geo.addFace(startPt,startPt+rows,startPt+rows+1,startPt+1);
        }


        setOutputGeometry(0, geo);
    }

}

enzo::prm::Template GopGrid::parameterList[] =
{
    enzo::prm::Template(enzo::prm::Type::FLOAT, "width", enzo::prm::Default(1)),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "height", enzo::prm::Default(1)),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "rows", enzo::prm::Default(10)),
    enzo::prm::Template(enzo::prm::Type::FLOAT, "columns", enzo::prm::Default(10)),
    enzo::prm::Terminator
};
