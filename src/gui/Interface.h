#pragma once
#include <QWidget>
#include <QBoxLayout>
#include <QSplitter>

class EnzoUI
: public QWidget
{
    public:
        EnzoUI(); 
        
    private:
        QVBoxLayout* mainLayout_;
        QVBoxLayout* viewportSplitLayout_;
        QSplitter* viewportSplitter_;


};
