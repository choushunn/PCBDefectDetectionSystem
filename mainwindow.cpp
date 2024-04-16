#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cv::VideoCapture *capture = new cv::VideoCapture(0
                                                     );
    if (!capture->isOpened())
    {
        qDebug() << "无法打开摄像头";
    }
    // 创建一个定时器，用于定时更新图像
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        cv::Mat frame;
        *capture >> frame;  // 从摄像头读取帧
        QImage qImage(frame.data, frame.cols, frame.rows, QImage::Format_RGB888);
        QPixmap pixmap = QPixmap::fromImage(qImage.rgbSwapped());
        ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
    });
    timer->start(30);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete capture;  // 释放VideoCapture对象
}
