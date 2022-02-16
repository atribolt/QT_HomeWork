#include <QApplication>
#include <QLoggingCategory>

#include "CommonLib/Server.h"
#include "mainwindow.h"
#include "WaveFunction.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Server server;

  if (!server.start("0.0.0.0", 1111)) {
    qCritical() << "Server didn't start";
  }

  MainWindow w(&server);
  w.setWaveFunction(Waves::WaveSinus);
  QObject::connect(&w, &MainWindow::destroyed, &a, &QApplication::quit);
  w.show();

  return a.exec();
}
