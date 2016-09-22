#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableWidget->setRowCount(0);
    qDebug()<<"starting ui";
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    QPixmap pic(":/img/default");
    scene->addPixmap(pic);
    ui->graphicsView->scale(0.25,0.25);

    client = new MBClient(this);
    connect(client, SIGNAL(newPicture(QImage)), this, SLOT(showPicture(QImage)) );

    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    //connect(client, SIGNAL(newPhoto(QString)), this, SLOT(appendPhoto(QString)) );
    connect(client, SIGNAL(newPhoto2(pic_struct)), this, SLOT(appendPhoto(pic_struct)) );


}

MainWindow::~MainWindow()

{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //QMessageBox box;
    //box.setText("quit");
    //box.exec();
    qDebug()<<"press button";
    //qApp->quit();
//    QApplication* app;
//    app->quit();
    //client->getPicture( ui->listWidget->currentItem()->data(Qt::DisplayRole).toString() );
    //client->getPicture( ui->tableWidget->currentItem()->data(Qt::DisplayRole).toString() );
    //client->getPicture( ui->tableWidget->currentRow()->data(Qt::DisplayRole).toString() );

    client->getPicture( ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->data(Qt::DisplayRole).toString() );

}

void MainWindow::showPicture(const QImage& img) {
    scene->clear();
    QPixmap pic=QPixmap::fromImage(img);
    scene->addPixmap(pic);
}

void MainWindow::appendPhoto(const pic_struct& str) {
    //ui->listWidget->addItem(str);

    //ui->tableWidget->setColumnCount(4);

    int row=ui->tableWidget->rowCount();
    //int row=ui->tableWidget->currentRow();
    //row=row+1;
    /*ui->tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

    ui->tableWidget->setItem(0,1,new QTableWidgetItem("Jan's month"));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem("Feb's month"));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem("Mar's month"));*/
    ui->tableWidget->insertRow(row);
    QTableWidgetItem* name = new QTableWidgetItem(str.name);
    ui->tableWidget->setItem(row,0,name);

    QTableWidgetItem* date = new QTableWidgetItem(str.date);
    ui->tableWidget->setItem(row,1,date);
    QTableWidgetItem* time = new QTableWidgetItem(str.time);
    ui->tableWidget->setItem(row,2,time);
    double sz = str.size / 1024.0/1024.0;
    QTableWidgetItem* isz = new
            QTableWidgetItem(QString("%1").
                             arg(sz, 0, 'g', 2) );
    ui->tableWidget->setItem(row,3, isz);

    if(row % 2 == 1) {
        QColor color = QColor(200,200,200);
        name->setBackgroundColor(color);
        time->setBackgroundColor(color);
        date->setBackgroundColor(color);
        isz->setBackgroundColor(color);
    }
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();



    ui->tableWidget->show();



}

void MainWindow::on_radioButton_clicked()
{
   ui->graphicsView->scale(1.1,1.1);
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->graphicsView->scale(0.9,0.9);
}
