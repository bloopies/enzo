#include "Engine/Parameter/Parameter.h"
#include <QWidget>
#include <QHBoxLayout>
#include <memory>

namespace enzo::ui
{

class AbstractFormParm
: public QWidget
{
public:
    AbstractFormParm(std::weak_ptr<prm::Parameter> parameter);

private:
    QHBoxLayout* mainLayout_;

};

}
