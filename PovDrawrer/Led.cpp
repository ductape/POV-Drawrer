#include "Led.h"
#include <QtWidgets>
#include <QScreen>

static const qreal LED_SIZE_IN = 0.1259;

Led::Led(const QColor color, int x, int y) :
    x(x),
    y(y),
    color(color),
    dpi(102.0),
    sizeInches(LED_SIZE_IN)
{
    setZValue((x + y) % 2);
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Led::boundingRect() const
{
    qreal height = this->dpi * LED_SIZE_IN;
    qreal width = this->dpi * LED_SIZE_IN;

    return QRectF(width/2, -height/2, width, height);
}

QPainterPath Led::shape() const
{
    QPainterPath path;
    path.addEllipse(this->boundingRect());
    return path;
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

void Led::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
    {
        fillColor = fillColor.light(125);
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
    {
        width += 2;
    }

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawEllipse(QRectF(this->boundingRect().width()/2,
                                -this->boundingRect().height()/2,
                                this->boundingRect().width(),
                                this->boundingRect().height()));
    painter->setBrush(b);
}

void Led::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Led::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
    update();
}

void Led::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
