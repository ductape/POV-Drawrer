#ifndef LEDCOLUMN_H
#define LEDCOLUMN_H

#include <QGraphicsItemGroup>
#include <QSharedDataPointer>

class LedColumn : public QGraphicsItemGroup
{
public:
    explicit LedColumn(quint32 numLeds, qreal heightInches = 0.0, QGraphicsItem *parent = 0);
    ~LedColumn();

    quint32 numberOfLeds(void) const;

signals:

public slots:
    virtual void setColor(QColor &color);

private:
    class PrivateData;
    QSharedDataPointer<PrivateData> priv;

};

#endif // LEDCOLUMN_H
