#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include <QtWidgets>
#include <QNetworkDatagram>
#include <QUdpSocket>
#include <QMessageBox>
#include <QHostAddress>
#include <QString>

class UdpClient : public QWidget
{
    Q_OBJECT
private:
    int own_port = 5556;
    int send_port = 5555;
    QString IP_own = "127.0.0.1";
    QString IP_send = "127.0.0.1";
    QUdpSocket *UDPSocket;

    QLineEdit* pLine_edit_own_port;
    QLineEdit* pLine_edit_send_port;
    QTextEdit* pMassages_text;
    QLineEdit* pMassage;

public:
    UdpClient(QWidget* parent = 0);
    ~UdpClient();
    void addMassageText(QString str = "");
    //void setOwnPort(int new_own_port = 0);
    //void setSendPort(int new_own_port = 0);

public slots:
    void SendBtnClicked();
    void dataReceived();
    void clearMassageText();
    void setOwnAddress();
    void setSendAddress();
};

#endif