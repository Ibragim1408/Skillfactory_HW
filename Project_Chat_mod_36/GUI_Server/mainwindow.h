#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/chat.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

signals:
  void UpdateUserList();
  void UpdateMessages();

private slots:
  void on_BanButton_clicked();
  void on_UnbanButton_clicked();
  void on_UpdateMessage_clicked();
  void on_updateUserButton_clicked();
  void updateUsers();
  void updateChats();

private:
  Ui::MainWindow *ui;
  Chat chat_;
};
#endif // MAINWINDOW_H
