#ifndef GRAPHICSLINE_HPP
#define GRAPHICSLINE_HPP

#include "GraphicsShape.hpp"

/*!
 * \class GraphicsLine
 * \brief Une ligne
 * \ingroup graphics
 */

class GraphicsLine : public GraphicsShape
{
public:
  explicit GraphicsLine(const Id &parent = boost::uuids::nil_generator()());
  explicit GraphicsLine(const Ptr &parent);
  explicit GraphicsLine(const GraphicsItem *parent);

  inline const Point &first() const { return m_points[0]; }
  inline Point &first() { return m_points[0]; }

  inline const Point &second() const { return m_points[1]; }
  inline Point &second() { return m_points[1]; }
};

#endif
