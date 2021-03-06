#ifndef QWGRAPHICSVIEW_H
#define QWGRAPHICSVIEW_H
#include <QMouseEvent>
#include <QGraphicsView>

class QWGraphicsView : public QGraphicsView
{
    Q_OBJECT
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

public:
    QWGraphicsView(QWidget* parent = 0);

signals:
    void mouseMovePoint(QPoint point);
    void mouseClicked(QPoint point);
    void mouseDoubleClicked(QPoint point);
    void keyPress(QKeyEvent* event);
};

#endif // QWGRAPHICSVIEW_H
