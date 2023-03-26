#ifndef LAYOUTITEM_H
#define LAYOUTITEM_H

#include <QGraphicsLayoutItem>
#include <QGraphicsItem>
#include <QPixmap>


class LayoutItem : public QGraphicsLayoutItem, public QGraphicsItem
{
 public:
  LayoutItem(QGraphicsItem *parent = nullptr);
}; 

#endif // LAYOUTITEM_H
