#include				"NewGameMenu.hh"
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

static inline void			selectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(120, 120, 50));
}

static inline void			unselectSubMenuItem(GuiComponent *c)
{
  GuiSelectableText			*t = dynamic_cast<GuiSelectableText*>(c);

  t->getText()->setColor(al_map_rgb(125, 125, 125));
}

static inline void			selectRangeMenuItem(GuiComponent *c)
{
  GuiRangeNumber			*t = dynamic_cast<GuiRangeNumber*>(c);

  t->getNumber()->setColor(al_map_rgb(120, 120, 50));
}

static inline void			unselectRangeMenuItem(GuiComponent *c)
{
  GuiRangeNumber			*t = dynamic_cast<GuiRangeNumber*>(c);

  t->getNumber()->setColor(al_map_rgb(125, 125, 125));
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
      t->setPosition(Vector3d(margin, 50, 0));
      margin += levels[i].size() * 20;
      t->setupText(levels[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 30));
      t->setSelectAction(selectSubMenuItem);
      t->setUnselectAction(unselectSubMenuItem);
      g->pushComponent(t);
    }
  return g;
}

NewGameMenu::NewGameMenu()
{
}

NewGameMenu::~NewGameMenu()
{}

void					NewGameMenu::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					NewGameMenu::draw(ALLEGRO_EVENT *event)
{
  this->gui_.draw();
  (void)(event);
}

void					NewGameMenu::input(ALLEGRO_EVENT *event)
{
  this->gui_.event(event);
}

void					NewGameMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

bool					NewGameMenu::initialize()
{
  std::string				text[] = {"Level", "Humans", "PNJ", "Play", "Cancel"};
  GuiText				*st;
  GuiSelectableText			*t;
  GuiRangeNumber			*r;
  GuiSelectableGroup			*g;
  int					margin = 0;

  this->gui_.setPosition(Vector3d(50, 50, 0));
  for (int i = 0; i < 5; ++i)
    {
      switch (i)
	{
	case 0:
	  // levels
	  // creation d'un groupe de text selectionnable
	  // et ajout des champs
	  g = createLevelMenu();
	  g->setPosition(Vector3d(50, margin, 0));

	  // entete du champs level
	  // texte non selectionnable
      	  st = new GuiText;
	  if (!st)
	    return false;
      	  st->setPosition(Vector3d(50, margin, 0));
	  *st = text[i];
	  st->setFont(FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));

	  // ajout de l'entete et du groupe de text
	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(g);
	  margin += 50 + 50;
	  break;
	case 1:
	  // nombre de joueur humain
	  // entete
      	  st = new GuiText;
	  if (!st)
	    return false;
      	  st->setPosition(Vector3d(50, margin, 0));
	  *st = text[i];
	  margin += 50;
	  st->setFont(FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));

	  // nombre de joueur humain
	  // ajout d'un champ number de type range
	  r = new GuiRangeNumber;
	  if (!st)
	    return false;
	  r->setBounds(1, 2);
	  r->attachOption(OptionManager::getInstance()->getOption<int>("nbHuman"));
	  r->setPosition(Vector3d(50, margin, 0));
	  r->setupNumber(1, FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 30));
	  r->setSelectAction(selectRangeMenuItem);
	  r->setUnselectAction(unselectRangeMenuItem);
	  margin += 50;

	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(r);
	  break;
	case 2:
	  // nombre de pnj
	  // entete
      	  st = new GuiText;
	  if (!st)
	    return false;
      	  st->setPosition(Vector3d(50, margin, 0));
	  *st = text[i];
	  st->setFont(FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
	  margin += 50;

	  // nombre de pnj
	  // ajout d'un champ number de type range
	  r = new GuiRangeNumber;
	  if (!r)
	    return false;
	  r->attachOption(OptionManager::getInstance()->getOption<int>("nbPnj"));
	  r->setBounds(1, 10000);
	  r->setPosition(Vector3d(50, margin, 0));
	  r->setupNumber(1, FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 30));
	  r->setSelectAction(selectRangeMenuItem);
	  r->setUnselectAction(unselectRangeMenuItem);
	  margin += 50;

	  this->gui_.pushComponent(st);
	  this->gui_.pushComponent(r);
	  break;
	case 3:
	  // validation du menu
	  // bouton de type text selectionnable
      	  t = new GuiSelectableText;
	  if (!t)
	    return false;
      	  t->setPosition(Vector3d(50, margin, 0));
      	  t->setupText(text[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
      	  t->setSelectAction(selectMenuItem);
      	  t->setUnselectAction(unselectMenuItem);
      	  // t->setPressAction(pressCancelMenuItem);
	  margin += 50;
	  this->gui_.pushComponent(t);
	  break;
	case 4:
	  // annulation du menu
	  // bouton de type text selectionna
      	  t = new GuiSelectableText;
	  if (!t)
	    return false;
      	  t->setPosition(Vector3d(50, margin, 0));
      	  t->setupText(text[i], FontManager::getInstance()->load("assets/fonts/LilitaOne-Regular.ttf", 40));
      	  t->setSelectAction(selectMenuItem);
      	  t->setUnselectAction(unselectMenuItem);
      	  t->setPressAction(pressCancelMenuItem);
	  this->gui_.pushComponent(t);
	  break;
	}
    }
  return true;
}

void					NewGameMenu::uninitialize()
{

}
