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

  qWarning ("scale %d, offset %d %d",scaleFactor,offset.x (),offset.y ());
  /// set Filename
  ui->lineEdit->setText (pvsFname);
  loadImage ();


  /// scale
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
{
  offset=QPoint(ui->horizontalScrollBar->value (),ui->verticalScrollBar->value ());
  scaleFactor=ui->horizontalSlider->value ();
  mysetting->setValue ("ImageSource",ui->lineEdit->text ());
  mysetting->setValue ("rotated",ui->checkBox->isChecked ());

  mysetting->setValue ("stretchType",stretchType);
  mysetting->setValue ("offset",offset);
  mysetting->setValue ("scaleFactor",scaleFactor);
  qWarning ("Saved all before closing");


  delete ui;
}

void MySettings::on_toolButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Images (*.png *.xpm *.jpg)"));
  if(!fileName.isEmpty ())
    {

ui->lineEdit->setText (fileName);
    }

}


KConfigGroup MySettings::getConfig()
{
  return grp;
}
void MySettings::setScreen(QRectF rect)
{
  desktopSize=rect;
  QSizeF x=rect.size ();

  x.scale (ui->frame_4->width ()-10,ui->frame_4->height (),Qt::KeepAspectRatio);
ui->frame_2->setMaximumSize (x.width (),x.height ());
}

void MySettings::appendUrl(QString str)
{


  emit settingsChanged ();
}

void MySettings::resizeEvent(QResizeEvent *event)
{

  QSizeF x=desktopSize.size ();

  x.scale (ui->frame_4->width ()-10,ui->frame_4->height (),Qt::KeepAspectRatio);
ui->frame_2->setMaximumSize (x.width (),x.height ());



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
