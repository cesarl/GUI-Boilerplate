#ifndef				__AOBJECT_HH__
# define			__AOBJECT_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>
#include			<Clock.hpp>
#include			<MyColor.hpp>
#include			<Game.hpp>
#include			<GameClock.hpp>
#include			<Image.hpp>
#include			<Model.hpp>
#include			<Window.hpp>
#include			"Vector3d.hh"

class				AObject
{
public:
  AObject() :
    position_(0.0f, 0.0f, 0.0f),
    rotation_(0.0f, 0.0f, 0.0f)
  {}
  virtual void			initialize() = 0;
  virtual void			update(gdl::GameClock const & gameClock, gdl::Input & input) = 0;
  virtual void			draw() = 0;
  virtual void			setPosition(Vector3d const & v)
  {
    this->position_ = v;
  }
  virtual void			setRotation(Vector3d const & v)
  {
    this->rotation_ = v;
  }
protected:
  Vector3d			position_;
  Vector3d			rotation_;
};

#endif				// __AOBJECT_HH__
