#include <QWidget>
#include <QHBoxLayout>

namespace enzo::ui
{

class AbstractFormParm
: public QWidget
{
public:
    AbstractFormParm();

private:
    QHBoxLayout* mainLayout_;

};

}
