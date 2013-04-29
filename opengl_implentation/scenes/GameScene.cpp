#include				"GameScene.hh"

GameScene::GameScene()
{
  this->cube_.setPosition(Vector3d(0, 300, 0));
  this->cube_.initialize();
  this->pyramide_.initialize();
}

GameScene::~GameScene()
{}

void					GameScene::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->cube_.update(gameClock, input);
  this->pyramide_.update(gameClock, input);
}

void					GameScene::draw()
{
  Object::Pyramide pyra;

  pyra.draw();
  this->cube_.draw();
  this->pyramide_.draw();
}

void					GameScene::receiveMessage(e_message type, bool activate)
{
  (void)type;
  (void)activate;
}

void					GameScene::receiveMessage(e_message type, void *data)
{
  (void)type;
  (void)data;
}
