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
}

void MySettings::setConfig(KConfigGroup config)
{
grp=config;
ui->lineEdit->setText (grp.readEntry("textString", QString("")));
}


MySettings::~MySettings()
{
  delete ui;
}

void MySettings::on_toolButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"~/",tr("Images (*.png *.xpm *.jpg)"));
  if(!fileName.isEmpty ())
    {

      ui->lineEdit->setText (fileName);
     QPixmap pmap;
      pmap.load (fileName);
      ui->lblImage->setPixmap (pmap);

      if(ui->lineEdit->text ()!=fileName)
        emit settingsChanged();

    }

}


KConfigGroup MySettings::getConfig()
{
  return grp;
}

void MySettings::appendUrl(QString str)
{
    grp.writeEntry("textString", str);
    ui->lineEdit->setText (str);
    emit settingsChanged ();
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
