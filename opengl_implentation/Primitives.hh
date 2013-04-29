#ifndef				__PRIMITIVES_HH__
# define			__PRIMITIVES_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>
#include			"AObject.hpp"

namespace Primitive
{
  class Triangle : public AObject
  {
  public:
    void initialize(void);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  };

  class Rectangle : public AObject
  {
  public:
    void initialize(void);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  };
}


#endif				// __PRIMITIVES_HH__
