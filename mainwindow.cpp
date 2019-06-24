#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    helper = new drawhelper(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_okButton_clicked()
{
    int m, n, a, b;
    m = ui->mText->text().toInt();
    n = ui->nText->text().toInt();
    a = ui->aText->text().toInt();
    b = ui->bText->text().toInt();
    helper->draw_graph(m, n, a, b);
}
