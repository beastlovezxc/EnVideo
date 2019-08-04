#include "Classification.h"

#include <QDateTime>
#include <QString>
#include <QDebug>
#include <stdio.h>
#include <algorithm>
#include <vector>
Classification::Classification(const char* param_path, const char*  model_path)
{
    net_ptr = new ncnn::Net();
#if NCNN_VULKAN
    net.opt.use_vulkan_compute = true;
#endif // NCNN_VULKAN

    net_ptr->load_param(param_path);
    net_ptr->load_model(model_path);
    ncnn::Extractor ex = net_ptr->create_extractor();
    /*
     *  Get Extractor
     *
     */
    ex.set_light_mode(true);
    ex.set_num_threads(4);
    exptr = &ex;
}

ncnn::Extractor Classification::GetExtractor()
{
    ncnn::Extractor ex = net_ptr->create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(4);
    return ex;
}

void Classification::Detect(const cv::Mat& bgr)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    // 字符串格式化
    QString timestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    // 获取毫秒值
    int ms = dateTime.time().msec();
    // 转换成时间戳
    qint64 epochTime = dateTime.toMSecsSinceEpoch();

    // --------------------------------
    ncnn::Extractor ex = net_ptr->create_extractor();
    ex.set_light_mode(true);
    ex.set_num_threads(4);
    ncnn::Mat in = ncnn::Mat::from_pixels_resize(bgr.data, ncnn::Mat::PIXEL_BGR, bgr.cols, bgr.rows, 227, 227);
    const float mean_vals[3] = {104.f, 117.f, 123.f};
    in.substract_mean_normalize(mean_vals, 0);
    ex.input("data", in);
    ex.extract("prob", out);
    // --------------------------------

    dateTime = QDateTime::currentDateTime();
    timestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    ms = dateTime.time().msec();
    qint64 epochTime1 = dateTime.toMSecsSinceEpoch();
    qDebug() << epochTime1-epochTime << "ms";
    PrintTopK(3);
}
void Classification::PrintTopK(int topk)
{
    cls_scores.resize(out.w);
    for (int j=0; j<out.w; j++)
    {
        cls_scores[j] = out[j];
    }

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

}

Classification::~Classification()
{
    net_ptr->clear();
    net_ptr = nullptr;
}
