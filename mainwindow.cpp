#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parse.h"

#define POINTS_NO 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::plot()
{
    // add two new graphs and set their look:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->yAxis2->setTickLabels(false);
    // pass data points to graphs:
    ui->customPlot->graph(0)->setData(xPoints, yPoints);
    ui->customPlot->xAxis2->setLabel("x");
    ui->customPlot->yAxis2->setLabel("f(x)");
    ui->customPlot->xAxis2->setRange(xMin, xMax);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->customPlot->graph(0)->rescaleAxes();
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void MainWindow::on_plotButton_clicked()
{
    QString str = ui->minx->text();
    xMin = str.toDouble();
    str = ui->maxx->text();
    xMax = str.toDouble();

    inputEqn = ui->eqn_txt->text();

    double step = (xMax - xMin) / POINTS_NO;

    inputText = inputEqn.toStdString();
    inputTextIdx = 0; inputTextLimit = inputText.size(); isError = false;
    TreeNode * root;
    token = getToken(); // initialize the token
    root = equ(); // build the tree

    xPoints = QVector<double>(POINTS_NO);
    yPoints = QVector<double>(POINTS_NO);
    double x;
    for (int i=0; i<POINTS_NO; ++i)
    {
      Xunknown = xMin + i * step;
      xPoints[i] = Xunknown;
      yPoints[i] = calc(root); // exponentially decaying cosine
    }
    plot();
}


void MainWindow::on_clearButton_clicked()
{
    xPoints.clear();
    yPoints.clear();
    plot();
}

double MainWindow::calcBasic(double x)
{
    return x*x;
}

