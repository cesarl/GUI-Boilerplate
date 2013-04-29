#ifndef				__CAMERA_HH__
# define			__CAMERA_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>
#include			<Input.hpp>
#include			<GameClock.hpp>
#include			"Vector3d.hh"

class				Camera
{
public:
  Camera();
  void				initialize();
  void				update(gdl::GameClock const & gameClock, gdl::Input & input);
private:
  Vector3d			position_;
  Vector3d			rotation_;
};

#endif				// __CAMERA_HH__
