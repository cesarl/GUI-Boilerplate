#include				"ImageManager.hh"

//ctor

ImageManager::ImageManager()
{
}

//dtor

ImageManager::~ImageManager()
{
  t_iter				it;

  for (it = this->collection_.begin(); it != this->collection_.end(); ++it)
    {
      this->collection_.erase(it);
    }
}

// return the singleton ImageManager

ImageManager				*ImageManager::getInstance()
{
  static ImageManager			that;
  return &that;
}

// load an image

gdl::Image				*ImageManager::load(std::string const & path)
{
  gdl::Image				tmp;
  gdl::Image				*res;
  std::pair<std::map<std::string, gdl::Image>::iterator, bool> ret;

  if ((res = this->get(path)))
    return res;
  tmp = gdl::Image::load(path);
  ret = this->collection_.insert(t_pair(path, tmp));
  return &(ret.first->second);
}

// delete image from the collection

void					ImageManager::erase(std::string const & path)
{
  t_iter				it;

  it = this->collection_.find(path);
  if (it != this->collection_.end())
    {
      this->collection_.erase(it);
    }
}

//return an image

gdl::Image				*ImageManager::get(std::string const & path)
{
  t_iter				it;

  it = this->collection_.find(path);
  if (it != this->collection_.end())
    return &(it->second);
  return NULL;
}

//load a list of image

bool					ImageManager::loadList(std::list<std::string> const & list)
{
  std::list<std::string>::const_iterator it = list.begin();
  bool					ret = true;

  for (; it != list.end(); ++it)
    {
      if(!this->load(*it))
	ret = false;
    }
  return ret;
}

//relaod all images

void					ImageManager::refresh()
{
  t_iter				it;

  for (it = this->collection_.begin(); it != this->collection_.end(); ++it)
    {
      it->second = gdl::Image::load(it->first);
    }
}
