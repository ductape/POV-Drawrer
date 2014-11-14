#ifndef LED_H
#define LED_H

#include <QColor>
#include <QGraphicsItem>

class Led : public QGraphicsItem
{
public:
    Led(const QColor color, int x, int y);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setScreenDpi(qreal dpi);
    qreal screenDpi() const;
    void setLedSizeInches(qreal inches);
    qreal ledSizeInches() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int x;
    int y;
    QColor color;
    qreal dpi;
    qreal sizeInches;
};
#endif // LED_H
