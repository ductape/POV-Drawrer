#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Led.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QScreen>
#include <QtMath>

static const qreal LED_SIZE_IN = 0.1259;
static const qreal WORK_SCREEN_X_DPI = 1920 / 18.75;
static const qreal WORK_SCREEN_Y_DPI = 1080 / 10.5;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    PopulateScene();

    QGraphicsView *view = new QGraphicsView(scene);
    view->setMinimumSize(scene->sceneRect().size().toSize());
    view->show();
    this->setCentralWidget(view);
    setWindowTitle(tr("Pov Drawrer"));

    //dynamic_cast<Led*>(scene->items()[0])->setColor(Qt::red);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::PopulateScene()
{
    static const qreal diameterInch = 3.74;
    static const qreal insideDiameterKeepout = 1.0;
    int columns = 32;
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

    for (int i = 0; i < columns; ++i)
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
        qreal columnAngle = ((360.0) / static_cast<qreal>(columns)) * static_cast<qreal>(i);
        column->setRotation(columnAngle);
    }
}
