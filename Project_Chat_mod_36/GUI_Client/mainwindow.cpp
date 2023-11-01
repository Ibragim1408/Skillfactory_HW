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

MainWindow *MainWindow::createClient(std::shared_ptr<Chat> dbPtr) {
  StartScreen s(dbPtr);
  auto result = s.exec();
  if(result == QDialog::Rejected)
    {
      return nullptr;
    }
  auto w = new MainWindow(s.userId(), s.userName(), s.getDatabase());
  w->setAttribute(Qt::WA_DeleteOnClose);
  return w;
}


void MainWindow::on_msgLineEdit_returnPressed() {
  on_sendMessageToAllButton_clicked();
}


void MainWindow::on_sendMessageToAllButton_clicked()
{

}


void MainWindow::on_sendMessageToButton_clicked()
{

}


void MainWindow::on_actionOpen_another_client_triggered() {
  createClient();
}


void MainWindow::on_actionCloseClient_triggered()
{

}

