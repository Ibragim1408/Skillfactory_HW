#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , chat_(Chat())
{
  ui->setupUi(this);
  auto timer = new QTimer(this);

  connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
  connect(this, &MainWindow::UpdateMessages, this, &MainWindow::updateChats);
  connect(this, &MainWindow::UpdateUserList, this, &MainWindow::updateUsers);

  timer->start(10);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_BanButton_clicked() {
  std::string name(ui->userLineEdit->text());
  if (!chat_.ChangeUserStatus(name, "Ban")) {
    QMessageBox::critical(this, "Error", "Incorrect name");
  }
  emit UpdateUserList();
}


void MainWindow::on_UnbanButton_clicked() {
  std::string name(ui->userLineEdit->text());
  if (!chat_.ChangeUserStatus(name, "Unan")) {
    QMessageBox::critical(this, "Error", "Incorrect name");
  }
  emit UpdateUserList()
}


void MainWindow::on_UpdateMessage_clicked() {
  emit UpdateMessages();
}


void MainWindow::on_updateUserButton_clicked() {
    emit UpdateUserList();
}

void MainWindow::updateChats() {
  auto allMsg = chat_.GetAllMessages();
  Qstring msgs(allMsg);
  ui->allMessBrowser>setText(chat);
}

void MainWindow::updateUsers() {
  auto allUsers = chat_.GetAllUsers();
  Qstring chat(allUsers);
  ui->allUserBrowser->setText(chat);
}