#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct h {
    int h;
    int g;
    QString text;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenPort_clicked();
    void on_btnSend_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void readData();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_8_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *_serialPort;
    struct h ip;

    // Variables to store received data
    int receivedH;
    int receivedG;
    QString receivedText;
    void loadPorts();
    void sendData();
    QByteArray serializeStruct(const h& data);
    h deserializeStruct(const QByteArray& data);
};
#endif // MAINWINDOW_H
