#ifndef GRAPHICSRECTANGLE_HPP
#define GRAPHICSRECTANGLE_HPP

/*!
 * \file GraphicsTriangle.hpp
 * \brief Classe GraphicsTriangle
 * \author Loïc Escales, Leo Sudreau
 * \version 0.1
 * \date 23 mai 2017
 */

#include <cmath>
#include "GraphicsItem.hpp"

/*!
 * \class GraphicsRectangle
 * \brief Permet la creation d'un rectangle
 *
 *
 */

class GraphicsRectangle : public GraphicsItem
{
public:

  /*!
   * \brief Constructeur par default de la classe GraphicsRectangle.
   *
   * Crée une instance de GraphicsRectangle.
   *
   */

  explicit GraphicsRectangle(GraphicsItem *parent = nullptr);

  /*!
   * \brief recupere les coordonnées.
   *
   * Crée une instance de GraphicsRectangle.
   *
   */

  inline Point &topLeft() { return m_topLeft; }

  inline Point &bottomRight() { return m_bottomRight; }

  inline GraphicsTypes type() const { return RectangleType; }

  inline size_t width() const { return std::abs(m_bottomRight.x() - m_topLeft.x()); }

  void setWidth(const size_t width);

  inline size_t height() const { return std::abs(m_bottomRight.y() - m_topLeft.y()); }

  void setHeight(const size_t height);

protected:
  void meDraw(Canvas *canvas);
  bool meIsOver(const Point &absoluteP);

private:
  //FIXME topLeft vraiment utile ?
  Point m_topLeft, m_bottomRight;
};


#endif
