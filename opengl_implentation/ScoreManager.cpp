#include				"ScoreManager.hh"
#include				"SceneManager.hh"

ScoreManager::ScoreManager() :
  id_(0)
{
  this->guiList_.setPosition(Vector3d(50, 10, 0));
}

ScoreManager::~ScoreManager()
{
  if (this->file_.is_open())
    {
      this->file_.close();
    }
  if (this->save_.is_open())
    {
      this->save_.close();
    }
}

ScoreManager				*ScoreManager::getInstance()
{
  static ScoreManager			that;

  return &that;
}

void					ScoreManager::setPath(std::string const & path)
{
  this->path_ = path;
}

bool					ScoreManager::load()
{
  std::string				line;

  if (this->path_.size() == 0)
    return false;
  if (!this->file_.is_open())
    this->file_.open(this->path_.c_str(), std::ifstream::in | std::ifstream::app);
  if (!this->file_.is_open())
    return false;
  while (this->file_.good())
    {
      getline (this->file_, line);
      if (line.size() > 0)
	this->parseLine(line);
    }
  this->file_.close();
  return true;
}

void					ScoreManager::parseLine(std::string & line)
{
  std::string				part;
  Score					*score;
  char					*tmp;
  int					i = 0;

  score = new Score;
  score->id = ++this->id_;

  tmp = strtok(const_cast<char*>(line.c_str()), "#");
  while (tmp)
    {
      switch(i)
	{
	case 0:
	  if (!(std::istringstream(std::string(tmp)) >> score->score) )
	    score->score = 0;
	  break;
	case 1:
	  score->player = std::string(tmp);
	case 2:
	  part = std::string(tmp);
	  if (!(std::istringstream(part) >> score->date) )
	    score->date = 0;
	  break;
	}
      tmp = strtok(NULL, "#");
      ++i;
    }
  if (i != 3)
    {
      delete score;
      return;
    }
  this->registerScore(score);
}

bool					ScoreManager::save()
{
  t_iter				it;

  if (!this->save_.is_open())
    this->save_.open(this->path_.c_str(), std::ofstream::out | std::ofstream::trunc);
  if (!this->save_.is_open())
    return false;
  it = this->list_.begin();
  while (it != this->list_.end())
    {
      this->save_ << it->second->score;
      this->save_ << "#";
      this->save_ << it->second->player;
      this->save_ << "#";
      this->save_ << it->second->date;
      this->save_ << "\n";
      ++it;
    }
  this->save_.close();
  return true;
}

void					ScoreManager::clear()
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      delete it->second;
      ++it;
    }
  this->list_.clear();
}

void					ScoreManager::erase(int id)
{
  t_iter				it;

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      if (it->second->id == id)
	{
	  delete it->second;
	  this->list_.erase(it++);
	  this->getGuiList();
	}
      else
	++it;
    }
}

void					ScoreManager::registerScore(int score, std::string const & player)
{
  Score					*tmp;

  tmp = new Score;
  tmp->score = score;
  tmp->id = ++this->id_;
  tmp->player = player;
  tmp->date = time(NULL);
  this->registerScore(tmp);
}

void					ScoreManager::registerScore(Score *score)
{
  this->list_.insert(std::pair<int, Score*>(score->score, score));
}

inline void				selectScore(GuiComponent *c)
{
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());
  GuiSelectableGroup			*gg = dynamic_cast<GuiSelectableGroup*>(c);
  Vector3d				pos;
  int					y;

  pos = c->getPosition();
  y = pos.getY();
  if (g)
    {
      g->getPosition().setY(100 - y);
    }
  if (gg)
    {
      gg->setColor(gdl::Color(255, 0, 255));
    }
}

inline void				unselectScore(GuiComponent *c)
{
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c);

  if (g)
    {
      g->setColor(gdl::Color(0, 0, 0));
    }
}

inline void				selectExit(GuiComponent *c)
{
  GuiSelectableText			*g = dynamic_cast<GuiSelectableText*>(c);

  if (g)
    {
      g->setColor(gdl::Color(0,255,255));
    }
}

inline void				unselectExit(GuiComponent *c)
{
  GuiSelectableText			*g = dynamic_cast<GuiSelectableText*>(c);

  if (g)
    {
      g->setColor(gdl::Color(0, 0, 0));
    }
}

static inline void			pressExit(GuiComponent *c)
{
  SceneManager				*manager;
  GuiSelectableGroup			*g = dynamic_cast<GuiSelectableGroup*>(c->getParent());

  g->selectNext();
  manager = SceneManager::getInstance();
  manager->handleMessage(MSG_ACTIVE, false, "scoreMenu");
  manager->handleMessage(MSG_VISIBLE, false, "scoreMenu");
  manager->handleMessage(MSG_ACTIVE, true, "mainMenu");
  manager->handleMessage(MSG_VISIBLE, true, "mainMenu");
}

static inline void			deleteScore(GuiComponent *c)
{
  ScoreManager				*manager;

  manager = ScoreManager::getInstance();
  manager->erase(c->getId());
  (void)c;
}

GuiSelectableGroup			*ScoreManager::getGuiList()
{
  GuiSelectableGroup			*scoreList;
  GuiSelectableGroup			*selGroup;
  GuiSelectableText			*exit;
  GuiText				*player;
  GuiText				*date;
  GuiNumber				*score;
  t_iter				it;
  int					margin = 0;

  this->guiList_.clear();
  this->guiList_.setHorizontal(true);

  scoreList = new GuiSelectableGroup;
  this->guiList_.pushComponent(scoreList);

  exit = new GuiSelectableText;
  exit->setText("Exit");
  exit->setSize(40);
  exit->setPosition(Vector3d(300, 100, 0));
  exit->setSelectAction(selectExit);
  exit->setUnselectAction(unselectExit);
  exit->setPressAction(pressExit);
  this->guiList_.pushComponent(exit);

  it = this->list_.begin();
  while (it != this->list_.end())
    {
      selGroup = new GuiSelectableGroup;
      player = new GuiText;
      date = new GuiText;
      score = new GuiNumber;

      selGroup->setSelectAction(selectScore);
      selGroup->setUnselectAction(unselectScore);
      selGroup->setDeleteAction(deleteScore);
      selGroup->setPosition(Vector3d(0, margin, 0));
      selGroup->setId(it->second->id);

      player->setSize(30);
      date->setSize(30);
      score->setSize(30);

      player->setPosition(Vector3d(0, 0, 0));
      // date->setPosition(Vector3d(0, margin + 30, 0));
      score->setPosition(Vector3d(0, 30, 0));

      *player = it->second->player;
      // *date = it->second->date;
      *score = it->second->score;

      selGroup->pushComponent(player);
      // g->pushComponent(date);
      selGroup->pushComponent(score);
      scoreList->pushComponent(selGroup);
      margin += 80;
      ++it;
    }
  (void)date;
  return &this->guiList_;
}
