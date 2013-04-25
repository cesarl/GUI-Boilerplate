#include				"EventManager.hh"

EventManager::EventManager()
{
  assert(al_install_keyboard());
  assert(al_install_mouse());
  assert(this->event_queue_ = al_create_event_queue());
  assert(this->timer_ = al_create_timer(1.0 / 60));
  al_register_event_source(this->event_queue_, al_get_keyboard_event_source());
  al_register_event_source(this->event_queue_, al_get_mouse_event_source());
  al_register_event_source(this->event_queue_, al_get_timer_event_source(this->timer_));
  al_start_timer(this->timer_);
  this->sceneManager_ = SceneManager::getInstance();
  this->pause_ = true;
}

EventManager::~EventManager()
{
  if (this->event_queue_)
    al_destroy_event_queue(this->event_queue_);
  if (this->timer_)
    al_destroy_timer(this->timer_);
  al_uninstall_keyboard();
  al_uninstall_mouse();
}

void					EventManager::play()
{
  bool					draw;
  t_iter				it;

  if (!this->sceneManager_)
    {
      this->sceneManager_ = SceneManager::getInstance();
      std::cerr << "Error : Event Manager - SceneManager has not been linked" << std::endl;
      return;
    }
  this->pause_ = false;
  while (!this->pause_)
    {
      ALLEGRO_EVENT			 ev;
      draw = false;
      al_wait_for_event(this->event_queue_, &ev);
      if (ev.type == ALLEGRO_EVENT_TIMER)
	{
	  draw = true;
	  this->sceneManager_->updateEvent(&ev);
	}
      else
	this->sceneManager_->inputEvent(&ev);
      if (draw && al_is_event_queue_empty(this->event_queue_))
	{
	  al_clear_to_color(al_map_rgb(0, 0, 0));
	  this->sceneManager_->drawEvent(&ev);
	  al_flip_display();
	}
      if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_KEY_UP)
	{
	}
    }
}

void					EventManager::pause()
{
  this->pause_ = true;
}

EventManager				*EventManager::getInstance()
{
  static EventManager			that;
  return &that;
}
