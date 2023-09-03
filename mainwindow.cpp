#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>
#include <QDebug>
#include <chrono>

using namespace cv;
using timeType = decltype(std::chrono::high_resolution_clock::now());
using timer =std::chrono::high_resolution_clock;

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
    //VideoCapture cap("C:\\Users\\kabuk\\OneDrive\\Resimler\\Camera Roll\\test2.mp4",CAP_ANY);
   // cap.set(CAP_PROP_FPS, 30.0);
   /* cap.set(CAP_PROP_FOURCC, VideoWriter.fourcc('m','j','p','g'));
    cap.set(CAP_PROP_FOURCC, VideoWriter.fourcc('M','J','P','G'));

    */
    //cap.set(CAP_PROP_FRAME_WIDTH, 1280); //I've maxed the resolution to get my webcam's max value
    //cap.set(CAP_PROP_FRAME_HEIGHT, 720);

    while (waitKey(1) != 'q')
    {
       cap >> myImage;
       if (myImage.empty()) break;
       auto currentTimePoint = timer::now();
       if ( prevTimePoint.time_since_epoch().count() )
       {
           std::chrono::duration<float> duration = currentTimePoint - prevTimePoint;
           putText(myImage, "FPS:" + std::to_string(static_cast<int>(1/duration.count())),
           Point2f(0, 60), 2, 2, cv::Scalar(0,255,0),2);
       }
       prevTimePoint = currentTimePoint;
       String res = std::to_string(static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH))) + "x" + std::to_string(static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)));
       putText(myImage, "Res:" + res, Point2f(0, 150), 2, 2, cv::Scalar(0,0,255),2);
       imshow("FPS Checker", myImage);
    }
    cap.release();
    destroyAllWindows();
}

