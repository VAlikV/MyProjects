#ifndef MAIN_MINDOW_HPP
#define MAIN_MINDOW_HPP

#include <QtWidgets>
#include <QtSerialPort>

class MainWindow: public QWidget
{
Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QSerialPort* serial_;
    bool serial_open_flag_ = false;

    QString data;
    
    QComboBox* ports_combo_box_;
    QComboBox* speed_combo_box_;
    QComboBox* data_combo_box_;
    QComboBox* parity_combo_box_;
    QComboBox* stopbit_combo_box_;
    QComboBox* flowcontrol_combo_box_;

    QPushButton* open_port_button_;
    QPushButton* refresh_port_button_;
    QPushButton* close_port_button_;

    QTextEdit* messages_;
    QPushButton* clear_text_button_;

    QLineEdit* write_message_;
    QPushButton* send_button_;

    void layoutSetup();
    void connectionSetup();

private slots:
    void refreshPorts();
    void openPort();
    void closePort();
    void sendMessage();
    void clearText();
    void serialRecieve();
};

#endif