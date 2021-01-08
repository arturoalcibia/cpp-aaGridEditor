#include <QtWidgets>
#include <QDebug>

#include "view.h"


int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    AAView aaView;

    aaView.show();
    return a.exec();
}
