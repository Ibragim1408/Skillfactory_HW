#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , chat_(Chat())
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_BanButton_clicked() {
  chat_.ChangeUserStatus(name, "Ban");
}


void MainWindow::on_UnbanButton_clicked() {
  chat_.ChangeUserStatus(name, "Unban");
}


void MainWindow::on_UpdateMessage_clicked()
{

}


void MainWindow::on_updateUserButton_clicked()
{

}

