#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "platform.h"
#include "net.h"
#if NCNN_VULKAN
#include "gpu.h"
#endif // NCNN_VULKAN
class Classification
{
public:
    Classification(const char* param_path, const char*  model_path);
    ncnn::Extractor GetExtractor();
    void Detect(const cv::Mat& bgr);
    void PrintTopK(int topk);
    ~Classification();

private:
    ncnn::Net* net_ptr;
    ncnn::Mat out;
    ncnn::Extractor*   exptr;

    std::vector<float> cls_scores;
};


#endif // CLASSIFICATION_H
