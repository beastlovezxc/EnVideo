#include "EvVideoCaptureView.h"

EvVideoCaptureView::EvVideoCaptureView()
{

}

void EvVideoCaptureView::setFrame()
{
    emit frameChanged();
}
