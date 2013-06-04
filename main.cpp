#include <mysettings.h>
#include <QApplication>
#include <QDialog>
#include <QHBoxLayout>
int main(int argn,char *argc[])
{
  QApplication app(argn,argc);
  QDialog *dlg=new QDialog;
  QHBoxLayout *hlayout=new QHBoxLayout(dlg);
  dlg->setFixedWidth (1000);
  dlg->setFixedHeight (700);
  MySettings window;
  hlayout->addWidget (&window);
  dlg->show ();

  return app.exec ();
}

