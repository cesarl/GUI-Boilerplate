#ifndef					__NEW_GAME_MENU_HH__
# define				__NEW_GAME_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"GuiComponent.hh"

class					NewGameMenu : public AScene
{
public:
  NewGameMenu();
  ~NewGameMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //variables
  GuiSelectableGroup			gui_;
};

#endif					// _NEW_GAME_MENU_HH__
