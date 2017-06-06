#include "../include/GraphicsSquare.hpp"
#include "../include/GraphicsPoint.hpp"
#include "../include/GraphicsAnchor.hpp"
#include <boost/bind.hpp>
#include <cmath>

GraphicsSquare::GraphicsSquare(GraphicsItem *parent)
: GraphicsItem(parent),
  m_topLeft({boost::bind(&GraphicsSquare::corrector, _1, boost::cref(m_bottomRight))}, &position()),
  m_bottomRight({boost::bind(&GraphicsSquare::corrector, _1, boost::cref(m_topLeft))}, &position())
{}

void GraphicsSquare::meDraw(Canvas *canvas)
{
  if (canvas)
    canvas->drawRectangle(topLeft(), bottomRight(), isFill());
}

bool GraphicsSquare::meIsOver(const Point &absoluteP)
{
  return topLeft() < absoluteP and absoluteP < bottomRight();
}

Point GraphicsSquare::corrector(const Point &pos, const Point &corner)
{
  Point diffP(pos - corner);
  double radius = std::hypot(diffP.x(), diffP.y());

  Point res(std::cos(std::sqrt(2)/2.0)*radius, std::sin(std::sqrt(2)/2.0)*radius);

  if (diffP.x() < 0)
    res.setX(-res.x());

  if (diffP.y() < 0)
    res.setY(-res.y());

  return corner + res;
}
