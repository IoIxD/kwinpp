#pragma once

#ifndef KWINPP_NO_QT
#include <QIcon>
#include <QList>
#include <QPalette>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QRegion>
#include <QSize>
#include <QSizeF>
#include <QString>
#include <QStringList>
#include <QUuid>
#include <Qt>
#endif

namespace KWin {
#ifndef KWINPP_NO_QT
using String = QString;
using StringList = QStringList;
template <typename T> using List = QList<T>;
using Uuid = QUuid;
using Region = QRegion;
using Point = QPoint;
using PointF = QPointF;
using Size = QSize;
using SizeF = QSizeF;
using Rect = QRect;
using RectF = QRectF;
using Edge = Qt::Edge;
#else
using String = std::string;
using StringList = std::vector<std::string>;
template <typename T> using List = std::vector<T>;
using Uuid = std::string; // as formatted by QUuid::toString()
enum class Edge {
  TopEdge = 0x1,
  LeftEdge = 0x2,
  RightEdge = 0x4,
  BottomEdge = 0x8,
};

class Point {
public:
  constexpr Point() = default;
  constexpr Point(int x, int y) : xp(x), yp(y) {}

  constexpr int x() const { return xp; }
  constexpr int y() const { return yp; }
  constexpr void setX(int x) { xp = x; }
  constexpr void setY(int y) { yp = y; }

private:
  int xp = 0;
  int yp = 0;
};

class PointF {
public:
  constexpr PointF() = default;
  constexpr PointF(double x, double y) : xp(x), yp(y) {}

  constexpr double x() const { return xp; }
  constexpr double y() const { return yp; }
  constexpr void setX(double x) { xp = x; }
  constexpr void setY(double y) { yp = y; }

private:
  double xp = 0.0;
  double yp = 0.0;
};

class Size {
public:
  constexpr Size() = default;
  constexpr Size(int width, int height) : wd(width), ht(height) {}

  constexpr int width() const { return wd; }
  constexpr int height() const { return ht; }
  constexpr void setWidth(int width) { wd = width; }
  constexpr void setHeight(int height) { ht = height; }

private:
  int wd = -1;
  int ht = -1;
};

class SizeF {
public:
  constexpr SizeF() = default;
  constexpr SizeF(double width, double height) : wd(width), ht(height) {}

  constexpr double width() const { return wd; }
  constexpr double height() const { return ht; }
  constexpr void setWidth(double width) { wd = width; }
  constexpr void setHeight(double height) { ht = height; }

private:
  double wd = -1.0;
  double ht = -1.0;
};

class Rect {
public:
  constexpr Rect() = default;
  constexpr Rect(int x, int y, int width, int height)
      : xp(x), yp(y), wd(width), ht(height) {}

  constexpr int x() const { return xp; }
  constexpr int y() const { return yp; }
  constexpr int width() const { return wd; }
  constexpr int height() const { return ht; }
  constexpr void setX(int x) { xp = x; }
  constexpr void setY(int y) { yp = y; }
  constexpr void setWidth(int width) { wd = width; }
  constexpr void setHeight(int height) { ht = height; }

private:
  int xp = 0;
  int yp = 0;
  int wd = 0;
  int ht = 0;
};

class RectF {
public:
  constexpr RectF() = default;
  constexpr RectF(double x, double y, double width, double height)
      : xp(x), yp(y), wd(width), ht(height) {}

  constexpr double x() const { return xp; }
  constexpr double y() const { return yp; }
  constexpr double width() const { return wd; }
  constexpr double height() const { return ht; }
  constexpr void setX(double x) { xp = x; }
  constexpr void setY(double y) { yp = y; }
  constexpr void setWidth(double width) { wd = width; }
  constexpr void setHeight(double height) { ht = height; }

private:
  double xp = 0.0;
  double yp = 0.0;
  double wd = 0.0;
  double ht = 0.0;
};

using Region = std::vector<Rect>;

#endif

} // namespace KWin
