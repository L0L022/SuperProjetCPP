#include "../include/GraphicsTriangle.hpp"

GraphicsTriangle::GraphicsTriangle(const Ptr &parent)
: GraphicsShape(parent)
{
  m_points.emplace_back(&position());
  m_points.emplace_back(&position());
  m_points.emplace_back(&position());
}
