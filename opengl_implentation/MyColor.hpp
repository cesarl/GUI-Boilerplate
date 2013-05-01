#ifndef				__COLOR_HH__
# define			__COLOR_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>

struct				Color
{
  Color()
  {
    this->r = 1.0f;
    this->g = 1.0f;
    this->b = 1.0f;
    this->a = 1.0f;
  }
  Color(float r, float g, float b, float a = 1.0f)
  {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
  ~Color()
  {}

  Color(struct Color const & o)
  {
    *this = o;
  }
  void				apply()
  {
    glColor4f(this->r, this->g, this->b, this->a);
  }
  float				r;
  float				g;
  float				b;
  float				a;
};

#endif				// __COLOR_HH__
