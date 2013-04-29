#include				"ScoreMenu.hh"

ScoreMenu::ScoreMenu()
{
  ScoreManager				*scoreManager;

  scoreManager = ScoreManager::getInstance();
  scoreManager->setPath("./scores");
  if (!scoreManager->load())
    {
      std::cerr << "score loading error" << std::endl;
    }
  // scoreManager->registerScore(1234, "Cesar");
  // scoreManager->registerScore(2345, "Julie");
  // scoreManager->registerScore(3456, "Marcus");
  this->gui_ = scoreManager->getGuiList();
  this->gui_->setPosition(Vector3d(50, 50, 0));
}

ScoreMenu::~ScoreMenu()
{
  ScoreManager				*scoreManager;

  scoreManager = ScoreManager::getInstance();
  if (!scoreManager->save())
    std::cerr << "save score error" << std::endl;
}

void					ScoreMenu::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->gui_->update(gameClock, input);
}

void					ScoreMenu::draw()
{
  this->gui_->draw();
}

void					ScoreMenu::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					ScoreMenu::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
