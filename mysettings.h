#ifndef MYSETTINGS_H
#define MYSETTINGS_H

#include <QWidget>
#include <KConfigGroup>
#include <QPicture>
#include <QSettings>
namespace Ui {
  class MySettings;
}

class MySettings : public QWidget
{
  Q_OBJECT
public:
  KConfigGroup grp;
  QSettings *mysetting;
  QRectF desktopSize;
  int stretchType;
  int scaleFactor;
  QPoint offset;
  QString pvsFname;


  bool scale;


   QPixmap pmap;

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


    void init();

    void on_pushButton_clicked();
    void applyScale();
    void applyScroll();
    void loadImage();

    void on_radioButton_4_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

signals:
  void settingsChanged();
private:
  Ui::MySettings *ui;
};

#endif // MYSETTINGS_H
