#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <mbclient.h>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showPicture(const QImage& img);

    void appendPhoto(const pic_struct& str);

private slots:
    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    MBClient *client;
};

#endif // MAINWINDOW_H
