#include				"NewGameMenu.hh"

static inline void			selectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(1.0f, 0.0f, 1.0f));
}

static inline void			unselectMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(0, 0, 0));
}

static inline void			selectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(1.0f, 1.0f, 0.5f));
}

static inline void			unselectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(Color(0, 0, 0));
}

static inline void			selectRangeMenuItem(GuiComponent *c)
{
  GuiRangeNumber			*t = dynamic_cast<GuiRangeNumber*>(c);

  t->getNumber()->setColor(Color(1.0f, 0, 1.0f));
}

static inline void			unselectRangeMenuItem(GuiComponent *c)
{
  GuiRangeNumber			*t = dynamic_cast<GuiRangeNumber*>(c);

  t->getNumber()->setColor(Color(0, 0, 0));
}

static inline void			pressCancelMenuItem(GuiComponent *c)
{
  SceneManager				*manager;
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());

  g->selectNext();
  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "newGameMenu");
  manager->handleMessage(MSG_VISIBLE, false, "newGameMenu");
  manager->handleMessage(MSG_ACTIVE, true, "mainMenu");
  manager->handleMessage(MSG_VISIBLE, true, "mainMenu");
}

static inline void			pressStartMenuItem(GuiComponent *c)
{
  SceneManager				*manager;
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());

  g->selectNext();
  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "newGameMenu");
  manager->handleMessage(MSG_VISIBLE, false, "newGameMenu");
  manager->handleMessage(MSG_ACTIVE, true, "gameScene");
  manager->handleMessage(MSG_VISIBLE, true, "gameScene");
}

static inline GuiSelectableGroup	*createLevelMenu()
{
  std::string				levels[] = {"Temple", "Jungle", "Facility", "Random 20", "Random 200", "Random 10k"};
  GuiSelectableGroup			*g;
  GuiSelectableText			*t;
  int					margin;

  g = new GuiSelectableGroup;
  g->attachOption(OptionManager::getInstance()->getOption<std::string>("level"));
  g->setHorizontal(true);
  margin = 0;
  for (int i = 0; i < 6; ++i)
    {
      t = new GuiSelectableText;
      t->setFont("assets/imgs/font.png");
      t->setPosition(Vector3d(margin, 50, 0));
      margin += levels[i].size() * 60;
      t->setText(levels[i]);
      t->setSize(80);
      t->setSelectAction(selectSubMenuItem);
      t->setUnselectAction(unselectSubMenuItem);
      g->pushComponent(t);
    }
  return g;
}

NewGameMenu::NewGameMenu()
{
  std::string				text[] = {"Level", "Humans", "PNJ", "Play", "Cancel"};
  GuiText				*st;
  GuiSelectableText			*t;
  GuiRangeNumber			*r;
  GuiSelectableGroup			*g;
  int					margin = 0;

  this->gui_.setPosition(Vector3d(-700, 500, 1000));
  for (int i = 0; i < 5; ++i)
    {
      switch (i)
	{
	case 0:
	  // levels
	  // creation d'un groupe de text selectionnable
	  // et ajout des champs
	  g = createLevelMenu();

	  // entete du champs level
	  // texte non selectionnable
      	  st = new GuiText;
	  st->setFont("assets/imgs/font.png");
	  *st = text[i];
	  st->setSize(100);

      	  st->setPosition(Vector3d(50, -margin, 0));
	  margin += 150;
	  g->setPosition(Vector3d(50, -margin, 0));

	  // ajout de l'entete et du groupe de text
	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(g);
	  margin += 150;
	  break;
	case 1:
	  // nombre de joueur humain
	  // entete
      	  st = new GuiText;
      	  st->setPosition(Vector3d(50, -margin, 0));
	  st->setFont("assets/imgs/font.png");
	  *st = text[i];
	  margin += 150;
	  st->setSize(100);

	  // nombre de joueur humain
	  // ajout d'un champ number de type range
	  r = new GuiRangeNumber;
	  r->setBounds(1, 2);
	  r->attachOption(OptionManager::getInstance()->getOption<int>("nbHuman"));
	  r->setPosition(Vector3d(50, -margin, 0));
	  r->setFont("assets/imgs/font.png");
	  r->setNbr(1);
	  r->setSize(130);
	  r->setSelectAction(selectRangeMenuItem);
	  r->setUnselectAction(unselectRangeMenuItem);
	  margin += 150;

	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(r);
	  break;
	case 2:
	  // nombre de pnj
	  // entete
      	  st = new GuiText;
      	  st->setPosition(Vector3d(50, -margin, 0));
	  st->setFont("assets/imgs/font.png");
	  *st = text[i];
	  st->setSize(100);
	  margin += 150;

	  // nombre de pnj
	  // ajout d'un champ number de type range
	  r = new GuiRangeNumber;
	  r->attachOption(OptionManager::getInstance()->getOption<int>("nbPnj"));
	  r->setBounds(1, 10000);
	  r->setPosition(Vector3d(50, -margin, 0));
	  r->setFont("assets/imgs/font.png");
	  r->setNbr(1);
	  r->setSize(130);
	  r->setSelectAction(selectRangeMenuItem);
	  r->setUnselectAction(unselectRangeMenuItem);
	  margin += 150;

	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(r);
	  break;
	case 3:
	  // validation du menu
	  // bouton de type text selectionnable
      	  t = new GuiSelectableText;
      	  t->setPosition(Vector3d(50, -margin, 0));
	  t->setFont("assets/imgs/font.png");
      	  t->setText(text[i]);
	  t->setSize(100);
      	  t->setSelectAction(selectMenuItem);
      	  t->setUnselectAction(unselectMenuItem);
      	  t->setPressAction(pressStartMenuItem);
	  margin += 150;
	  this->gui_.pushComponent(t);
	  break;
	case 4:
	  // annulation du menu
	  // bouton de type text selectionna
      	  t = new GuiSelectableText;
      	  t->setPosition(Vector3d(50, -margin, 0));
	  t->setFont("assets/imgs/font.png");
      	  t->setText(text[i]);
	  t->setSize(100);
      	  t->setSelectAction(selectMenuItem);
      	  t->setUnselectAction(unselectMenuItem);
      	  t->setPressAction(pressCancelMenuItem);
	  this->gui_.pushComponent(t);
	  break;
	}
    }
}

NewGameMenu::~NewGameMenu()
{}

void					NewGameMenu::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->gui_.update(gameClock, input);
}

void					NewGameMenu::draw()
{
  this->gui_.draw();
}

void					NewGameMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					NewGameMenu::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
