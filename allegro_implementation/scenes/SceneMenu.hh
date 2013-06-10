#ifndef					__SCENE_MENU_HH__
# define				__SCENE_MENU_HH__

#include				<iostream> // for debug - to clear
#include				<string>
#include				"AScene.hh"
#include				"GuiSelectableGroup.hh"
#include				"GuiSelectableText.hh"


class					SceneMenu : public AScene
{
public:
  SceneMenu();
  ~SceneMenu();
  virtual void				update(ALLEGRO_EVENT *event);
  virtual void				draw(ALLEGRO_EVENT *event);
  virtual void				input(ALLEGRO_EVENT *event);
  virtual void				receiveMessage(e_message type, bool activate);
  virtual bool				initialize();
  virtual void				uninitialize();
private: //member functions
  void					p_rollMenu(int direction);
private: //variables
  GuiSelectableGroup			gui_;
  int					selectedChoice_;
};

#endif					// __SCENE_MENU_HH__
