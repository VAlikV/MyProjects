#include "main_window.hpp"

MainWindow::MainWindow(QWidget* parent):
QWidget(parent)
{
    layoutSetup();
    connectionSetup();
    refreshPorts();
}

MainWindow::~MainWindow()
{
    if (serial_open_flag_){
        serial_->close();
    }
}

void MainWindow::layoutSetup()
{   
    QVBoxLayout* main_layout = new QVBoxLayout();
    QHBoxLayout* up_layout = new QHBoxLayout();
    //QHBoxLayout* up_layout = new QHBoxLayout();
    QVBoxLayout* left_layout = new QVBoxLayout();
    QGridLayout* setup_layout = new QGridLayout();
    QHBoxLayout* button_layout = new QHBoxLayout();
    QHBoxLayout* write_layout = new QHBoxLayout();

    QLabel* label = new QLabel("Available ports: ");
    ports_combo_box_ = new QComboBox();
    ports_combo_box_->setMaximumWidth(100);

    QLabel* label1 = new QLabel("Bit rate: ");
    speed_combo_box_ = new QComboBox();
    speed_combo_box_->setMaximumWidth(100);

    QLabel* label2 = new QLabel("Data bits: ");
    data_combo_box_ = new QComboBox();
    data_combo_box_->setMaximumWidth(100);

    QLabel* label3 = new QLabel("Set parity: ");
    parity_combo_box_ = new QComboBox();
    parity_combo_box_->setMaximumWidth(100);

    QLabel* label4 = new QLabel("Stop bit: ");
    stopbit_combo_box_ = new QComboBox();
    stopbit_combo_box_->setMaximumWidth(100);

    QLabel* label5 = new QLabel("Flow control: ");
    flowcontrol_combo_box_ = new QComboBox();
    flowcontrol_combo_box_->setMaximumWidth(100);

    QStringList speed;
    speed << "300" << "1200" << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" << "74880" << "115200" << "230400" << "250000" << "500000" << "1000000" << "2000000";
    speed_combo_box_->addItems(speed);
    speed_combo_box_->setCurrentIndex(4);

    open_port_button_ = new QPushButton("Open");
    open_port_button_->setMaximumWidth(70);
    refresh_port_button_ = new QPushButton("Refresh");
    refresh_port_button_->setMaximumWidth(70);
    close_port_button_ = new QPushButton("Close");
    close_port_button_->setMaximumWidth(70);

    messages_ = new QTextEdit();
    messages_->setReadOnly(true);

    clear_text_button_ = new QPushButton("Clear");
    clear_text_button_->setMaximumWidth(70);
    
    write_message_ = new QLineEdit();
    send_button_ = new QPushButton("Send");

    setup_layout->addWidget(label,0,0);
    setup_layout->addWidget(ports_combo_box_,0,1);

    setup_layout->addWidget(label1,1,0);
    setup_layout->addWidget(speed_combo_box_,1,1);

    setup_layout->addWidget(label2,2,0);
    setup_layout->addWidget(data_combo_box_,2,1);

    setup_layout->addWidget(label3,3,0);
    setup_layout->addWidget(parity_combo_box_,3,1);

    setup_layout->addWidget(label4,4,0);
    setup_layout->addWidget(stopbit_combo_box_,4,1);

    setup_layout->addWidget(label5,5,0);
    setup_layout->addWidget(flowcontrol_combo_box_,5,1);
    QWidget *controlsRestrictorWidget = new QWidget();
    controlsRestrictorWidget->setLayout(setup_layout);
    controlsRestrictorWidget->setFixedWidth(230);

    button_layout->addWidget(open_port_button_);
    button_layout->addWidget(refresh_port_button_);
    button_layout->addWidget(close_port_button_);
    button_layout->setAlignment(Qt::AlignLeft);

    write_layout->addWidget(write_message_);
    write_layout->addWidget(send_button_);
    write_layout->addWidget(clear_text_button_);

    left_layout->addWidget(controlsRestrictorWidget);
    left_layout->addLayout(button_layout);
    left_layout->addStretch(1);
    //left_layout->addLayout(write_layout);

    up_layout->addLayout(left_layout);
    up_layout->addWidget(messages_);

    main_layout->addLayout(up_layout);
    main_layout->addLayout(write_layout);
    
    this->setLayout(main_layout);

    serial_ = new QSerialPort();
}

void MainWindow::connectionSetup()
{
    connect(open_port_button_, SIGNAL(clicked()), this, SLOT(openPort()));
    connect(refresh_port_button_, SIGNAL(clicked()), this, SLOT(refreshPorts()));
    connect(close_port_button_, SIGNAL(clicked()), this, SLOT(closePort()));
    connect(clear_text_button_, SIGNAL(clicked()), this, SLOT(clearText()));
    connect(speed_combo_box_, SIGNAL(currentTextChanged()), this, SLOT(setSpeed()));
}

// -------------------------------------------------------------- Слоты

void MainWindow::refreshPorts()
{
    ports_combo_box_->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        QSerialPort port;
        port.setPort(info);
        if (port.open(QIODevice::ReadWrite)){
            ports_combo_box_->addItem(info.portName());
        }
    }
}

void MainWindow::openPort()
{
    if (ports_combo_box_->count() != 0){
        serial_->setPortName(ports_combo_box_->currentText());
        serial_->setBaudRate((speed_combo_box_->currentText()).toUInt());
        serial_->setDataBits(QSerialPort::Data8);
        serial_->setParity(QSerialPort::NoParity);
        serial_->setStopBits(QSerialPort::OneStop);
        serial_->setFlowControl(QSerialPort::NoFlowControl);
        serial_->open(QIODevice::ReadWrite);
        serial_open_flag_ = true;

        connect(serial_, SIGNAL(readyRead()), this, SLOT(serialRecieve()));

        ports_combo_box_->setEnabled(false);
        speed_combo_box_->setEnabled(false);
        data_combo_box_->setEnabled(false);
        parity_combo_box_->setEnabled(false);
        stopbit_combo_box_->setEnabled(false);
        flowcontrol_combo_box_->setEnabled(false);
        send_button_->setEnabled(false);
        open_port_button_->setEnabled(false);
        refresh_port_button_->setEnabled(false);
    }
}

void MainWindow::closePort()
{
    if (serial_open_flag_){
        serial_->close();
        ports_combo_box_->setEnabled(true);
        speed_combo_box_->setEnabled(true);
        data_combo_box_->setEnabled(true);
        parity_combo_box_->setEnabled(true);
        stopbit_combo_box_->setEnabled(true);
        flowcontrol_combo_box_->setEnabled(true);
        send_button_->setEnabled(true);
        open_port_button_->setEnabled(true);
        refresh_port_button_->setEnabled(true);
    }
}

void MainWindow::setSpeed()
{
    serial_->setBaudRate((speed_combo_box_->currentText()).toUInt());
}

void MainWindow::clearText()
{
    messages_->clear();
}

void MainWindow::serialRecieve(){
    data = serial_->readAll();
    messages_->insertPlainText(data);
}