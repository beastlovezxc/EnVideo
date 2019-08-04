#include "EvVideoCapture.h"
#include <QDebug>
#include <QFileInfo>
EvVideoCapture::EvVideoCapture():
    m_pEvShowFrame(nullptr),
    m_bCameraOn(false),
    m_strVideoPath("")
{
    m_pEvShowFrame = new EvShowFrame();
    m_pClassification = new Classification("/Users/Bean/WorkSpace/ncnn/squeezenet_v1.1.param","/Users/Bean/WorkSpace/ncnn/squeezenet_v1.1.bin");
    this->moveToThread(&mWorkThread);
    connect(&mWorkThread, SIGNAL(started()), this, SLOT(slotVideoCaptureProcess()), Qt::QueuedConnection);
}

EvVideoCapture::~EvVideoCapture()
{
    mWorkThread.quit();
}

void EvVideoCapture::startVideoCaptureProcess()
{
    if(!m_bCameraOn) {
        m_pVideoCapture = VideoCapture(m_strVideoPath.toStdString());
    } else {
        m_pVideoCapture = VideoCapture(1200);
    }
    mWorkThread.start();
}

void EvVideoCapture::registEvVideoCaptureView(EvVideoCaptureView *videoCaptureView)
{
    m_pEvVideoCaptureView = videoCaptureView;
    connect(this, SIGNAL(sigFrame()), m_pEvVideoCaptureView, SLOT(setFrame()), Qt::DirectConnection);
}

void EvVideoCapture::restartProcess(bool isCameraOn)
{
    if(isCameraOn == m_bCameraOn)
        return;
    m_bCameraOn = isCameraOn;
    if(isCameraOn) {
        mWorkThread.quit();
        m_pVideoCapture = VideoCapture(0);
        mWorkThread.start();
    } else {
        mWorkThread.quit();
        m_pVideoCapture = VideoCapture("/Users/Bean/WorkSpace/1.mp4");
        mWorkThread.start();
    }
}

void EvVideoCapture::closeProcess()
{
    m_pVideoCapture.release();
    mWorkThread.quit();
}

void EvVideoCapture::setVideoPath(QString videoPath)
{
    m_strVideoPath = videoPath;
}

void EvVideoCapture::setCameraOn(bool isCameraOn)
{
    m_bCameraOn = isCameraOn;
}

void EvVideoCapture::slotVideoCaptureProcess()
{
    int count = 0;
    while(1) {
        Mat frame;
        if(!m_pVideoCapture.isOpened()) {
            break;
        }
        m_pVideoCapture >> frame;
        if(frame.empty())
            break;
        qDebug() << "count is " << ++count;
        m_pFrame = BGRToRGB(frame);
        m_pEvShowFrame->setFrame(m_pFrame);
        m_pClassification->Detect(m_pFrame);
        waitKey(30);
        emit sigFrame();
    }
}
Mat EvVideoCapture::BGRToRGB(Mat img)
{
    Mat image(img.rows, img.cols, CV_8UC3);
    for (int i = 0; i < img.rows; ++i)
    {
        Vec3b *p1 = img.ptr<Vec3b>(i);
        Vec3b *p2 = image.ptr<Vec3b>(i);
        for(int j=0; j<img.cols; ++j)
        {
            p2[j][2] = p1[j][0];
            p2[j][1] = p1[j][1];
            p2[j][0] = p1[j][2];
        }
    }
    return image;
}
