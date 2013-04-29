#ifndef					__SCORE_MENU_HH__
# define				__SCORE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"GuiComponent.hh"
#include				"ScoreManager.hh"

class					ScoreMenu : public AScene
{
public:
  ScoreMenu();
  ~ScoreMenu();
  virtual void				update(gdl::GameClock const & gameClock, gdl::Input & input);
  virtual void				draw();
  virtual void				receiveMessage(e_message type, bool activate);
  virtual void				receiveMessage(e_message type, void *data);
private: //variables
  GuiSelectableGroup			*gui_;
};

#endif					// _SCORE_MENU_HH__
