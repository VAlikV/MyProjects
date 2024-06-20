#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);

    Refresh();

    //QVector<double> x(360), y(360);
    x = QVector<double>(360);
    y = QVector<QVector<double>>(8);

    for (int i = 0; i < 8; ++i){
        y[i].resize(360);
    }

    for (int i=0; i<360; ++i){
        x[i] = i;
    }

    // Инициализация графиков
    {
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y[0]);

    ui->widget->xAxis->setLabel("Время");
    ui->widget->yAxis->setLabel("Напряжение");
    //ui->widget->plotLayout()->insertRow(0);
    //ui->widget->plotLayout()->addElement(0, 0, new QCPTextElement(ui->widget, "Way too many graphs in one plot", QFont("sans", 8, QFont::Bold)));

    ui->widget->xAxis->setRange(360, 0);
    ui->widget->yAxis->setRange(-1, 6);
    ui->widget->replot();
    // -------------------------------------------
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(x, y[1]);

    ui->widget_2->xAxis->setLabel("Время");
    ui->widget_2->yAxis->setLabel("Напряжение");

    ui->widget_2->xAxis->setRange(360, 0);
    ui->widget_2->yAxis->setRange(-1, 6);
    ui->widget_2->replot();
    // -------------------------------------------
    ui->widget_3->addGraph();
    ui->widget_3->graph(0)->setData(x, y[2]);

    ui->widget_3->xAxis->setLabel("Время");
    ui->widget_3->yAxis->setLabel("Напряжение");

    ui->widget_3->xAxis->setRange(360, 0);
    ui->widget_3->yAxis->setRange(-1, 6);
    ui->widget_3->replot();
    // -------------------------------------------
    ui->widget_4->addGraph();
    ui->widget_4->graph(0)->setData(x, y[3]);

    ui->widget_4->xAxis->setLabel("Время");
    ui->widget_4->yAxis->setLabel("Напряжение");

    ui->widget_4->xAxis->setRange(360, 0);
    ui->widget_4->yAxis->setRange(-1, 6);
    ui->widget_4->replot();
    // -------------------------------------------
    ui->widget_5->addGraph();
    ui->widget_5->graph(0)->setData(x, y[4]);

    ui->widget_5->xAxis->setLabel("Время");
    ui->widget_5->yAxis->setLabel("Напряжение");

    ui->widget_5->xAxis->setRange(360, 0);
    ui->widget_5->yAxis->setRange(-1, 6);
    ui->widget_5->replot();
    // -------------------------------------------
    ui->widget_6->addGraph();
    ui->widget_6->graph(0)->setData(x, y[5]);

    ui->widget_6->xAxis->setLabel("Время");
    ui->widget_6->yAxis->setLabel("Напряжение");

    ui->widget_6->xAxis->setRange(360, 0);
    ui->widget_6->yAxis->setRange(-1, 6);
    ui->widget_6->replot();
    // -------------------------------------------
    ui->widget_7->addGraph();
    ui->widget_7->graph(0)->setData(x, y[6]);

    ui->widget_7->xAxis->setLabel("Время");
    ui->widget_7->yAxis->setLabel("Напряжение");

    ui->widget_7->xAxis->setRange(360, 0);
    ui->widget_7->yAxis->setRange(-1, 6);
    ui->widget_7->replot();
    // -------------------------------------------
    ui->widget_8->addGraph();
    ui->widget_8->graph(0)->setData(x, y[7]);

    ui->widget_8->xAxis->setLabel("Время");
    ui->widget_8->yAxis->setLabel("Напряжение");

    ui->widget_8->xAxis->setRange(360, 0);
    ui->widget_8->yAxis->setRange(-1, 6);
    ui->widget_8->replot();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    serial->close();
    delete serial;
}

void MainWindow::Refresh(){
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        QSerialPort port;
        port.setPort(info);
        if (port.open(QIODevice::ReadWrite)){
            ui->comboBox->addItem(info.portName());
        }
    }
}

void MainWindow::serialRecieve(){
    QByteArray data;
    data = serial->readAll();
    ui->statusbar->showMessage(QString(data));
}


void MainWindow::on_pushButton_clicked()
{

    serial->setPortName(ui->comboBox->currentText());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadWrite);

    connect(serial, SIGNAL(readyRead()), this, SLOT(serialRecieve()));
}


