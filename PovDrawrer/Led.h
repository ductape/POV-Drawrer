#ifndef LED_H
#define LED_H

#include <QColor>
#include <QGraphicsEllipseItem>

class Led : public QGraphicsEllipseItem
{
public:
    explicit Led(const QColor color = Qt::red, int x = 0, int y = 0);

    void setScreenDpi(qreal dpi);
    qreal screenDpi() const;
    void setLedSizeInches(qreal inches);
    qreal ledSizeInches() const;

    void setCenterPos(const QPointF &pos);
    QPointF centerPos() const;

private:
    qreal dpi;
    qreal sizeInches;
};
#endif // LED_H
