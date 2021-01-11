#include <QtWidgets>
#include <QDebug>

#include "grid.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    AAGrid aaView;

    aaView.show();
    return a.exec();
}
