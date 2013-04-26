#ifndef					__MAIN_MENU_HH__
# define				__MAIN_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"GuiComponent.hh"

class					MainMenu : public AScene
{
public:
  MainMenu();
  ~MainMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual void				receiveMessage(e_message type, void *data);
private: //variables
  GuiSelectableGroup			gui_;
};

#endif					// __MAIN_MENU_HH__