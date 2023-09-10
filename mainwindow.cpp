#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <chrono>
#include "medianfilter.h"

using namespace cv;
using timeType = decltype(std::chrono::high_resolution_clock::now());
using timer =std::chrono::high_resolution_clock;

MedianFilter medianFilter;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<< "OpenCV version : " << CV_VERSION;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    timeType prevTimePoint;
    Mat myImage;
    namedWindow("FPS Checker");
    VideoCapture cap(0,CAP_DSHOW);

    while ( waitKey(1) != 'q' )
    {
       cap >> myImage;
       if (myImage.empty()) break;
       auto currentTimePoint = timer::now();
       if ( prevTimePoint.time_since_epoch().count() )
       {
           std::chrono::duration<float> duration = currentTimePoint - prevTimePoint;
           medianFilter.enterData(static_cast<int>(1/duration.count()));
          // if( medianFilter.getIndex() == 28 )
          // {
               qDebug()<<medianFilter.getData();
               putText(myImage, "FPS:" + std::to_string(medianFilter.getData()),
               Point2f(0, 60), 2, 2, cv::Scalar(0,255,0),2);
          // }
       }
       prevTimePoint = currentTimePoint;
       String res = std::to_string(static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH))) + "x" + std::to_string(static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)));
       putText(myImage, "Res:" + res, Point2f(0, 150), 2, 2, cv::Scalar(0,0,255),2);
       imshow("FPS Checker", myImage);
    }
    cap.release();
    destroyAllWindows();
}


