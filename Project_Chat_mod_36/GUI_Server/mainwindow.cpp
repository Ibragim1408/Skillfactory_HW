#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_BanButton_clicked()
{

}


void MainWindow::on_UnbanButton_clicked()
{

}


void MainWindow::on_UpdateMessage_clicked()
{

}

