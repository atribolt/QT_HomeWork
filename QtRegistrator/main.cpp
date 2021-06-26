#include <QApplication>

#include "Client.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  
  Client client;
  client.connectToServer("127.0.0.1", 1111);
  MainWindow w(&client);
  
  QObject::connect(&w, &MainWindow::destroyed, &a, &QApplication::quit);
  w.show();

  return a.exec();
}
