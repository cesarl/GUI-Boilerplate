#ifndef				__MYGAME_HH__
# define			__MYGAME_HH__

#include			<cstdlib>
#include			<list>
#include			"SceneManager.hh"
#include			"AObject.hpp"
#include			"Camera.hh"
#include			"OptionManager.hpp"
#include			"TextDrawer.hh"

class				MyGame : public gdl::Game
{
public:
  void				initialize();
  void				add(AObject *object);
  void				update();
  void				draw();
  void				unload();
private:
  Camera			camera_;
  std::list<AObject*>		objects_;
  OptionValue<bool>		*run_;
  SceneManager			*sceneManager_;
  TextDrawer			*textDrawer_;
  typedef std::list<AObject*>::iterator t_iter;
};

#endif				// __MYGAME_HH__
