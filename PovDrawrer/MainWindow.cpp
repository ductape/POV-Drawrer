#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Led.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QScreen>
#include <QtMath>
#include <QDebug>

static const qreal LED_SIZE_IN = 0.1259;
static const qreal WORK_SCREEN_X_DPI = 1920 / 18.75;
static const qreal WORK_SCREEN_Y_DPI = 1080 / 10.5;
static const int SPIN_BOX_MIN_WIDTH = 70;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    numberOfColumns(60)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    PopulateScene(this->numberOfColumns);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMinimumSize(scene->sceneRect().size().toSize()*1.5);
    ui->graphicsView->show();

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setMaximum(INT_MAX);
    spinBox->setMinimum(INT_MIN);
    spinBox->setValue(this->numberOfColumns);
    spinBox->setMinimumWidth(SPIN_BOX_MIN_WIDTH);
    spinBox->setKeyboardTracking(false);
    ui->formLayout->addRow(tr("Number of columns"), spinBox);

    ui->textEdit->setReadOnly(true);
    ui->textEdit->append(QString(tr("Columns")) + " " + QString::number(this->numberOfColumns));

    setWindowTitle(tr("Pov Drawrer"));
    //dynamic_cast<Led*>(scene->items()[0])->setColor(Qt::red);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(PopulateScene(int)));
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::PopulateScene(int numberColumns)
{
    static const qreal diameterInch = 3.74;
    static const qreal insideDiameterKeepout = 1.0;
    this->numberOfColumns = numberColumns;
    int itemsPerColumn = 8;

    qreal physX = logicalDpiX();
    qreal physY = logicalDpiY();

    /* Draw circle */
    QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(QRectF(-(physX * diameterInch) / 2.0,
                                                           -(physY * diameterInch) / 2.0,
                                                           physX * diameterInch,
                                                           physY * diameterInch));
    circle->setBrush(QBrush(Qt::blue));
    scene->addItem(circle);

    QRectF circleRect = circle->boundingRect();

    for (int i = 0; i < this->numberOfColumns; ++i)
    {
        QList<QGraphicsItem*> ledColumn;

        for (int j = 0; j < itemsPerColumn; ++j)
        {
            QColor color;

            switch(i%5)
            {
            case 1:
                color = Qt::red;
                break;

            case 2:
                color = Qt::green;
                break;

            case 3:
                color = Qt::yellow;
                break;

            case 4:
                color = Qt::white;
                break;

            default:
                color = Qt::black;
                break;
            }

            Led *item = new Led(color);
            item->setParentItem(circle);

            /* Set the initial position to the middle of the circle accounting for the center of the shape */
            qreal radius = ((circleRect.height()-(insideDiameterKeepout*physY))/2.0/itemsPerColumn*(j + 1))+(insideDiameterKeepout*physY/2.0);
            item->setCenterPos(QPointF(circleRect.center().x(), circleRect.center().y() - radius));
            ledColumn.push_back(item);
        }
        QGraphicsItemGroup *column = scene->createItemGroup(ledColumn);
        qreal columnAngle = ((360.0) / static_cast<qreal>(this->numberOfColumns)) * static_cast<qreal>(i);
        column->setRotation(columnAngle);
    }
}
