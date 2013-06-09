#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QWidget>
#include <KConfigGroup>
#include <QPicture>
namespace Ui {
  class MySettings;
}

class MySettings : public QWidget
{
  Q_OBJECT
public:
  KConfigGroup grp;
  QRectF desktopSize;
  bool scale;
  QPoint offset;
public:
  explicit MySettings(QWidget *parent = 0);
  void setConfig(KConfigGroup config);
  KConfigGroup getConfig();
  void setScreen(QRectF rect);
  void appendUrl(QString str);
  void resizeEvent (QResizeEvent *);
  void setScaleOffset(QPointF offset,double scale);
  ~MySettings();
  
private slots:
  void on_toolButton_clicked();

  void on_horizontalSlider_valueChanged(int value);

  void on_horizontalScrollBar_valueChanged(int value);

  void on_verticalScrollBar_valueChanged(int value);
  void scroll();
  void on_checkBox_clicked();

  void on_lineEdit_returnPressed();

signals:
  void settingsChanged();
private:
  Ui::MySettings *ui;
};

#endif // MYSETTINGS_H
