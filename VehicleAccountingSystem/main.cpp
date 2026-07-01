#include "VehicleAccountingSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/VehicleAccountingSystem/resources/icons/app.ico"));
    VehicleAccountingSystem window;
    window.show();
    return app.exec();
}
