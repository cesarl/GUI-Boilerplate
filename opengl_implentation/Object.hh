#ifndef				__OBJECT_HH__
# define			__OBJECT_HH__

#include			"AObject.hpp"

namespace Object
{
  class Cube : public AObject
  {
  public:
    void initialize(void);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  };
  class Pyramide : public AObject
  {
  public:
    void initialize(void);
    void update(gdl::GameClock const &, gdl::Input &);
    void draw(void);
  };
}

#endif				// __OBJECT_HH__
