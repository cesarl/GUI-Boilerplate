#include			"Object.hh"

using namespace			Object;

void				Cube::initialize(void)
{
}

void				Cube::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->rotation_.setX(((int)rotation_.getX() + 1) % 360);
  (void)gameClock;
  (void)input;
}

void				Cube::draw(void)
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

  /// Rotation autour de l’axe X
  glRotatef(this->rotation_.getX(), 1.0f, 0.0f, 0.0f);

  /// Ouverture d’un contexte de rendu
  glBegin(GL_QUADS);

  /// Configuration de la couleur des vertices
  glColor3f(1.0f, 0.50f, 0.7f);

  /// Dessin des vertices
  /// Vertex superieur gauche
  glVertex3f(-150.0f, 150.0f, 150.0f);

  /// Vertex inferieur gauche
  glVertex3f(-150.0f, -150.0f, 150.0f);

  /// Vertex inferieur droit
  glVertex3f(150.0f, -150.0f, 150.0f);

  /// Vertex superieur droit
  glVertex3f(150.0f, 150.0f, 150.0f);

  glColor3f(1.0f, 0.50f, 0.0f);

  /// Vertex superieur gauche
  glVertex3f(-150.0f, 150.0f, -150.0f);

  /// Vertex inferieur gauche
  glVertex3f(-150.0f, -150.0f, -150.0f);

  /// Vertex inferieur droit
  glVertex3f(-150.0f, -150.0f, 150.0f);

  /// Vertex superieur droit
  glVertex3f(-150.0f, 150.0f, 150.0f);

  glColor3f(1.0f, 0.0f, 1.0f);

  /// Vertex superieur gauche
  glVertex3f(150.0f, 150.0f, -150.0f);

  /// Vertex inferieur gauche
  glVertex3f(150.0f, -150.0f, -150.0f);

  /// Vertex inferieur droit
  glVertex3f(-150.0f, -150.0f, -150.0f);

  /// Vertex superieur droit
  glVertex3f(-150.0f, 150.0f, -150.0f);

  glColor3f(0.0f, 1.0f, 1.0f);

  /// Vertex superieur gauche
  glVertex3f(150.0f, 150.0f, 150.0f);

  /// Vertex inferieur gauche
  glVertex3f(150.0f, -150.0f, 150.0f);

  /// Vertex inferieur droit
  glVertex3f(150.0f, -150.0f, -150.0f);

  /// Vertex superieur droit
  glVertex3f(150.0f, 150.0f, -150.0f);

  /// Fermeture du contexte de rendu
  glEnd();
}
