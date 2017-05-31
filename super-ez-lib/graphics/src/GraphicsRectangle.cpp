#include "../include/GraphicsRectangle.hpp"
#include "../include/GraphicsPoint.hpp"
#include "../include/GraphicsAnchor.hpp"


GraphicsRectangle::GraphicsRectangle(GraphicsItem *parent)
: GraphicsItem(parent),
  m_topLeft(&position()),
  m_bottomRight(&position())
{
}

void GraphicsRectangle::meDraw(Canvas *canvas)
{
  if (canvas)
    canvas->drawRectangle(m_topLeft, m_bottomRight, isFill());
}

bool GraphicsRectangle::meIsOver(const Point &absoluteP)
{
  return m_topLeft < absoluteP and absoluteP < m_bottomRight;
}

void GraphicsRectangle::setWidth(const size_t width)
{
  m_bottomRight.setX(width);
}

void GraphicsRectangle::setHeight(const size_t height)
{
  m_bottomRight.setY(height);
}
