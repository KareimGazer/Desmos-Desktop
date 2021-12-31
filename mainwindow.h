#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString inputEqn;
    QVector<double> xPoints, yPoints;
    double xMin, xMax;

private slots:
    void plot();
    void on_plotButton_clicked();
    void on_clearButton_clicked();
    void setupCalculations(double step); // sets the points to be drawn
    void getEqnText(); // gets the equation text
    void setLimits(); // set min and max limits of the equation

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
