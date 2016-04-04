#include "mainwindow.h"
#include <QApplication>
#include <cblas.h>

int main(int argc, char *argv[])
{
    openblas_set_num_threads(4);
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
