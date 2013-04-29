#include				"SceneManager.hh"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

SceneManager				*SceneManager::getInstance()
{
  static SceneManager			that;
  return &that;
}

void					SceneManager::add(AScene * scene, int priority)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if (priority >= (*i)->getPriority())
	break;
      ++i;
    }
  if (i != this->collection_.end())
    this->collection_.insert(i, scene);
  else
    this->collection_.push_back(scene);
  scene->setPriority(priority);
}

AScene					*SceneManager::remove(AScene * scene)
{
  t_iter				i;
  AScene				*res;

  i = std::find(this->collection_.begin(), this->collection_.end(), scene);
  if (i != this->collection_.end())
    {
      res = *i;
      this->collection_.erase(i);
      return res;
    }
  return NULL;
}

// search don't use algorythm and is string comparaison - that's bad
AScene					*SceneManager::get(std::string const & name)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getName() == name)
	return *i;
      ++i;
    }
  return NULL;
}

void					SceneManager::setVisibleAll(bool val)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      (*i)->setVisible(val);
      ++i;
    }
}
void					SceneManager::setActiveAll(bool val)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      (*i)->setActive(val);
      ++i;
    }
}

void					SceneManager::setPriority(AScene *scene, int priority)
{
  (void)(scene);
  (void)(priority);
}

void					SceneManager::updateEvent(gdl::GameClock const & gameClock,
								  gdl::Input & input)
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getActive())
	(*i)->update(gameClock, input);
      ++i;
    }
}

void					SceneManager::drawEvent()
{
  t_iter				i;

  i = this->collection_.begin();
  while (i != this->collection_.end())
    {
      if ((*i)->getVisible())
	{
	  // std::cout << (*i)->getName() << std::endl;
	  (*i)->draw();
	}
      ++i;
    }
}

void					SceneManager::handleMessage(e_message type, void *data, std::string const & sceneName)
{
  AScene				*tmp;
  t_iter				it;

  tmp = this->get(sceneName);
  if (tmp)
    tmp->receiveMessage(type, data);
  else if (sceneName.empty())
    {
      it = this->collection_.begin();
      while (it != this->collection_.end())
	{
	  (*it)->receiveMessage(type, data);
	  ++it;
	}
    }
}

void					SceneManager::handleMessage(e_message type, bool activate, std::string const & sceneName)
{
  AScene				*tmp;
  t_iter				it;

  tmp = this->get(sceneName);
  switch (type)
    {
    case MSG_ACTIVE:
      if (sceneName.empty())
	this->setActiveAll(activate);
      else
	{
	  if (tmp)
	    tmp->setActive(activate);
	  else
	    std::cout << "existe pas " << sceneName << std::endl;
	}
      break;
    case MSG_VISIBLE:
      if (sceneName.empty())
	this->setVisibleAll(activate);
      else
	{
	  if (tmp)
	    tmp->setVisible(activate);
	}
      break;
    case MSG_EXITAPP:
      // this->exit();
      break;
    default:
      if (tmp)
	tmp->receiveMessage(type, activate);
      else if (sceneName.empty())
	{
	  it = this->collection_.begin();
	  while (it != this->collection_.end())
	    {
	      (*it)->receiveMessage(type, activate);
	      ++it;
	    }
	}
    }
}
