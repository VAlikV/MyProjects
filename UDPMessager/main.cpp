#include <QApplication>
#include <QtWidgets>
#include "UDPclient.hpp"

int main(int argc, char **argv){
    QApplication app(argc, argv);

    UdpClient client;
    
    client.setWindowTitle("Massager");
    client.resize(250,300);
    client.show();

    return app.exec();
}