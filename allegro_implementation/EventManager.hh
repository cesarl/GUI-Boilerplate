#ifndef					__EVENT_MANAGER_HH__
# define				__EVENT_MANAGER_HH__

#include                                <allegro5/allegro.h>
#include				<iostream>
#include				<list>
#include				<algorithm>
#include				"SceneManager.hh"

class					SceneManager;
class					Input;

class					EventManager
{
public:
  ~EventManager();
  static EventManager			*getInstance();
  void					play();
  void					pause();
private:
  ALLEGRO_EVENT_QUEUE			*event_queue_;
  ALLEGRO_TIMER				*timer_;
  SceneManager				*sceneManager_;
  bool					pause_;
  EventManager();
  typedef std::list<Input*>::iterator	t_iter;
};

#endif					// __EVENT_MANAGER_HH__

