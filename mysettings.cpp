#include "mysettings.h"
#include "ui_mysettings.h"
#include "QFileDialog"
#include <QPicture>
MySettings::MySettings(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MySettings)
{
  ui->setupUi(this);
  ui->lblImage->setMaximumWidth (ui->frame_3->width ());
  ui->lblImage->setMaximumHeight (ui->frame_3->height());
 // ui->lineEdit->setText (grp.readEntry("textString", QString("")));
ui->desktop->move (0,0);
scale=true;
offset=QPoint(0,0);
}

void MySettings::setConfig(KConfigGroup config)
{
grp=config;
ui->lineEdit->setText (grp.readEntry("textString", QString("")));
//QString str;
//str.sprintf("%f x %f",desktopSize.width(),desktopSize.height());
//ui->label_3->setText (str);

}


MySettings::~MySettings()
{
  delete ui;
}

void MySettings::on_toolButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg)"));
  if(!fileName.isEmpty ())
    {

      ui->lineEdit->setText (fileName);
      QPixmap newmap;
      newmap.load (ui->lineEdit->text ());

       if(ui->checkBox->isChecked ())
      newmap=newmap.scaled (ui->desktop->size (),Qt::KeepAspectRatioByExpanding);

       ui->lblImage->setPixmap (newmap);
  ui->horizontalScrollBar->setValue (0);
  ui->verticalScrollBar->setValue (0);
      if(ui->lineEdit->text ()!=fileName)
        emit settingsChanged();

    }

}


KConfigGroup MySettings::getConfig()
{
  return grp;
}
void MySettings::setScreen(QRectF rect)
{
desktopSize=rect;


}

void MySettings::appendUrl(QString str)
{
    grp.writeEntry("textString", str);
    ui->lineEdit->setText (str);
    emit settingsChanged ();
}

void MySettings::resizeEvent(QResizeEvent *event)
{
  QString str;
  double screenRatio=(double)desktopSize.width()/desktopSize.height();
  double boxRatio=(double)ui->frame_3->width ()/ui->frame_3->height ();
  int myheight,mywidth;
  ui->horizontalScrollBar->setValue (0);
  ui->verticalScrollBar->setValue (0);
  if(screenRatio>=boxRatio)
    {
      mywidth=ui->frame_3->width () ;
      myheight=int(mywidth*(desktopSize.height ()/desktopSize.width ()));

      str.sprintf("Dimensions : %f x %f \n Mapped to %f  %f",(double)desktopSize.width()/desktopSize.height(),(double)ui->frame_3->width ()/ui->frame_3->height ());
      ui->label_3->setText (str);

      ui->desktop->resize (mywidth,myheight);


    }
else
    {
        myheight=ui->frame_3->height ()  ;
        mywidth= int(myheight*(desktopSize.width ()/desktopSize.height())) ;

      str.sprintf("Dimensions : %f x %f \n Mapped to %f  %f",(double)desktopSize.width()/desktopSize.height(),(double)ui->frame_3->width ()/ui->frame_3->height ());
      ui->label_3->setText (str);

      ui->desktop->resize (mywidth,myheight);

    }


ui->lblImage->resize(mywidth,myheight);
if(!ui->lineEdit->text ().isEmpty ())
  {
     QPixmap pmap;
     pmap.load (ui->lineEdit->text ());
     ui->horizontalScrollBar->setMaximum (pmap.width ());

     ui->verticalScrollBar->setMaximum (pmap.height ());

//     ui->verticalScrollBar->setMinimum (-pmap.height ());
//     ui->horizontalScrollBar->setMinimum (-pmap.width ());

     if(ui->checkBox->isChecked ())
     pmap=pmap.scaled (ui->desktop->size (),Qt::KeepAspectRatioByExpanding);

//     pmap.scroll (ui->horizontalScrollBar->value (),ui->verticalScrollBar->value (),ui->lblImage->rect ());
  ui->lblImage->setPixmap (pmap);

  }
    ui->desktop->move ((ui->frame_3->width ()-ui->desktop->width ())/2,(ui->frame_3->height()-ui->desktop->height())/2);




       QWidget::resizeEvent(event);
}

void MySettings::setScaleOffset(QPointF offset, double scale)
{

  grp.writeEntry ("offset",offset);
  grp.writeEntry ("scale",scale);

  int scaleindx=scale/0.1;
  ui->horizontalSlider->setValue (scaleindx);
//  ui->doubleSpinBox->setValue(scale);
//  ui->horizontalSlider->setValue(offset.x ());
//  ui->verticalSlider->setValue(offset.y ());



}

void MySettings::on_horizontalSlider_valueChanged(int value)
{

}

void MySettings::on_horizontalScrollBar_valueChanged(int value)
{
 scroll ();

}

void MySettings::on_verticalScrollBar_valueChanged(int value)
{
  scroll ();
}

void MySettings::scroll()
{
  QPixmap newmap;
  newmap.load (ui->lineEdit->text ());

  newmap.scroll (-ui->horizontalScrollBar->value (),-ui->verticalScrollBar->value (),newmap.rect ());
  if(ui->checkBox->isChecked ())
  newmap=newmap.scaled (ui->desktop->size (),Qt::KeepAspectRatioByExpanding);

  offset=QPoint(-ui->horizontalScrollBar->value (),-ui->verticalScrollBar->value ());
  scale=ui->checkBox->isChecked ();

  ui->lblImage->setPixmap (newmap);
  emit settingsChanged ();
}




void MySettings::on_checkBox_clicked()
{
    scroll ();

}

void MySettings::on_lineEdit_returnPressed()
{
    scroll ();
}
