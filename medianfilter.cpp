#include "medianfilter.h"

MedianFilter::MedianFilter(QObject *parent)
    : QObject{parent} ,itsData( windowSize ), index(0)
{

}


void MedianFilter::enterData(int data)
{
   itsData[index++] = data;
   if(index >= 29)
       index = 0;
}

int MedianFilter::getData()
{
    std::sort(itsData.begin(),itsData.end());
    int average{};
    for(int i{medianSize}; i<medianSize*2; i++ )
    {
        average+=itsData[i];
    }
    return average/medianSize;
}

int MedianFilter::getIndex()
{
    return index;
}
