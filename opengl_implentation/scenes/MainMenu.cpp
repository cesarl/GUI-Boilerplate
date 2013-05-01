#include				"MainMenu.hh"

static inline void			selectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(255, 0, 255));
}

static inline void			unselectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(0, 0, 0));
}

static inline void			pressExitMenuItem(GuiComponent *c)
{
  OptionManager::getInstance()->setOption<bool>("run", false);
  (void)c;
}

static inline void			pressNewGameMenuItem(GuiComponent *c)
{
  SceneManager				*manager;

  std::cout << "nmew game" << std::endl;
  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "mainMenu");
  manager->handleMessage(MSG_VISIBLE, false, "mainMenu");
  manager->handleMessage(MSG_ACTIVE, true, "newGameMenu");
  manager->handleMessage(MSG_VISIBLE, true, "newGameMenu");
  (void)c;
}

static inline void			pressScoreMenuItem(GuiComponent *c)
{
  SceneManager				*manager;

  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "mainMenu");
  manager->handleMessage(MSG_VISIBLE, false, "mainMenu");
  manager->handleMessage(MSG_ACTIVE, true, "scoreMenu");
  manager->handleMessage(MSG_VISIBLE, true, "scoreMenu");
  (void)c;
}


MainMenu::MainMenu()
{
  std::string				text[] = {"New Game", "Load Game", "Scores", "Exit"};
  GuiSelectableText			*t;

  this->gui_.setPosition(Vector3d(-700, 500, 1000));
  for (int i = 0; i < 4; ++i)
    {
      t = new GuiSelectableText;
      t->setFont("assets/imgs/font.png");
      t->setPosition(Vector3d(50, - 300 * i, 0));
      t->setText(text[i]);
      t->setSize(150);
      t->setSelectAction(selectMenuItem);
      t->setUnselectAction(unselectMenuItem);
      switch (i)
	{
	case 0:
	  t->setPressAction(pressNewGameMenuItem);
	  break;
	case 2:
	  t->setPressAction(pressScoreMenuItem);
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

void					MainMenu::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->gui_.update(gameClock, input);
}

void					MainMenu::draw()
{
  this->gui_.draw();
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
