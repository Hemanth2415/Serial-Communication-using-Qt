#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _serialPort(nullptr)
    , ip{0, 0, ""}
    , receivedH(0)
    , receivedG(0)
{
    ui->setupUi(this);
    loadPorts();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (_serialPort != nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }
}

void MainWindow::readData()
{
    if (!_serialPort->isOpen())
    {
        QMessageBox::critical(this, "Port Error", "Port is not Opened");
        return;
    }

    QByteArray data = _serialPort->readAll();
    h receivedData = deserializeStruct(data);

    // Store the received values in member variables
    receivedH = receivedData.h;
    receivedG = receivedData.g;
    receivedText = receivedData.text;

    QString receivedDisplayText = QString("h: %1, g: %2, text: %3").arg(receivedH).arg(receivedG).arg(receivedText);
    ui->listWidget->addItem(receivedDisplayText);
}

void MainWindow::loadPorts()
{
    foreach (auto &Port, QSerialPortInfo::availablePorts())
    {
        ui->cmbPorts->addItem(Port.portName());
    }
}

void MainWindow::on_btnOpenPort_clicked()
{
    if (_serialPort != nullptr)
    {
        _serialPort->close();
        delete _serialPort;
    }
    _serialPort = new QSerialPort(this);
    _serialPort->setPortName(ui->cmbPorts->currentText());
    _serialPort->setBaudRate(QSerialPort::Baud9600);
    _serialPort->setDataBits(QSerialPort::Data8);
    _serialPort->setParity(QSerialPort::NoParity);
    _serialPort->setStopBits(QSerialPort::OneStop);
    if (_serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::information(this, "Result", "Port Opened Successfully");
        connect(_serialPort, &QSerialPort::readyRead, this, &MainWindow::readData);
    }
    else
    {
        QMessageBox::critical(this, "Port Error", "Unable to open the Port");
    }
}

void MainWindow::on_btnSend_clicked()
{
    if (!_serialPort->isOpen())
    {
        QMessageBox::critical(this, "Port Error", "Port is not Opened");
        return;
    }

    ip.text = ui->lineEdit->text();
    sendData();
}

void MainWindow::sendData()
{
    QByteArray data = serializeStruct(ip);
    _serialPort->write(data);
}

void MainWindow::on_radioButton_clicked()
{
    ip.h = 1;
    ui->lineEdit->setText("1 and ");
}

void MainWindow::on_radioButton_2_clicked()
{
    ip.g = 2;
    ui->lineEdit->setText("2 and ");
}

QByteArray MainWindow::serializeStruct(const h& data)
{
    QByteArray byteArray;
    QDataStream stream(&byteArray, QIODevice::WriteOnly);
    stream.writeRawData(reinterpret_cast<const char*>(&data.h), sizeof(data.h));
    stream.writeRawData(reinterpret_cast<const char*>(&data.g), sizeof(data.g));
    stream << data.text;
    return byteArray;
}

h MainWindow::deserializeStruct(const QByteArray& data)
{
    h deserializedData;
    QDataStream stream(data);
    stream.readRawData(reinterpret_cast<char*>(&deserializedData.h), sizeof(deserializedData.h));
    stream.readRawData(reinterpret_cast<char*>(&deserializedData.g), sizeof(deserializedData.g));
    stream >> deserializedData.text;
    return deserializedData;
}

void MainWindow::on_radioButton_3_clicked()
{
    ip.h = 3;
    ui->lineEdit->setText("3 and ");
}

void MainWindow::on_radioButton_4_clicked()
{
    ip.h = 4;
    ui->lineEdit->setText("4 and ");
}


void MainWindow::on_radioButton_5_clicked()
{
    ip.h = 11;
    ui->lineEdit->insert("11 are Clicked ");
}


void MainWindow::on_radioButton_6_clicked()
{
    ip.h = 12;
    ui->lineEdit->insert("12 are Clicked ");
}

void MainWindow::on_radioButton_7_clicked()
{
    ip.h = 13;
    ui->lineEdit->insert("13 are Clicked ");
}


void MainWindow::on_radioButton_8_clicked()
{
    ip.h = 14;
    ui->lineEdit->insert("14 are Clicked ");
}

