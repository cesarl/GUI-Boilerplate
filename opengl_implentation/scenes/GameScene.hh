#ifndef					__GAME_SCENE_HH__
# define				__GAME_SCENE_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"Primitives.hh"
#include				"GuiComponent.hh"
#include				"Primitives.hh"
#include				"AScene.hh"
#include				"ScoreManager.hh"
#include				"Text.hh"

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
  Primitive::Sprite			sprite_;
  Primitive::Rectangle			rec_;
  Primitive::TextBlock			text_;
};

#endif					// _GAME_SCENE_HH__
