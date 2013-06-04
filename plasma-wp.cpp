#include <QPainter>
#include <complex>
#include <QMessageBox>
#include "plasma-wp.h"
#include <QAction>
#include <mysettings.h>
PlasmaWp::PlasmaWp(QObject *parent, const QVariantList &args)
        : Plasma::Wallpaper(parent, args)
{
        fontsize=1;

        image=KUrl("/home/ssk/.face");
//	if ( image.isLocalFile() )
	txt=image.toLocalFile (); //"Hello World";
	scale=1;
	offset=QPointF(0,0);
	origimg=QImage(image.toLocalFile ());
	 img = QImage(image.toLocalFile ());
	connect(this,SIGNAL(Wallpaper::urlDropped(KUrl)),this,SLOT(showImage(KUrl)));
	QAction *act;

	if(contextualActions ().count ()>0)
	  {
	    act=contextualActions ().first ();
	    txt=act->text();
	  }
	settingwidget=NULL;
}
void PlasmaWp::showImage(const KUrl &url)
{


  txt="Something dropped";
        image=url;
    origimg = QImage(image.toLocalFile ());
    txt=image.toLocalFile (); //"Hello World";
    scale=1;
    offset=QPointF(0,0);
//    int ret = QMessageBox::warning(0, tr("My Application"),
//                                   tr("The document has been modified.\n"
//                                      "Do you want to save your changes?"),
//                                   QMessageBox::Save);
//  QMessageBox::information (this,"Simple","Information message dropdd"+txt,QMessageBox::Ok,);
    //	txt="Unknown "+image.fileName ();
        emit Wallpaper::update(boundingRect());

}

void PlasmaWp::addUrls (const KUrl::List &urls)
{
  if(settingwidget==NULL)
    {
      settingwidget=new MySettings;
        connect(settingwidget,SIGNAL(settingsChanged()),this,SLOT(settingsModified()));

    }

           foreach (const KUrl &url, urls) {
               settingwidget->appendUrl(url.toLocalFile ());
               scale=1;
               offset=QPointF(0,0);
//                 showImage (url);
             }

}

void PlasmaWp::settingsModified()
{
  KConfigGroup cgrp;
  if(!settingwidget) return;

  cgrp=settingwidget->getConfig ();
  textString = cgrp.readEntry("textString", QString(""));


  if(!textString.isEmpty ())
    {
      KUrl url(textString);
      showImage(url);
    }
}

void PlasmaWp::updateSettings()
{
  if(settingwidget==NULL)
    {
      settingwidget=new MySettings;
        connect(settingwidget,SIGNAL(settingsChanged()),this,SLOT(settingsModified()));
    }

  settingwidget->setScaleOffset(offset,scale);
  emit update (boundingRect ());

}

void PlasmaWp::wheelEvent(QGraphicsSceneWheelEvent* event)
{
  if(event->modifiers ()==Qt::ShiftModifier)
    {
      int del=event->delta()/120;
      if(del>0)
        scale=scale+0.1;
      else
        scale=scale-0.1;
      if(scale==0) scale=1;

      //Plasma::Wallpaper::wheelEvent(event);
      event->accept();
      updateSettings ();
//      emit Wallpaper::update(boundingRect());
    }
  if(event->modifiers ()==Qt::ControlModifier)
{
      int del=event->delta()/60;
    offset.setX (offset.x ()+del);
    event->accept();
    updateSettings ();
//    emit Wallpaper::update(boundingRect());
    }
  if(event->modifiers ()==Qt::AltModifier)
{
      int del=event->delta()/60;
    offset.setY (offset.y ()+del);
    updateSettings ();
    event->accept();
//    emit Wallpaper::update(boundingRect());
    }
}

void PlasmaWp::paint(QPainter *painter, const QRectF& exposedRect)
{

    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
 
    painter->setPen(Qt::blue);
    painter->setFont(QFont("Arial", 10));

QPointF zeros(0,0);
    if(scale!=1)
      {
        img=origimg.scaled (origimg.width ()*scale,origimg.height()*scale);


        QRectF rc;
        rc.setTopLeft (offset);
        rc.setWidth (std::min(img.width (),int(boundingRect ().width ())));
        rc.setHeight (std::min(img.height (),int(boundingRect ().height ())));
    //    rc.setHeight (img.height ());

        if(offset.x ()==0 && offset.y()==0)
          painter->drawImage(boundingRect (),img);
        else
         painter->drawImage(boundingRect (),img,rc);
      }
  else
      {
        img=origimg;
//        QRectF rc;
//        rc.setTopLeft (offset);
//        rc.setWidth (boundingRect ().width ());
//        rc.setHeight (boundingRect ().height ());
//        painter->drawImage(boundingRect (),img,rc);
//        QRectF rc;
//        rc.setTopLeft (offset);
//        rc.setWidth (std::min(img.width (),int(boundingRect ().width ())));
//        rc.setHeight (std::min(img.height (),int(boundingRect ().height ())));
        if(offset.x ()==0 && offset.y()==0)
         painter->drawImage(boundingRect (),img);
        else
          painter->drawImage(0,0,img,offset.x (),offset.y ());
      }




}


void PlasmaWp::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//  if(event->button ()==Qt::LeftButton)
    {
     txt="Move";
      offset=event->screenPos ();
      offset=QPointF(500,500);
    //  offset=(event->lastPos ()-event->pos ());


Wallpaper::mouseMoveEvent (event);
      emit update (boundingRect ());
  }
}

void PlasmaWp::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{  offset=event->screenPos ();
   offset=QPointF(100,100);
    txt="Pressed";
 //  offset=(event->lastPos ()-event->pos ());
     Wallpaper::mouseReleaseEvent (event);
   emit update (boundingRect ());

}
 



void PlasmaWp::init(const KConfigGroup &config)
{
  if(settingwidget==NULL)
    {
      settingwidget=new MySettings;
        connect(settingwidget,SIGNAL(settingsChanged()),this,SLOT(settingsModified()));

    }
     settingwidget->setConfig (config);
     QString fname=config.readEntry("textString","");
     offset=config.readEntry("offset",QPointF(0,0));
     scale=config.readEntry("scale",1);

     if(!fname.isEmpty ())
       {
         KUrl url(fname);
         showImage(url);
       }
//    textString = config.readEntry("textString", QString(""));
//    emit update(boundingRect());
}

void PlasmaWp::save(KConfigGroup &config)
{
  if(settingwidget==NULL)
    {
      settingwidget=new MySettings;
        connect(settingwidget,SIGNAL(settingsChanged()),this,SLOT(settingsModified()));

    }
     settingwidget->setConfig (config);
}

QWidget *PlasmaWp::createConfigurationInterface(QWidget *parent)
{
  if(settingwidget==NULL)
    {
      settingwidget=new MySettings(parent);
        connect(settingwidget,SIGNAL(settingsChanged()),this,SLOT(settingsModified()));
    }
  else
    settingwidget->setParent (parent);

//  tmp->show ();

  return settingwidget;
}

#include "plasma-wp.moc"
