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
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //variables
  GuiSelectableGroup			*gui_;
};

#endif					// _SCORE_MENU_HH__
