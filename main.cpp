#include <QGuiApplication>
#include <QtQuick>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlApplicationEngine>

#include "Controller/EvDispatcher.h"
#include "Common/EvVideoCapture.h"
#include "View/EvVideoCaptureView.h"
#include "View/EvSetting.h"

#include "opencv2/opencv.hpp"
#include "net.h"
#include "platform.h"
#define SAFE_RELEASE(x) { if(x != nullptr) delete x; x = nullptr; }
static int detect_squeezenet(const cv::Mat& bgr, std::vector<float>& cls_scores)
{
    ncnn::Net squeezenet;

#if NCNN_VULKAN
    squeezenet.opt.use_vulkan_compute = true;
#endif // NCNN_VULKAN

    squeezenet.load_param("squeezenet_v1.1.param");
    squeezenet.load_model("squeezenet_v1.1.bin");

    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR, bgr.cols, bgr.rows, 227, 227);

    const float mean_vals[3] = {104.f, 117.f, 123.f};
    in.substract_mean_normalize(mean_vals, 0);

    ncnn::Extractor ex = squeezenet.create_extractor();

    ex.input("data", in);

    ncnn::Mat out;
    ex.extract("prob", out);

    cls_scores.resize(out.w);
    for (int j=0; j<out.w; j++)
    {
        cls_scores[j] = out[j];
    }

    return 0;
}

static int print_topk(const std::vector<float>& cls_scores, int topk)
{
    // partial sort topk with index
    int size = cls_scores.size();
    std::vector< std::pair<float, int> > vec;
    vec.resize(size);
    for (int i=0; i<size; i++)
    {
        vec[i] = std::make_pair(cls_scores[i], i);
    }

    std::partial_sort(vec.begin(), vec.begin() + topk, vec.end(),
                      std::greater< std::pair<float, int> >());

    // print topk and score
    for (int i=0; i<topk; i++)
    {
        float score = vec[i].first;
        int index = vec[i].second;
        fprintf(stderr, "%d = %f\n", index, score);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    EvDispatcher* gEvDispatcher = new EvDispatcher();
    EvVideoCapture* gEvVideoCapture = new EvVideoCapture();
    EvVideoCaptureView* gEvVideoCaptureView = new EvVideoCaptureView();
    EvSetting* gEvSettingView = new EvSetting();

    gEvVideoCapture->registEvVideoCaptureView(gEvVideoCaptureView);
    gEvSettingView->registVideoCapture(gEvVideoCapture);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickView viewer;

    viewer.engine()->addImageProvider("img",gEvVideoCapture->getEvShowFrame());
    viewer.rootContext()->setContextProperty("dispatcher", gEvDispatcher);
    viewer.rootContext()->setContextProperty("EvVideoCaptureView", gEvVideoCaptureView);
    viewer.rootContext()->setContextProperty("EvSettingView", gEvSettingView);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    viewer.setSource(url);
    viewer.show();

   // gEvVideoCapture->startVideoCaptureProcess();

    return app.exec();
}
