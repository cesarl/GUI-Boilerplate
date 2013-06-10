#include				<iostream>
#include				<sstream>
#include				"GuiComponent.hh"

//////////////////
// GuiComponent //
//////////////////

GuiComponent::GuiComponent() :
  visible_(true),
  parent_(NULL),
  selectable_(false),
  option_(NULL),
  color_(al_map_rgb(150, 150, 150))
{}

GuiComponent::~GuiComponent()
{}

void					GuiComponent::setPosition(Vector3d const & pos)
{
  this->position_ = pos;
}

void					GuiComponent::setVisible(bool val)
{
  this->visible_ = val;
}

void					GuiComponent::draw(Vector3d *position)
{
  (void)(position);
}

void					GuiComponent::event(ALLEGRO_EVENT *event)
{
  (void)(event);
}

Vector3d				&GuiComponent::getPosition()
{
  return this->position_;
}

void					GuiComponent::setParent(GuiComponent *parent)
{
  this->parent_ = parent;
}

GuiComponent				*GuiComponent::getParent() const
{
  return this->parent_;
}

bool					GuiComponent::isSelectable() const
{
  return this->selectable_;
}

void					GuiComponent::select(bool val)
{
  (void)(val);
}

void					GuiComponent::attachOption(Option *option)
{
  this->option_ = option;
}

void					GuiComponent::saveOptionValue()
{}

void					GuiComponent::importOptionValue()
{}

void					GuiComponent::setColor(ALLEGRO_COLOR color)
{
  this->color_ = color;
}

void					GuiComponent::setId(int id)
{
  this->id_ = id;
}

int					GuiComponent::getId() const
{
  return this->id_;
}

///////////////////
// GuiSelectable //
///////////////////

GuiSelectable::GuiSelectable() :
  GuiComponent(),
  selected_(false),
  pressAction_(NULL),
  selectAction_(NULL),
  unselectAction_(NULL),
  deleteAction_(NULL)
{
  this->selectable_ = true;
}

GuiSelectable::~GuiSelectable()
{}

void					GuiSelectable::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectable::pressed()
{
  if (this->pressAction_)
    {
      this->pressAction_(this);
    }
}

void					GuiSelectable::setPressAction(void (* function)(GuiComponent *gui))
{
  this->pressAction_ = function;
}

void					GuiSelectable::setSelectAction(void (* function)(GuiComponent *gui))
{
  this->selectAction_ = function;
}

void					GuiSelectable::setUnselectAction(void (* function)(GuiComponent *gui))
{
  this->unselectAction_ = function;
}

void					GuiSelectable::setDeleteAction(void (* function)(GuiComponent *gui))
{
  this->deleteAction_ = function;
}

void					GuiSelectable::event(ALLEGRO_EVENT *event)
{
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_ENTER:
      this->pressed();
      break;
    }
}

/////////////
// GuiText //
/////////////

GuiText::GuiText(std::string const & val) :
  GuiComponent(),
  val_(val),
  font_(NULL)
{
}


GuiText::~GuiText()
{}

void					GuiText::operator=(std::string const & str)
{
  this->val_ = str;
  this->saveOptionValue();
}

void					GuiText::operator+=(std::string const & str)
{
  this->val_ += str;
  this->saveOptionValue();
}

void					GuiText::setFont(ALLEGRO_FONT *font)
{
  this->font_ = font;
}

void					GuiText::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  if (!this->font_)
    return;
  al_draw_text(this->font_ , this->color_, vec.getX(), vec.getY(), 0, this->val_.c_str());
}

void					GuiText::saveOptionValue()
{
  if (!this->option_)
    return;
  static_cast<OptionValue<std::string>*>(this->option_)->setValue(this->val_);
}

void					GuiText::importOptionValue()
{
  OptionValue<std::string>		*value;

  if (!this->option_)
    return;
  value = dynamic_cast<OptionValue<std::string>*>(this->option_);
  if (!value)
    return;
  value->setValue(this->val_);
}


///////////////
// GuiNumber //
///////////////

GuiNumber::GuiNumber(int val) :
  GuiComponent(),
  val_(val),
  font_(NULL)
{
  this->updateStr();
}

GuiNumber::~GuiNumber()
{}

void					GuiNumber::operator=(int val)
{
  this->val_ = val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator+=(int val)
{
  this->val_ += val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator-=(int val)
{
  this->val_ -= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator*=(int val)
{
  this->val_ *= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::operator/=(int val)
{
  this->val_ /= val;
  this->updateStr();
  this->saveOptionValue();
}

void					GuiNumber::setFont(ALLEGRO_FONT *font)
{
  this->font_ = font;
}

void					GuiNumber::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  if (!this->font_)
    return;
  al_draw_text(this->font_ , this->color_, vec.getX(), vec.getY(), 0, this->strVal_.c_str());
}

void					GuiNumber::updateStr()
{
  std::ostringstream			convert;

  convert << this->val_;
  this->strVal_ = convert.str();
}

int					GuiNumber::getVal() const
{
  return this->val_;
}

void					GuiNumber::saveOptionValue()
{
  if (!this->option_)
    return;
  static_cast<OptionValue<int>*>(this->option_)->setValue(this->val_);
}

void					GuiNumber::importOptionValue()
{
  OptionValue<int>			*value;

  if (!this->option_)
    return;
  value = dynamic_cast<OptionValue<int>*>(this->option_);
  if (!value)
    return;
  value->setValue(this->val_);
}

///////////////////////
// GuiSelectableText //
///////////////////////

GuiSelectableText::GuiSelectableText() :
  GuiSelectable()
{}

GuiSelectableText::~GuiSelectableText()
{}

void					GuiSelectableText::setupText(std::string const & val, ALLEGRO_FONT *font)
{
  this->text_ = val;
  this->text_.setFont(font);
}

GuiText					*GuiSelectableText::getText()
{
  return &(this->text_);
}

void					GuiSelectableText::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  this->text_.draw(&vec);
}

void					GuiSelectableText::attachOption(Option *option)
{
  this->text_.attachOption(option);
}

void					GuiSelectableText::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
      this->text_.saveOptionValue();
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectableText::setColor(ALLEGRO_COLOR color)
{
  this->text_.setColor(color);
}

/////////////////////////
// GuiSelectableNumber //
/////////////////////////

GuiSelectableNumber::GuiSelectableNumber() :
  GuiSelectable()
{}

GuiSelectableNumber::~GuiSelectableNumber()
{}

void					GuiSelectableNumber::setupNumber(int val, ALLEGRO_FONT *font)
{
  this->nbr_ = val;
  this->nbr_.setFont(font);
}

GuiNumber				*GuiSelectableNumber::getNumber()
{
  return &(this->nbr_);
}

int					GuiSelectableNumber::getVal() const
{
  return this->nbr_.getVal();
}

void					GuiSelectableNumber::draw(Vector3d *position)
{
  Vector3d				vec;

  vec = this->position_;
  if (position)
    vec += *position;
  this->nbr_.draw(&vec);
}

void					GuiSelectableNumber::attachOption(Option *option)
{
  this->nbr_.attachOption(option);
}

void					GuiSelectableNumber::select(bool val)
{
  this->selected_ = val;
  if (val && this->selectAction_)
    {
      this->selectAction_(this);
      this->nbr_.saveOptionValue();
    }
  if (!val && this->unselectAction_)
    {
      this->unselectAction_(this);
    }
}

void					GuiSelectableNumber::setColor(ALLEGRO_COLOR color)
{
  this->nbr_.setColor(color);
}

////////////////////////
// GuiSelectableGroup //
////////////////////////

GuiSelectableGroup::GuiSelectableGroup() :
  GuiSelectable(),
  horizontal_(false)
{}

GuiSelectableGroup::~GuiSelectableGroup()
{}

void					GuiSelectableGroup::clear()
{
  t_iter				it;

  it = this->sellist_.begin();
  while (it != this->sellist_.end())
    {
      delete *it;
      ++it;
    }
  this->sellist_.clear();
  this->selected_ = this->sellist_.end();
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      delete *it;
      ++it;
    }
  this->list_.clear();
}

void					GuiSelectableGroup::pushComponent(GuiComponent *component)
{
  if (component->isSelectable())
    this->sellist_.push_back(component);
  else
    this->list_.push_back(component);
  component->setParent(this);
  this->selectFirst();
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(true);
  if (component->isSelectable() && this->option_)
    component->attachOption(this->option_);
}

void					GuiSelectableGroup::draw(Vector3d *position)
{
  Vector3d				vec;
  t_iter				it;

  vec = this->position_;
  if (position)
    vec += *position;
  if (this->list_.size() > 0)
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  (*it)->draw(&vec);
	  ++it;
	}
    }
  if (this->sellist_.size() > 0)
    {
      it = this->sellist_.begin();
      while (it != this->sellist_.end())
	{
	  (*it)->draw(&vec);
	  ++it;
	}
    }
}

void					GuiSelectableGroup::setHorizontal(bool val)
{
  this->horizontal_ = val;
}

void					GuiSelectableGroup::event(ALLEGRO_EVENT *event)
{
  t_iter				it;

  if (this->selected_ != this->sellist_.end()
      && (*this->selected_)->isSelectable())
    (*this->selected_)->event(event);
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_UP:
      if (this->horizontal_)
	break;
      this->selectPrev();
      break;
    case ALLEGRO_KEY_DOWN:
      if (this->horizontal_)
	break;
      this->selectNext();
      break;
    case ALLEGRO_KEY_LEFT:
      if (!this->horizontal_)
	break;
      this->selectPrev();
      break;
    case ALLEGRO_KEY_RIGHT:
      if (!this->horizontal_)
	break;
      this->selectNext();
      break;
    case ALLEGRO_KEY_ENTER:
      this->pressed();
      break;
    case ALLEGRO_KEY_BACKSPACE:
      if (this->deleteAction_)
	this->deleteAction_(this);
      break;
    }
}

void					GuiSelectableGroup::selectNext()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(false);
  ++this->selected_;
  if (this->selected_ == this->sellist_.end())
    this->selected_ = this->sellist_.begin();
  (*this->selected_)->select(true);
}

void					GuiSelectableGroup::selectPrev()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  if (this->selected_ != this->sellist_.end())
    (*this->selected_)->select(false);
  if (this->selected_ == this->sellist_.begin())
    {
      this->selected_ = this->sellist_.end();
      --this->selected_;
    }
  else
    --this->selected_;
  (*this->selected_)->select(true);
}

void					GuiSelectableGroup::selectFirst()
{
  if (this->sellist_.size() == 0)
    {
      this->selected_ = this->sellist_.end();
      return;
    }
  this->selected_ = this->sellist_.begin();
  while (this->selected_ != this->sellist_.end() && !(*this->selected_)->isSelectable())
    ++this->selected_;
}

void					GuiSelectableGroup::setColor(ALLEGRO_COLOR color)
{
  t_iter				it;

  if (this->list_.size() > 0)
    {
      it = this->list_.begin();
      while (it != this->list_.end())
	{
	  (*it)->setColor(color);
	  ++it;
	}
    }
  if (this->sellist_.size() > 0)
    {
      it = this->sellist_.begin();
      while (it != this->sellist_.end())
	{
	  (*it)->setColor(color);
	  ++it;
	}
    }
}

////////////////////
// GuiRangeNumber //
////////////////////

GuiRangeNumber::GuiRangeNumber() :
  GuiSelectableNumber(),
  min_(-2147483648),
  max_(2147483647)
{}

GuiRangeNumber::~GuiRangeNumber()
{}

void					GuiRangeNumber::setBounds(int min, int max)
{
  this->min_ = min;
  this->max_ = max;
  if (this->nbr_.getVal() < this->min_)
    this->nbr_ = this->min_;
  else if (this->nbr_.getVal() > this->max_)
    this->nbr_ = this->max_;
  this->nbr_.updateStr();
}

void					GuiRangeNumber::event(ALLEGRO_EVENT *event)
{
  if (event->type != ALLEGRO_EVENT_KEY_DOWN)
    return;
  switch (event->keyboard.keycode)
    {
    case ALLEGRO_KEY_LEFT:
      this->increment(-1);
      break;
    case ALLEGRO_KEY_RIGHT:
      this->increment(1);
      break;
    }
}

void					GuiRangeNumber::increment(int n)
{
  this->nbr_ += n;
  if (this->nbr_.getVal() < this->min_)
    this->nbr_ = this->min_;
  else if (this->nbr_.getVal() > this->max_)
    this->nbr_ = this->max_;
  this->nbr_.updateStr();
}

