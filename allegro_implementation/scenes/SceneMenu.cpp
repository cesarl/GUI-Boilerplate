#include				"SceneMenu.hh"
#include				"FontManager.hh"

inline void				selectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());
  Vector3d				pos;
  int					y;

  pos = c->getPosition();
  y = pos.getY();
  if (t)
    t->getText()->setColor(al_map_rgb(255, 0, 255));
  if (g)
    g->getPosition().setY(150 - y);
}

inline void				selectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(255, 0, 255));
}

inline void				unselectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(125, 125, 125));
}

inline void				unselectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(125, 125, 125));
}


SceneMenu::SceneMenu()
{
}

SceneMenu::~SceneMenu()
{}

void					SceneMenu::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					SceneMenu::draw(ALLEGRO_EVENT *event)
{
  this->gui_.draw();
  (void)(event);
}

void					SceneMenu::input(ALLEGRO_EVENT *event)
{
  this->gui_.event(event);
}

void					SceneMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

bool					SceneMenu::initialize()
{
  std::string				text[] = {"coucou", "comment", "ca", "va", "mon", "ami", "?", "moi", "ca", "va", "tres", "bien"};
  std::string				subText[] = {"Temple", "Jungle", "Facility", "Random"};
  GuiSelectableText			*t;
  GuiSelectableGroup			*g;

  this->gui_.setPosition(Vector3d(50, 150, 0));
  for (int i = 0; i < 12; ++i)
    {
      if (i == 3)
	{
	  g = new GuiSelectableGroup;
	  if (!g)
	    return false;
	  g->setHorizontal(true);
	  for (int j = 0; j < 4; ++j)
	    {
	      t = new GuiSelectableText;
	      if (!t)
		return false;
	      t->setPosition(Vector3d(200 * j, 0, 0));
	      t->setupText(subText[j], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
	      t->setSelectAction(selectSubMenuItem);
	      t->setUnselectAction(unselectSubMenuItem);
	      g->pushComponent(t);
	    }
	  g->setSelectAction(selectMenuItem);
	  this->gui_.pushComponent(g);
	  g->setPosition(Vector3d(50, 70 * i, 0));
	}
      else
	{
	  t = new GuiSelectableText;
	  if (!t)
	    return false;
	  t->setPosition(Vector3d(50, 70 * i, 0));
	  t->setupText(text[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
	  t->setSelectAction(selectMenuItem);
	  t->setUnselectAction(unselectMenuItem);
	  this->gui_.pushComponent(t);
	}
    }
  return true;
}

void					SceneMenu::uninitialize()
{

}

