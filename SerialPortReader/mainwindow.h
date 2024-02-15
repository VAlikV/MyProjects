#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Refresh();

private slots:
    void serialRecieve();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    bool serial_open_flag = false;
    QVector<double> x;
    QVector<QVector<double>> y;

};
#endif // MAINWINDOW_H
