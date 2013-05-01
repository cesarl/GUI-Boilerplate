#ifndef					__IMAGE_MANAGER_H__
# define				__IMAGE_MANAGER_H__

#include				<list>
#include				<map>
#include				<string>
#include				<iostream>
#include				<GL/gl.h>
#include				<GL/glu.h>
#include				<Image.hpp>

class					ImageManager
{
public:
  ~ImageManager();
  static ImageManager			*getInstance();
  gdl::Image				*load(std::string const & path);
  void					erase(std::string const & path);
  gdl::Image				*get(std::string const & path);
  bool					loadList(std::list<std::string> const & list);
  void					refresh();
private:
  ImageManager();			// private ctor because of singleton pattern
  std::map<std::string, gdl::Image> collection_;
  typedef std::map<std::string, gdl::Image>::iterator t_iter;
  typedef std::pair<std::string, gdl::Image> t_pair;
};

#endif					// __IMAGE_MANAGER_H__
