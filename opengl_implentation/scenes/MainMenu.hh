#ifndef					__MAIN_MENU_HH__
# define				__MAIN_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"Primitives.hh"
#include				"GuiComponent.hh"
#include				"Object.hh"

class					MainMenu : public AScene
{
public:
  MainMenu();
  ~MainMenu();
  virtual void				update(gdl::GameClock const & gameClock, gdl::Input & input);
  virtual void				draw();
  virtual void				receiveMessage(e_message type, bool activate);
  virtual void				receiveMessage(e_message type, void *data);
private: //variables
  Object::Cube				cube_;
  GuiSelectableGroup			gui_;
};

#endif					// __MAIN_MENU_HH__
