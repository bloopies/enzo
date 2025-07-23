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

protected slots:
    void changeValue(bt::floatT value);


private:
    QHBoxLayout* mainLayout_;
    std::weak_ptr<prm::Parameter> parameter_;

};

}
