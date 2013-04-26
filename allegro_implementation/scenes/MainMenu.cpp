#include				"MainMenu.hh"
#include				"FontManager.hh"

static inline void			selectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(255, 0, 255));
}

static inline void			unselectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(125, 125, 125));
}

static inline void			pressExitMenuItem(GuiComponent *c)
{
  SceneManager::getInstance()->handleMessage(MSG_EXITAPP, false, "");
  (void)c;
}

static inline void			pressNewGameMenuItem(GuiComponent *c)
{
  SceneManager				*manager;
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());

  g->selectNext();
  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "mainMenu");
  manager->handleMessage(MSG_VISIBLE, false, "mainMenu");
  manager->handleMessage(MSG_ACTIVE, true, "newGameMenu");
  manager->handleMessage(MSG_VISIBLE, true, "newGameMenu");
}

MainMenu::MainMenu()
{
  std::string				text[] = {"New Game", "Load Game", "Scores", "Exit"};
  GuiSelectableText			*t;

  this->gui_.setPosition(Vector3d(50, 150, 0));
  for (int i = 0; i < 4; ++i)
    {
      t = new GuiSelectableText;
      t->setPosition(Vector3d(50, 70 * i, 0));
      t->setupText(text[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
      t->setSelectAction(selectMenuItem);
      t->setUnselectAction(unselectMenuItem);
      switch (i)
	{
	case 0:
	  t->setPressAction(pressNewGameMenuItem);
	  break;
	case 3:
	  t->setPressAction(pressExitMenuItem);
	  break;
	}
      this->gui_.pushComponent(t);
    }
}

MainMenu::~MainMenu()
{}

void					MainMenu::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					MainMenu::draw(ALLEGRO_EVENT *event)
{
  this->gui_.draw();
  (void)(event);
}

void					MainMenu::input(ALLEGRO_EVENT *event)
{
  this->gui_.event(event);
}

void					MainMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					MainMenu::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
