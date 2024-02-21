#ifndef ENGINEQTSIGNALS_H
#define ENGINEQTSIGNALS_H

#include <QObject>

class EngineQtSignals : public QObject
{
    Q_OBJECT
private:
    EngineQtSignals() {}
    ~EngineQtSignals() {}
public:
signals:
    static void windowWidthSet();  // Tell Qt that window width was set
    static void windowHeightSet();  // Tell Qt that window height was set
    static void frameFinished();
    static void objectsPositionChanged();
    static void objVecResized();
};

#endif // ENGINEQTSIGNALS_H
