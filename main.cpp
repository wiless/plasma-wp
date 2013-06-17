#include <mysettings.h>
#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
#include <KPlotWidget>
#include <KPlotObject>
#include <KPlotAxis>
#include <KPlotPoint>
#include <itpp/itbase.h>
#include <QDesktopWidget>
#include <QString>
#include <qtextstream.h>

int main(int argn,char *argc[])
{
  QApplication app(argn,argc);
  QDialog *dlg=new QDialog;
  QHBoxLayout *hlayout=new QHBoxLayout(dlg);
   dlg->setFixedWidth (700);
   dlg->setFixedHeight (700);

  
  MySettings window;

  hlayout->addWidget (&window);
  QRect  r=app.desktop()->screenGeometry();
  window.setScreen(QRectF(0,0,r.width(),r.height()));


  
  dlg->show ();
  return app.exec ();
}

