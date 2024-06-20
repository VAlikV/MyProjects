#include "UDPclient.hpp"
#include <QDebug>

UdpClient::UdpClient(QWidget* parent)
    : QWidget(parent)
{
    // Создание лейаутов
    QVBoxLayout* pVLay_main = new QVBoxLayout;
    QHBoxLayout* pHLay_first_line = new QHBoxLayout;
    QHBoxLayout* pHLay_second_line = new QHBoxLayout;
    QHBoxLayout* pHLay_last_line = new QHBoxLayout;

    // Обвязка для собственного порта
    QLabel* lbl_own_port = new QLabel("Own port: ");
    pLine_edit_own_port = new QLineEdit;
    //pLine_edit_own_port->setMaximumSize(50,20);
    //pLine_edit_own_port->setValidator( new QIntValidator(0, 9999, this) );
    pLine_edit_own_port->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    // Обвязка для ответного порта
    QLabel* lbl_send_port = new QLabel("Sending port: ");
    pLine_edit_send_port = new QLineEdit;
    //pLine_edit_send_port->setMaximumSize(50,20);
    //pLine_edit_send_port->setValidator( new QIntValidator(0, 9999, this) );
    pLine_edit_send_port->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    // Окно вывода сообщений
    pMassages_text = new QTextEdit;
    pMassages_text->setReadOnly(true);

    // Сообшение
    pMassage = new QLineEdit;
    QPushButton* pSend_massage_button = new QPushButton("Send");

    // Загрузка в лейауты
    pHLay_first_line->setSpacing(15);
    pHLay_first_line->addWidget(lbl_own_port);
    pHLay_first_line->addWidget(pLine_edit_own_port);

    pHLay_second_line->setSpacing(15);
    pHLay_second_line->addWidget(lbl_send_port);
    pHLay_second_line->addWidget(pLine_edit_send_port);

    pHLay_last_line->setSpacing(15);
    pHLay_last_line->addWidget(pMassage);
    pHLay_last_line->addWidget(pSend_massage_button);

    pVLay_main->setSpacing(10);
    pVLay_main->addLayout(pHLay_first_line);
    pVLay_main->addLayout(pHLay_second_line);
    pVLay_main->addWidget(pMassages_text);
    pVLay_main->addLayout(pHLay_last_line);

    this->setLayout(pVLay_main);

    this->addMassageText("Hello! 1");
    this->addMassageText("Hello! 2");
    this->addMassageText("Hello! 3");

    UDPSocket = new QUdpSocket(this);       // Создаем QUdpSocket

    bool result = UDPSocket->bind(QHostAddress(IP_own),own_port);    // Привязать порт
    if(!result)
    {
        QMessageBox::information(this,"error","UDP socket create error!");
        return;
    }

    pLine_edit_own_port->setText(IP_own + ":" + QString::number(own_port));
    pLine_edit_send_port->setText(IP_send + ":" + QString::number(send_port));   

    connect(UDPSocket,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(pSend_massage_button, SIGNAL(clicked()), this, SLOT(SendBtnClicked()));
    connect(pLine_edit_own_port, SIGNAL(editingFinished()), this, SLOT(setOwnAddress()));
    connect(pLine_edit_send_port, SIGNAL(editingFinished()), this, SLOT(setSendAddress()));
}


UdpClient::~UdpClient()
{
    close();
}

void UdpClient::dataReceived()
{
    while(UDPSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(UDPSocket->pendingDatagramSize());
        UDPSocket->readDatagram(datagram.data(),datagram.size());
        QString msg = datagram.data();
        this->addMassageText(msg);
    }
}

void UdpClient::addMassageText(QString str)
{
    pMassages_text->append(str);
}

void UdpClient::clearMassageText()
{
    pMassages_text->clear();
}

/*
void UdpClient::setOwnPort(int new_own_port)
{
    this->own_port = new_own_port;
    bool result = UDPSocket->bind(own_port);    // Привязать порт
    if(!result)
    {
        QMessageBox::information(this,"error","UDP socket create error!");
        return;
    }
}

void UdpClient::setSendPort(int new_send_port)
{
    this->send_port = new_send_port;
}
*/

void UdpClient::SendBtnClicked()
{    
    UDPSocket->writeDatagram(pMassage->text().toUtf8(),QHostAddress(IP_send), send_port);
}

void UdpClient::setOwnAddress()
{
    QStringList adr;
    adr = pLine_edit_own_port->text().split(":");
    IP_own = adr[0];
    own_port = adr[1].toInt();

    qDebug() << IP_own << own_port;

    UDPSocket->close();
	UDPSocket->abort();

    bool result = UDPSocket->bind(QHostAddress(IP_own),own_port);    // Привязать порт
    if(!result)
    {
        QMessageBox::information(this,"error","UDP socket REcreate error!");
        return;
    }
}

void UdpClient::setSendAddress()
{
    QStringList adr;
    adr = pLine_edit_send_port->text().split(':');
    IP_send = adr[0];
    send_port = adr[1].toInt();
    
    qDebug() << IP_send << send_port;
}