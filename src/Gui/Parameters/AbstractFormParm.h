#include "Engine/Parameter/Parameter.h"
#include <QWidget>
#include <QHBoxLayout>
#include <memory>
#include <qtmetamacros.h>

namespace enzo::ui
{

class AbstractFormParm
: public QWidget
{
    Q_OBJECT
public:
    AbstractFormParm(std::weak_ptr<prm::Parameter> parameter);

protected Q_SLOTS:
    void changeValue(bt::floatT value, unsigned int index=0);

private:
    QHBoxLayout* mainLayout_;
    std::weak_ptr<prm::Parameter> parameter_;

};

}
