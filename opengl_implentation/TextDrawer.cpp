#include			"TextDrawer.hh"

TextDrawer::TextDrawer()
{}

TextDrawer::~TextDrawer()
{}

TextDrawer			*TextDrawer::getInstance()
{
  static TextDrawer		that;

  return &that;
}

void				TextDrawer::draw()
{
  t_iter			it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->draw();
      ++it;
    }
  this->list_.clear();
}

void				TextDrawer::push(gdl::Text * text)
{
  this->list_.push_back(text);
}
