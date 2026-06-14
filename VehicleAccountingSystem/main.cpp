#include "VehicleAccountingSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    VehicleAccountingSystem window;
    window.show();
    return app.exec();
}
