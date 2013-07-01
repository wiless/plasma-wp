#ifndef PLASMAWP_H
#define PLASMAWP_H

#include <Plasma/Wallpaper>
#include <QGraphicsSceneMouseEvent>
#include <KUrl>
#include <mysettings.h>

class PlasmaWp : public Plasma::Wallpaper
{
    Q_OBJECT
    

    private:
	int fontsize;
	double scale;
	QString txt;
	KUrl image;
	bool type;
	QImage img;
	QImage origimg;
	 
	
	/// NEW approach
	int stretchType;
	int scaleFactor;
	QPoint offset;
	QString pvsFname;
	QPixmap pmap;
	bool rotated;
	QPixmap rpmap;

	///
private:
QSettings *mysetting;
      MySettings *settingwidget;
               QString textString;     // New
    public:
	    
	PlasmaWp(QObject* parent, const QVariantList& args);
	void wheelEvent	(QGraphicsSceneWheelEvent * event);	
        void paint(QPainter* painter, const QRectF& exposedRect);
      //  bool supportsMimetype (const QString &mimetype) const;
        void mouseMoveEvent (QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);
/// Configuration related
public:
        void save(KConfigGroup &config);
        QWidget* createConfigurationInterface(QWidget *parent);
protected:
        void init (const KConfigGroup &config);

public slots:
	void showImage(const KUrl &url);
	void addUrls (const KUrl::List &urls);

	void applyScale();
	void applyScroll();
	void loadImage();
protected slots:                            // New
      void settingsModified();                // New
      void updateSettings();
Q_SIGNALS:
        void settingsChanged(bool modified);    // New
};
 
K_EXPORT_PLASMA_WALLPAPER(plasma Wallpaper, PlasmaWp)
 
#endif // PLASMA-WP_H
