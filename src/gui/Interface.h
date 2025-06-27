#pragma once
#include <QWidget>
#include <QBoxLayout>
#include <QSplitter>
#include <gui/UtilWidgets/Splitter.h>

class EnzoUI
: public QWidget
{
    public:
        EnzoUI(); 
        
    private:
        QVBoxLayout* mainLayout_;
        QVBoxLayout* viewportSplitLayout_;
        Splitter* viewportSplitter_;


};
