#include			"Object.hh"

using namespace			Object;

void				Pyramide::initialize(void)
{
}

void				Pyramide::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->rotation_.setY(((int)rotation_.getY() + 1) % 360);
  (void)gameClock;
  (void)input;
}

void				Pyramide::draw(void)
{
  glPushMatrix();
  glLoadIdentity();

  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

  /// Rotation autour de l’axe Y
  glRotatef(this->rotation_.getY(), 0.0f, 1.0f, 0.0f);

  /// Ouverture d’un contexte de rendu
  glBegin(GL_TRIANGLES);

  /// Dessin des vertices
  glColor3f(1.0f, 1.0f, 1.0f);

  /// Vertex haut : B
  glVertex3f(0.0f, -150.0f, -150.0f);

  /// Vertex inferieur gauche : C
  glVertex3f(-150.0f, -150.0f, 150.0f);

  /// Vertex inferieur droit : D
  glVertex3f(150.0f, -150.0f, 150.0f);
  glColor3f(1.0f, 0.0f, 0.0f);

  /// Vertex haut : A
  glVertex3f(0.0f, 150.0f, 0.0f);

  /// Vertex inferieur gauche : C
  glVertex3f(-150.0f, -150.0f, 150.0f);

  /// Vertex inferieur droit : D
  glVertex3f(150.0f, -150.0f, 150.0f);
  glColor3f(0.0f, 1.0f, 0.0f);

  /// Vertex haut : A
  glVertex3f(0.0f, 150.0f, 0.0f);

  /// Vertex inferieur gauche : B
  glVertex3f(0.0f, -150.0f, -150.0f);

  /// Vertex inferieur droit : C
  glVertex3f(-150.0f, -150.0f, 150.0f);
  glColor3f(0.0f, 0.0f, 1.0f);

  /// Vertex haut : A
  glVertex3f(0.0f, 150.0f, 0.0f);

  /// Vertex inferieur gauche : D
  glVertex3f(150.0f, -150.0f, 150.0f);

  /// Vertex inferieur droit : B
  glVertex3f(0.0f, -150.0f, -150.0f);

  /// Fermeture du contexte de rendu
  glEnd();
  glPopMatrix();
}
