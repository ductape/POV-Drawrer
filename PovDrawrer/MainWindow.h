#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QSplitter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void PopulateScene(int numberColumns);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int numberOfColumns;

};

#endif // MAINWINDOW_H
