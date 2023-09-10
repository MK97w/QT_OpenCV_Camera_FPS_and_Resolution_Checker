#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <QObject>

class MedianFilter : public QObject
{
    Q_OBJECT
public:
    explicit MedianFilter(QObject *parent = nullptr);
    static constexpr int medianSize = 10;
    static constexpr int windowSize{ medianSize * 3 };
    int getData();
    int getIndex();
    void enterData( int data );
signals:

private:
    std::vector<int> itsData;
    int index;
};

#endif // MEDIANFILTER_H
