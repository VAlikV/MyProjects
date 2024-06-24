#include <QApplication>
#include <QtWidgets>
#include "main_window/main_window.hpp"

int main(int argc, char **argv){
    QApplication app(argc, argv);

    MainWindow window;

    window.setWindowTitle("Serial Messager");
    window.resize(1000,500);
    window.show();

    return app.exec();
}