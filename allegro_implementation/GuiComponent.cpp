#include				<iostream>
#include				"GuiComponent.hh"

//////////////////
// GuiComponent //
//////////////////

GuiComponent::GuiComponent() :
  visible_(true),
  parent_(NULL),
  selectable_(false)
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

///////////////////
// GuiSelectable //
///////////////////

GuiSelectable::GuiSelectable() :
  GuiComponent(),
  selected_(false),
  pressAction_(NULL),
  selectAction_(NULL)
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

/////////////
// GuiText //
/////////////

GuiText::GuiText(std::string const & val) :
  GuiComponent(),
  val_(val),
  font_(NULL),
  color_(al_map_rgb(125, 125, 125))
{}


GuiText::~GuiText()
{}

void					GuiText::operator=(std::string const & str)
{
  this->val_ = str;
}

void					GuiText::operator+=(std::string const & str)
{
  this->val_ += str;
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

void					GuiText::setColor(ALLEGRO_COLOR color)
{
  this->color_ = color;
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

////////////////////////
// GuiSelectableGroup //
////////////////////////

GuiSelectableGroup::GuiSelectableGroup() :
  GuiSelectable(),
  horizontal_(false)
{}

GuiSelectableGroup::~GuiSelectableGroup()
{}

void					GuiSelectableGroup::pushComponent(GuiSelectable *component)
{
  this->list_.push_back(component);
  this->selected_ = this->list_.begin();
  (*this->selected_)->select(true);
  component->setParent(this);
}

void					GuiSelectableGroup::draw(Vector3d *position)
{
  Vector3d				vec;
  t_iter				it;

  vec = this->position_;
  if (position)
    vec += *position;
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      (*it)->draw(&vec);
      ++it;
    }
}

void					GuiSelectableGroup::setHorizontal(bool val)
{
  this->horizontal_ = val;
}

void					GuiSelectableGroup::event(ALLEGRO_EVENT *event)
{
  t_iter				it;

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
      break;
    }
}

void					GuiSelectableGroup::selectNext()
{
  (*this->selected_)->select(false);
  do
    {
      ++this->selected_;
    }
  while (this->selected_ != this->list_.end() && !(*this->selected_)->isSelectable());
  if (this->selected_ == this->list_.end())
    this->selected_ = this->list_.begin();
  (*this->selected_)->select(true);
}

void					GuiSelectableGroup::selectPrev()
{
  (*this->selected_)->select(false);
  if (this->selected_ == this->list_.begin())
    this->selected_ = --(this->list_.end());
  else
    {
      do
	{
	  --this->selected_;
	}
      while (this->selected_ != this->list_.begin() && !(*this->selected_)->isSelectable());
      if (this->selected_ == this->list_.end())
	this->selected_ = --(this->list_.end());
    }
  (*this->selected_)->select(true);
}
