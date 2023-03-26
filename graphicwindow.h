#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QtWidgets>

class GraphicWindow : public QGraphicsWidget {
  Q_OBJECT
  
 public:
  explicit GraphicWindow (QGraphicsWidget *parent = 0);
  ~GraphicWindow();
  
}; 


#endif
