#include			"Primitives.hh"

using namespace			Primitive;

//////////////
// triangle //
//////////////

void				Triangle::initialize(void)
{
}

void				Triangle::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void)gameClock;
  (void)input;
}

void				Triangle::draw(void)
{
  /// Ouverture d’un contexte de rendu
  glBegin(GL_TRIANGLES);

  /// Configuration de la couleur des vertices
  glColor3f(1.0f, 0.50f, 0.75f);

  /// Dessin des vertices

  /// Vertex haut
  glVertex3f(0.0f, 150.0f, 0.0f);

  /// Vertex bas gauche
  glVertex3f(-150.0f, 0.0f, 0.0f);

  /// Vertex bas droit
  glVertex3f(150.0f, 00.0f, 0.0f);

  /// Fermeture du contexte de rendu
  glEnd();
}

///////////////
// rectangle //
///////////////

void				Rectangle::initialize(void)
{
}

void				Rectangle::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  this->position_ += Vector3d(0.2, 0.2, 0.2);
  (void)gameClock;
  (void)input;
}

void				Rectangle::draw(void)
{
  /// Ouverture d’un contexte de rendu
  glBegin(GL_QUADS);

  /// Configuration de la couleur des vertices
  glColor3f(1.0f, 0.50f, 0.75f);

  /// Dessin des vertices
  /// Vertex superieur gauche
  glVertex3f(-150.0f, 100.0f, 0.0f);

  /// Vertex inferieur gauche
  glVertex3f(-150.0f, -100.0f, 0.0f);

  /// Vertex inferieur droit
  glVertex3f(150.0f, -100.0f, 0.0f);

  /// Vertex superieur droit
  glVertex3f(150.0f, 100.0f, 0.0f);

  /// Fermeture du contexte de rendu
  glEnd();
}
