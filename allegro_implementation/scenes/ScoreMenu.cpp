#include				"ScoreMenu.hh"
#include				"FontManager.hh"

ScoreMenu::ScoreMenu()
{
}

ScoreMenu::~ScoreMenu()
{
  ScoreManager				*scoreManager;

  scoreManager = ScoreManager::getInstance();
  if (!scoreManager->save())
    std::cerr << "save score error" << std::endl;
}

void					ScoreMenu::update(ALLEGRO_EVENT *event)
{
  (void)(event);
}

void					ScoreMenu::draw(ALLEGRO_EVENT *event)
{
  this->gui_->draw();
  (void)(event);
}

void					ScoreMenu::input(ALLEGRO_EVENT *event)
{
  this->gui_->event(event);
  (void)event;
}

void					ScoreMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

bool					ScoreMenu::initialize()
{
  ScoreManager				*scoreManager;

  scoreManager = ScoreManager::getInstance();
  scoreManager->setPath("./scores");
  if (!scoreManager->load())
    {
      std::cerr << "score loading error" << std::endl;
    }
  scoreManager->registerScore(1234, "Cesar");
  this->gui_ = scoreManager->getGuiList();
  this->gui_->setPosition(Vector3d(50, 50, 0));
  return true;
}

void					ScoreMenu::uninitialize()
{}
