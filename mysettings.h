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

public:
  explicit MySettings(QWidget *parent = 0);
  void setConfig(KConfigGroup config);
  KConfigGroup getConfig();
  void appendUrl(QString str);
  void setScaleOffset(QPointF offset,double scale);
  ~MySettings();
  
private slots:
  void on_toolButton_clicked();

signals:
  void settingsChanged();
private:
  Ui::MySettings *ui;
};

#endif // MYSETTINGS_H
