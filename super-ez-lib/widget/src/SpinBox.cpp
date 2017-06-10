#include "../include/SpinBox.hpp"
#include "../include/Layout.hpp"
#include "../include/LineEdit.hpp"
#include "../include/Button.hpp"

SpinBox::SpinBox(GraphicsItem *parent)
: Widget(parent),
  m_value(0),
  m_minimumValue(0),
  m_maximumValue(100),
  m_step(1),
  m_layout(nullptr)
{
  m_layout = new Layout(this);

  Button *minusButton = new Button("-");
  m_layout->push_back(minusButton);
  minusButton->clicked([this]() {
    setValue(m_value - m_step);
  });

  LineEdit *lineEdit = new LineEdit;
  lineEdit->setText(std::to_string(m_value));
  m_layout->push_back(lineEdit);
  lineEdit->accepted([this, lineEdit]() {
    try {
      setValue(std::stoi(lineEdit->text()));
    } catch (std::invalid_argument &err) {
      lineEdit->setText(std::to_string(m_value));
    }
  });

  Button *plusButton = new Button("+");
  m_layout->push_back(plusButton);
  plusButton->clicked([this]() {
    setValue(m_value + m_step);
  });

  valueChanged([this, lineEdit]() {
    lineEdit->setText(std::to_string(m_value));
  });

  widthChanged([this, minusButton, lineEdit, plusButton]() {
    m_layout->setWidth(width());
  });
  heightChanged([this]() {
    m_layout->setHeight(height());
  });

  m_layout->minimumWidthChanged([this]() {
    m_minimumWidthChanged();
  });
  m_layout->minimumHeightChanged([this]() {
    m_minimumHeightChanged();
  });
}

void SpinBox::setValue(int value)
{
  if (value < m_minimumValue)
    value = m_minimumValue;

  if (value > m_maximumValue)
    value = m_maximumValue;

  if (value != m_value) {
    m_value = value;
    m_valueChanged();
  }
}

void SpinBox::setMinimumValue(const int minimumValue)
{
  if (minimumValue != m_minimumValue) {
    m_minimumValue = minimumValue;
    setValue(m_value);
    m_minimumValueChanged();
  }
}

void SpinBox::setMaximumValue(const int maximumValue)
{
  if (maximumValue != m_maximumValue) {
    m_maximumValue = maximumValue;
    setValue(m_value);
    m_maximumValueChanged();
  }
}

size_t SpinBox::minimumWidth() const
{
  return m_layout->minimumWidth();
}

size_t SpinBox::minimumHeight() const
{
  return m_layout->minimumHeight();
}