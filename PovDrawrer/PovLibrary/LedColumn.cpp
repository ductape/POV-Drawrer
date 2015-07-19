#include "LedColumn.h"
#include "Led.h"
#include <QList>

class LedColumn::PrivateData : public QSharedData
{
public:
    PrivateData()
    {
    }

    ~PrivateData()
    {
    }

    QList<Led*> ledList;
};

LedColumn::LedColumn(quint32 numLeds, qreal heightInches, QGraphicsItem *parent) :
    QGraphicsItemGroup(parent)
{
    for(quint32 index = 0; index < numLeds; ++index)
    {
        Led *led = new Led(this);
        qreal ledYPos;

        if (heightInches > 0.0)
        {
            ledYPos = static_cast<qreal>(this->priv->ledList.size()) * heightInches / static_cast<qreal>(numLeds);
        }
        else
        {
            if (this->priv->ledList.isEmpty())
            {
                ledYPos = 0.0;
            }
            else
            {
                ledYPos = this->priv->ledList.last()->pos().y() + led->boundingRect().height();
            }
        }
        led->setPos(led->pos().x(), ledYPos);
        this->priv->ledList.append(led);
    }
}

LedColumn::~LedColumn()
{
    while(!this->priv->ledList.isEmpty())
    {
        delete this->priv->ledList.takeFirst();
    }
}

quint32 LedColumn::numberOfLeds(void) const
{
    return this->priv->ledList.size();
}

void LedColumn::setColor(QColor &color)
{
    foreach(Led *led, this->priv->ledList)
    {
        led->setColor(color);
    }
}
