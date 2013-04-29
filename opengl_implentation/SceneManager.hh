#ifndef					__SCENE_MANAGER_HH__
# define				__SCENE_MANAGER_HH__

#include				<string>
#include				<list>
#include				<algorithm>
#include				<Input.hpp>
#include				<GameClock.hpp>
#include				"AScene.hh"
#include				"EMessages.hh"

class					AScene;
class					EventManager;

enum					E_PRIORITY
  {
    HIGH,
    MEDIUM,
    LOW
  };

class					SceneManager
{
public:
  static SceneManager			*getInstance();
  ~SceneManager();
  void					add(AScene *scene, int priority = MEDIUM);
  AScene				*remove(AScene *scene);
  AScene				*get(std::string const & name);
  void					setVisibleAll(bool val);
  void					setActiveAll(bool val);
  void					setPriority(AScene *scene, int priority);
  void					updateEvent(gdl::GameClock const & gameClock, gdl::Input & input);
  void					drawEvent();
  void					handleMessage(e_message type, void *data, std::string const & sceneName);
  void					handleMessage(e_message type, bool activate, std::string const & sceneName);
private:
  SceneManager();
  std::list<AScene*>			collection_;
  typedef std::list<AScene*>::iterator	t_iter;
};

#endif					// __SCENE_MANAGER_HH__
