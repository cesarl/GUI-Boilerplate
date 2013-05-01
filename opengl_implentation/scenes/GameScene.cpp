#include				"GameScene.hh"

GameScene::GameScene()
{
  this->sprite_.setImage("assets/imgs/mummy.png");
  this->sprite_.initialize();
  this->sprite_.setColumn(8);
  this->sprite_.setRow(4);
  this->sprite_.setSize(Vector3d(300, 300, 0));
  this->sprite_.setIndex(0);
  this->sprite_.setPosition(Vector3d(0,0, 1100));


  this->rec_.initialize();
  this->rec_.setPosition(Vector3d(0, 0, 200));
  this->rec_.setColor(Color(255, 1, 255));
  this->rec_.setSize(Vector3d(300, 3000, 0));

  this->text_.setFont("assets/imgs/font.png");
  this->text_.setFontSize(50);
  this->text_.setPosition(Vector3d(0, 200, 0));
  this->text_ = "abcdefghijklmnopqrstuvwxyz";
}

GameScene::~GameScene()
{}

void					GameScene::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  static int i = 0;
  this->sprite_.update(gameClock, input);
  this->sprite_.setIndex(i % 31);
  this->sprite_.setRotation(Vector3d(i  % 360, i % 360, i % 360));
  ++i;
}

void					GameScene::draw()
{
  this->sprite_.draw();
  // this->rec_.draw();
  // this->text_.draw();
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
