#ifndef					__GAME_SCENE_HH__
# define				__GAME_SCENE_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"Primitives.hh"
#include				"GuiComponent.hh"
#include				"Object.hh"
#include				"AScene.hh"
#include				"ScoreManager.hh"

class					GameScene : public AScene
{
public:
  GameScene();
  ~GameScene();
  virtual void				update(gdl::GameClock const & gameClock, gdl::Input & input);
  virtual void				draw();
  virtual void				receiveMessage(e_message type, bool activate);
  virtual void				receiveMessage(e_message type, void *data);
private: //variables
  Primitive::Triangle			triangle_;
  Primitive::Rectangle			rectangle_;
  Object::Pyramide			pyramide_;
  Object::Cube				cube_;
};

#endif					// _GAME_SCENE_HH__
