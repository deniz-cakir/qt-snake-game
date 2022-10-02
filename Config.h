#ifndef CONFIG_H
#define CONFIG_H

#include <QBrush>

// Size of one rect element
const int elementSize = 10;

const int snakeSize = 8;

const int elementRadius = 2;

const int elementCount = 70;

const int sizeOfArea = elementSize * elementCount;

const int pace = 100;

const int scoreStep = 100;

//*******************************************

const QColor backgroundColor =  QColor(qRgba (47, 79, 79, 0));

const QBrush backgroundBrush = QBrush(backgroundColor);

//********************************************

const QColor elementColor = QColor(qRgba (128, 128, 128, 0));

const QBrush elementBrush = QBrush (elementColor);

enum Direction {top, right, left, bottom};

enum Vector {x, y, ee, rr};

#endif // CONFIG_H

