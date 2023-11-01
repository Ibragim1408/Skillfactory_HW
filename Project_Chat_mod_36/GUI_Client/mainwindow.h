#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chat.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

   static MainWindow* createClient(std::shared_ptr<Chat> dbPtr = nullptr);

private slots:
  void on_msgLineEdit_returnPressed();
  void on_sendMessageToAllButton_clicked();
  void on_sendMessageToButton_clicked();
  void on_actionOpen_another_client_triggered();
  void on_actionCloseClient_triggered();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
