#include			"Camera.hh"

Camera::Camera() :
  position_(500.0f, 500.0f, -1000.0f),
  rotation_(0.0f, 0.0f, 0.0f)
{}

void				Camera::initialize()
{
  /// Configuration du frustum de la camera
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0f, 800.0f/600.0f, 1.0f, 10000.0f);
  gluLookAt(this->position_.getX(), this->position_.getY(), this->position_.getZ(),
	    0.0f, 0.0f, -1.0f,
	    0.0f, 1.0f, 0.0f);

  /// Positionnement de la camera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /// Activation des tests de profondeur
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void				Camera::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void)gameClock;
  (void)input;
}
