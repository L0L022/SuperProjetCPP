#ifndef GRAPHICSITEM_HPP
#define GRAPHICSITEM_HPP

#include <vector>
#include <map>
#include <memory>
#include <Color.hpp>
#include <Canvas.hpp>
#include <Event.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/core/noncopyable.hpp>

/**
 * \defgroup graphics Graphics
 * \brief Classes pour dessiner
 */

/*!
 * \class GraphicsItem
 * \brief Classe de base
 * \ingroup graphics
 */

class GraphicsItem : private boost::noncopyable {
public:
  typedef boost::uuids::uuid Id;
  typedef std::shared_ptr<GraphicsItem> Ptr;
  typedef std::vector<GraphicsItem*> GraphicsItemList;

  enum GraphicsTypes { //mouse movable type ?
    UndefinedType = 0x0,
    ItemType = 0x1,
    PointType = 0x2,
    TextType = 0x4,
    ShapeType = 0x6,
    LineType = 0x8,
    TriangleType = 0x10,
    RectangleType = 0x12,
    PolygonType = 0x14,
    AnchorType = 0x16,
    CircleType = 0x18,
    EllipseType = 0x20,
    SquareType = 0x22,
    AnimationType = 0x24,
    BlinkAnimationType = 0x26
  };

  enum SearchTypes {
    DirectChildren,
    ChildrenRecursively
  };

  explicit GraphicsItem(const Id &parent = boost::uuids::nil_generator()());
  explicit GraphicsItem(const Ptr &parent);
  explicit GraphicsItem(const GraphicsItem *parent);

  virtual ~GraphicsItem();

  inline Id id() const { return m_id; }
  inline Id parentId() const { return m_parent; }
  inline Ptr parent() const { return m_graphicsItems[m_parent]; }

  void setParent(const Id &parent = boost::uuids::nil_generator()());
  void setParent(const Ptr &parent);
  void setParent(const GraphicsItem *parent);

  virtual GraphicsTypes type() const {
    return ItemType;
  }

  GraphicsItemList children(const GraphicsTypes filter = UndefinedType, const SearchTypes option = ChildrenRecursively) const;

  inline Point position() const { return m_position; }
  inline Point &position() { return m_position; }

  Color color() const {
    return m_color;
  }

  int z() const {
    return m_z;
  }

  void setZ(const int z);

  void setColor(const Color color) {
    m_color = color;
  }

  unsigned int thick() const {
    return m_thick;
  }

  void setThick(unsigned int thick = 1) {
    m_thick = thick;
  }

  bool isFill() const {
    return m_isFill;
  }

  void setFill(const bool fill) {
    m_isFill = fill;
  }

  bool isVisible() const {
    return m_isVisible;
  }

  void setVisible(const bool isVisible = true) {
    m_isVisible = isVisible;
  }

  void draw(Canvas *canvas);

  void update(const unsigned int time);

  void handleEvent(const Event &event);

  bool isOver(const Point &p);

  inline static GraphicsItem *focusItem() { return m_focusItem; };
  inline static void setFocusItem(GraphicsItem *item) { m_focusItem = item; }
  inline bool hasFocus() const { return m_focusItem == this; };

  template<class T, class... Args>
  static std::shared_ptr<T> make(Args&&... args);

protected:
  virtual void meDraw(Canvas *canvas) {}
  virtual void meUpdate(const unsigned int time) {}
  virtual void meHandleEvent(const Event &event) {}
  virtual bool meIsOver(const Point &absoluteP) { return m_position == absoluteP; }

private:
  void sortChildren();

private:
  Id m_id;
  Id m_parent;
  std::vector<Id> m_children;
  static GraphicsItem *m_focusItem;
  Point m_position;
  int m_z;
  Color m_color;
  unsigned int m_thick;
  bool m_isFill;
  bool m_isVisible;

  static std::map<Id, Ptr> m_graphicsItems;
};

template<class T, class... Args>
std::shared_ptr<T> GraphicsItem::make(Args&&... args)
{
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
  m_graphicsItems[ptr->id()] = ptr;

  auto parent = ptr->parent();
  if (parent)
    parent->sortChildren();

  return ptr;
}

bool operator==(const GraphicsItem &l, const GraphicsItem &r);
bool operator!=(const GraphicsItem &l, const GraphicsItem &r);

#endif
