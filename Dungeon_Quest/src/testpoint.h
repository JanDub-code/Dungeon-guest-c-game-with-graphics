#ifndef TESTPOINT_H
#define TESTPOINT_H

#include <QObject>
#include "vectors.h"

class TestPoint : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int x_cr READ getPosCamRelX NOTIFY posChanged)
    Q_PROPERTY(int y_cr READ getPosCamRelY NOTIFY posChanged)
public:
    TestPoint();
    int getPosCamRelX();
    int getPosCamRelY();

    Vec2f m_pos = Vec2f(0.0F);
signals:
    void posChanged();
};

#endif // TESTPOINT_H
