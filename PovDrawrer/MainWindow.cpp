#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PovLibrary/LedColumn.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemGroup>
#include <QScreen>
#include <QtMath>
#include <QDebug>

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

    this->resize(view->size()*1.2);
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
    int columns = 4;
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

    for (int i = 0; i < columns; ++i)
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

        LedColumn *column = new LedColumn(itemsPerColumn, (diameterInch - insideDiameterKeepout)/2.0, circle);
        column->setColor(color);
        column->moveBy(-column->boundingRect().width()/2.0,insideDiameterKeepout*WORK_SCREEN_Y_DPI/2.0);
       column->setTransformOriginPoint(0,0);
       qDebug() << "Column[" << i << "] pos:" << column->pos() << ", bounding rect:" << column->boundingRect() << ", origin:" << column->transformOriginPoint() << ", rotation:" << column->rotation();

        if (columns > 0)
        {
            column->setRotation((360/columns)*i);
        }
        qDebug() << "rColumn[" << i << "] pos:" << column->pos() << ", bounding rect:" << column->boundingRect() << ", origin:" << column->transformOriginPoint() << ", rotation:" << column->rotation();
    }
    qDebug() << "circle pos:" << circle->pos() << ", bounding rect:" << circle->boundingRect() << ", origin:" << circle->transformOriginPoint() << ", rotation:" << circle->rotation() << ", center:" << circle->pos().x() + circle->boundingRect().width()/2 << "x" << circle->pos().y() + circle->boundingRect().height()/2;
}
