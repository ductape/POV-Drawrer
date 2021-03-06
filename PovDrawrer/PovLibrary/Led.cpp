#include "Led.h"
#include <QtWidgets>

static const qreal LED_SIZE_IN = 0.1259;
static const qreal NOMINAL_SCREEN_DPI = 96.0;
static const QColor DEFAULT_COLOR = Qt::red;

/**
 * @brief Led::Led creates a QGraphicsEllipseItem that is set with the defaults of a special LED type.
 * @param color - the color to set the LED to.
 * @param x - the x coordinate for the center position of the LED
 * @param y - the y coordinate for hte center position of the LED
 */
Led::Led(const QColor color, int x, int y, QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent),
    dpi(NOMINAL_SCREEN_DPI),
    sizeInches(LED_SIZE_IN)
{
    qreal diameter = this->dpi * this->sizeInches;

    this->setRect(QRectF((diameter/2) + x, -(diameter/2) - y, diameter, diameter));
    this->setColor(color);
}

Led::Led(QGraphicsItem *parent) :
    QGraphicsEllipseItem(parent),
    dpi(NOMINAL_SCREEN_DPI),
    sizeInches(LED_SIZE_IN)
{
    qreal diameter = this->dpi * this->sizeInches;
    this->setRect(QRectF((diameter/2), -(diameter/2), diameter, diameter));
    this->setColor(DEFAULT_COLOR);
}

void Led::setScreenDpi(qreal dpi)
{
    this->dpi = dpi;
    this->update();
}
qreal Led::screenDpi() const
{
    return this->dpi;
}
void Led::setLedSizeInches(qreal inches)
{
    this->sizeInches = inches;
    this->update();
}

qreal Led::ledSizeInches() const
{
    return this->sizeInches;
}

void Led::setCenterPos(const QPointF &pos)
{
    qreal xpos = pos.x() - (this->boundingRect().width());
    qreal ypos = pos.y() + (this->boundingRect().height());
    QPointF position = QPointF(xpos, ypos);
    this->setPos(position);
}

QPointF Led::centerPos() const
{
    qreal xpos = this->pos().x() + (this->boundingRect().width());
    qreal ypos = this->pos().y() - (this->boundingRect().height());
    QPointF pos = QPointF(xpos, ypos);
    return pos;
}

void Led::setColor(const QColor &color)
{
    this->setPen(QPen(color.darker()));
    this->setBrush(QBrush(color));
    this->update();
}

QColor Led::color() const
{
    return this->brush().color();
}
