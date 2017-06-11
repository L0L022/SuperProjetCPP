#include "../include/MainWindow.hpp"

#include "ToolsWindow.hpp"
#include <LineEdit.hpp>
#include <Button.hpp>
#include "ConfigItem.hpp"

MainWindow::MainWindow()
: Window(400, 400, "SuperProjetCPP"),
  m_scene(nullptr),
  m_layout(nullptr),
  m_config(nullptr),
  currentItem(nullptr)
{
  m_scene = GraphicsItem::make<GraphicsItem>();

  m_layout = GraphicsItem::make<Layout>(m_scene);
  m_layout->setSpacing(10);
  m_layout->position().set(5, 5);

  auto tool = GraphicsItem::make<ToolsWindow>();
  m_layout->push_back(tool);

  organize();
}

void MainWindow::drawEvent()
{
  m_scene->draw(&canvas());
}

void MainWindow::resizeEvent(const size_t width, const size_t height)
{
  organize();
}

void MainWindow::updateEvent(const unsigned int time)
{
  m_scene->update(time);
  drawRequest();
}

void MainWindow::handleEvent(const Event &event)
{
  m_scene->handleEvent(event);
  drawRequest();
}

void MainWindow::organize()
{
  m_layout->setWidth(width());
  //m_layout->setHeight(height()*0.65);
}
