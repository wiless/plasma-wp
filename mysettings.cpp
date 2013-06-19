#include "mysettings.h"
#include "ui_mysettings.h"
#include "QFileDialog"
#include <QPicture>
#include <QCompleter>
#include <QDirModel>
MySettings::MySettings(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::MySettings)
{
  ui->setupUi(this);
  connect(this,SIGNAL(destroyed()),this,SLOT(close()));
//   ui->lblImage->setMaximumWidth (ui->frame_3->width ());
//   ui->lblImage->setMaximumHeight (ui->frame_3->height());
 // ui->lineEdit->setText (grp.readEntry("textString", QString("")));
// ui->desktop->move (0,0);
// scale=true;
  mysetting=new QSettings("wilessbytes", "plasma-wp",this);

offset=QPoint(0,0);
scaleFactor=100;
stretchType=0;
init();

}

void MySettings::init()
{

 pvsFname=mysetting->value ("ImageSource").toString ();
  scaleFactor=mysetting->value ("scaleFactor").toInt ();
  stretchType=mysetting->value ("stretchType").toInt ();
  offset=mysetting->value ("offset").toPoint ();
  bool rotated=mysetting->value ("rotated").toBool ();

  if(rotated) ui->checkBox->setChecked (true);
  /// set radiobuttons
  if(stretchType==0) ui->radioButton->setChecked (true);
  if(stretchType==1) ui->radioButton_2->setChecked (true);
  if(stretchType==2) ui->radioButton_3->setChecked (true);
  if(stretchType==3) ui->radioButton_4->setChecked (true);

QString str;
str.sprintf ("scale %d, offset %d %d",scaleFactor,offset.x (),offset.y ());\
  qWarning ("scale %d, offset %d %d",scaleFactor,offset.x (),offset.y ());
  /// set Filename
  ui->lineEdit->setText (pvsFname);
  loadImage ();


  /// scale
//  ui->horizontalSlider->setRange (10,400);
  ui->horizontalSlider->setValue (scaleFactor);

  /// set Offset
  ui->horizontalScrollBar->setValue (offset.x ());
  ui->verticalScrollBar->setValue (offset.y ());

  QCompleter *completer = new QCompleter(this);
  QDirModel *dirmodel=new QDirModel(completer);
  dirmodel->setFilter (QDir::AllEntries|QDir::Hidden|QDir::System); ///
  completer->setModel(dirmodel);
  completer->setCompletionMode (QCompleter::PopupCompletion);
  ui->lineEdit->setCompleter (completer);
}


void MySettings::setConfig(KConfigGroup config)
{
 grp=config;
//ui->lineEdit->setText (grp.readEntry("textString", QString("")));
//QString str;
//str.sprintf("%f x %f",desktopSize.width(),desktopSize.height());
//ui->lblPreview_3->setText (str);

}


MySettings::~MySettings()
{ offset=QPoint(ui->horizontalScrollBar->value (),ui->verticalScrollBar->value ());
  scaleFactor=ui->horizontalSlider->value ();

  qWarning ("DE scale %d, offset %d %d",scaleFactor,offset.x (),offset.y ());
 mysetting->setValue ("ImageSource",ui->lineEdit->text ());
  qWarning (qPrintable(mysetting->fileName ()));
       mysetting->setValue ("rotated",ui->checkBox->isChecked ());

  mysetting->setValue ("stretchType",stretchType);
  mysetting->setValue ("offset",offset);
    mysetting->setValue ("scaleFactor",scaleFactor);
    qWarning ("Saved all before closing");

    qWarning ("DE scale %d, offset %d %d",scaleFactor,offset.x (),offset.y ());

  delete ui;
}

void MySettings::on_toolButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg)"));
  if(!fileName.isEmpty ())
    {
     

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

   
    emit settingsChanged ();
}

void MySettings::resizeEvent(QResizeEvent *event)
{
//   QString str;
//   double screenRatio=(double)desktopSize.width()/desktopSize.height();
//   double boxRatio=(double)ui->frame_3->width ()/ui->frame_3->height ();
//   int myheight,mywidth;
//   ui->horizontalScrollBar->setValue (0);
//   ui->verticalScrollBar->setValue (0);
//   if(screenRatio>=boxRatio)
//     {
//       mywidth=ui->frame_3->width () ;
//       myheight=int(mywidth*(desktopSize.height ()/desktopSize.width ()));
// 
//       str.sprintf("Dimensions : %f x %f \n Mapped to %f  %f",(double)desktopSize.width()/desktopSize.height(),(double)ui->frame_3->width ()/ui->frame_3->height ());
//       ui->lblPreview_3->setText (str);
// 
//       ui->desktop->resize (mywidth,myheight);
// 
// 
//     }
// else
//     {
//         myheight=ui->frame_3->height ()  ;
//         mywidth= int(myheight*(desktopSize.width ()/desktopSize.height())) ;
// 
//       str.sprintf("Dimensions : %f x %f \n Mapped to %f  %f",(double)desktopSize.width()/desktopSize.height(),(double)ui->frame_3->width ()/ui->frame_3->height ());
//       ui->lblPreview_3->setText (str);
// 
//       ui->desktop->resize (mywidth,myheight);
// 
//     }
// 
// 
// ui->lblImage->resize(mywidth,myheight);
// if(!ui->lineEdit->text ().isEmpty ())
//   {
//      QPixmap pmap;
//      pmap.load (ui->lineEdit->text ());
//      ui->horizontalScrollBar->setMaximum (pmap.width ());
// 
//      ui->verticalScrollBar->setMaximum (pmap.height ());
// 
// //     ui->verticalScrollBar->setMinimum (-pmap.height ());
// //     ui->horizontalScrollBar->setMinimum (-pmap.width ());
// 
//      if(ui->checkBox->isChecked ())
//      pmap=pmap.scaled (ui->desktop->size (),Qt::KeepAspectRatioByExpanding);
// 
// //     pmap.scroll (ui->horizontalScrollBar->value (),ui->verticalScrollBar->value (),ui->lblImage->rect ());
//   ui->lblImage->setPixmap (pmap);
// 
//   }
//     ui->desktop->move ((ui->frame_3->width ()-ui->desktop->width ())/2,(ui->frame_3->height()-ui->desktop->height())/2);
// 
// 


       QWidget::resizeEvent(event);
}








void MySettings::on_pushButton_clicked()
{
loadImage ();

}

void MySettings::applyScale()
{

  QPixmap rpmap;

//  rpmap=pmap.copy (ui->horizontalScrollBar->value (),ui->verticalScrollBar->value (),pmap.width ()-ui->horizontalScrollBar->value (),pmap.height ()-ui->verticalScrollBar->value ());

  if(stretchType==0)
    {
      applyScroll ();
      return;
    }



  if(stretchType==1)
  rpmap=pmap.scaled (ui->lblPreview->size (),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
  if(stretchType==2)
  rpmap=pmap.scaled (ui->lblPreview->size (),Qt::KeepAspectRatio,Qt::SmoothTransformation);
if(stretchType==3)
  rpmap=pmap.scaled (ui->lblPreview->size (),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);


  ui->lblPreview->setPixmap (rpmap);
}


void MySettings::applyScroll()
{

  QPixmap rpmap;
  double scale=ui->horizontalSlider->value ()/100.0;

  QPoint newoffset=QPoint(ui->horizontalScrollBar->value (),ui->verticalScrollBar->value ());
//  mysetting->setValue ("offset",offset);
//  mysetting->setValue ("scaleFactor",scaleFactor);
//  mysetting->setValue ("stretchType",stretchType);

  QRect rect=ui->lblPreview->rect ();
  rpmap=pmap.copy (newoffset.x (),newoffset.y (),rect.width ()*scale,rect.height ()*scale);

  rpmap=rpmap.scaled (ui->lblPreview->size (),Qt::KeepAspectRatio);



  ui->lblPreview->setPixmap (rpmap);
}

void MySettings::loadImage( )
{
  QString fname=ui->lineEdit->text ();

  pmap.load (fname);
  QFileInfo finfo(fname);
  if(!finfo.isFile ()) return;
  ui->horizontalScrollBar->setMaximum (pmap.width ());
  ui->verticalScrollBar->setMaximum (pmap.height());
  ui->horizontalScrollBar->setValue (offset.x ());
  ui->verticalScrollBar->setValue (offset.y ());
//  mysetting->setValue ("ImageSource",fname);

  if(ui->checkBox->isChecked ())
      {

        QTransform tform;
        tform.rotate (90);
        pmap=pmap.transformed (tform);
      }


 applyScale ();
}

void MySettings::on_verticalScrollBar_valueChanged(int value)
{
applyScroll ();
}

void MySettings::on_horizontalScrollBar_valueChanged(int value)
{
applyScroll ();
}

void MySettings::on_horizontalSlider_valueChanged(int value)
{

applyScroll ();

}

void MySettings::on_radioButton_4_clicked()
{
stretchType=3;

    applyScale ();
}

void MySettings::on_radioButton_3_clicked()
{
  stretchType=2;
    applyScale ();
}

void MySettings::on_radioButton_2_clicked()
{
  stretchType=1;
    applyScale ();
}

void MySettings::on_radioButton_clicked()
{
  stretchType=0;
    applyScale ();
}

void MySettings::on_lineEdit_editingFinished()
{
   loadImage ();
   ui->horizontalScrollBar->setValue (0);
   ui->verticalScrollBar->setValue (0);
   ui->horizontalSlider->setValue (100);

}

void MySettings::on_lineEdit_textChanged(const QString &arg1)
{
   loadImage ();
}

void MySettings::on_pushButton_2_clicked()
{



}
