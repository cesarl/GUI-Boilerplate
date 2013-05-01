#ifndef				__TEXT_DRAWER_HH__
# define			__TEXT_DRAWER_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>
#include			<vector>
#include			<Text.hpp>

class				TextDrawer
{
public:
  ~TextDrawer();
  static TextDrawer		*getInstance();
  void				draw();
  void				push(gdl::Text * text);
private:
  std::vector<gdl::Text *>	list_;
  typedef std::vector<gdl::Text *>::iterator t_iter;
  TextDrawer();
};

#endif				// __TEXT_DRAWER_HH__
