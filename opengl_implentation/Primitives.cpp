#include			<iostream> // for debug
#include			"Primitives.hh"

using namespace			Primitive;

///////////////
// rectangle //
///////////////

Rectangle::Rectangle()
{}

Rectangle::Rectangle(Rectangle const & o)
{
  *this = o;
}

Rectangle::~Rectangle()
{}

void				Rectangle::initialize(void)
{
}

void				Rectangle::update(gdl::GameClock const & gameClock, gdl::Input & input)
{
  (void)gameClock;
  (void)input;
}

void				Rectangle::draw(void)
{
  glPushMatrix();
  // glLoadIdentity();

  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

  /// Rotation autour de l’axe X
  glRotatef(this->rotation_.getX(), 1.0f, 0.0f, 0.0f);

  /// Rotation autour de l’axe Y
  glRotatef(this->rotation_.getY(), 0.0f, 1.0f, 0.0f);

  /// Rotation autour de l’axe Z
  glRotatef(this->rotation_.getZ(), 0.0f, 0.0f, 1.0f);

  /// Ouverture d’un contexte de rendu
  glBegin(GL_QUADS);

  /// Configuration de la couleur des vertices
  this->color_.apply();

  /// Dessin des vertices
  /// Vertex superieur gauche
  glVertex3f(0.0f, 0.0f, 0.0f);

  /// Vertex inferieur gauche
  glVertex3f(0.0f, this->dimension_.getY(), 0.0f);

  /// Vertex inferieur droit
  glVertex3f(this->dimension_.getX(), this->dimension_.getY(), 0.0f);

  /// Vertex superieur droit
  glVertex3f(this->dimension_.getX(), 0.0f, 0.0f);

  /// Fermeture du contexte de rendu
  glEnd();
  glPopMatrix();
}

void				Rectangle::setColor(Color const & color)
{
  this->color_ = color;
}

void				Rectangle::setSize(Vector3d const & dimension)
{
  this->dimension_ = dimension;
}

///////////////
// RectImage //
///////////////

RectImage::RectImage(std::string const & path) :
  Rectangle(),
  path_(path),
  image_(NULL)
{
}

RectImage::RectImage(RectImage const & o) :
  Rectangle(o)
{
  *this = o;
}

RectImage::~RectImage()
{}

void				RectImage::initialize()
{
}

void				RectImage::draw()
{
  if (this->image_)
    this->image_->bind();

  glPushMatrix();
  // glLoadIdentity();

  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

  /// Rotation autour de l’axe X
  glRotatef(this->rotation_.getX(), 1.0f, 0.0f, 0.0f);

  /// Rotation autour de l’axe Y
  glRotatef(this->rotation_.getY(), 0.0f, 1.0f, 0.0f);

  /// Rotation autour de l’axe Z
  glRotatef(this->rotation_.getZ(), 0.0f, 0.0f, 1.0f);

  /// Ouverture d’un contexte de rendu
  glBegin(GL_QUADS);

  /// Configuration de la couleur des vertices
  this->color_.apply();

  /// Dessin des vertices
  /// Vertex superieur gauche
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f);

  /// Vertex superieur droit
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(this->dimension_.getX(), 0.0f, 0.0f);

  /// Vertex inferieur droit
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(this->dimension_.getX(), this->dimension_.getY(), 0.0f);

  /// Vertex inferieur gauche
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(0.0f, this->dimension_.getY(), 0.0f);

  /// Fermeture du contexte de rendu
  glEnd();
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);
}

void				RectImage::setImage(std::string const & path)
{
  this->path_ = path;
  this->image_ = ImageManager::getInstance()->load(path);
}


////////////
// Sprite //
////////////

Sprite::Sprite(std::string const & path,
	       int column,
	       int row,
	       int index) :
  RectImage(path),
  column_(column),
  row_(row),
  index_(index)
{
}

Sprite::Sprite(Sprite const & o) :
  RectImage(o)
{
  *this = o;
}

void				Sprite::initialize()
{
}

Sprite::~Sprite()
{}

void				Sprite::draw()
{
  float				fromX;
  float				fromY;
  float				toX;
  float				toY;

  fromX = (float)(this->index_ % this->column_) / this->column_;
  fromY = (float)(this->index_ / this->column_) / (float)this->row_;
  toX = fromX + 1.0f / this->column_;
  toY = fromY + 1.0f / this->row_;

  if (this->image_)
    this->image_->bind();
  else
    std::cout << "sprite no image" << std::endl;

  glPushMatrix();
  // glLoadIdentity();
  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());

  /// Rotation autour de l’axe X
  glRotatef(this->rotation_.getX(), 1.0f, 0.0f, 0.0f);

  /// Rotation autour de l’axe Y
  glRotatef(this->rotation_.getY(), 0.0f, 1.0f, 0.0f);

  /// Rotation autour de l’axe Z
  glRotatef(this->rotation_.getZ(), 0.0f, 0.0f, 1.0f);

  /// Ouverture d’un contexte de rendu
  glBegin(GL_QUADS);

  /// Configuration de la couleur des vertices
  this->color_.apply();

  /// Dessin des vertices
  /// Vertex superieur gauche
  glTexCoord2f(fromX, fromY);
  glVertex3f( - this->dimension_.getX() / 2, this->dimension_.getY() / 2, 0.0f);

  /// Vertex superieur droit
  glTexCoord2f(toX, fromY);
  glVertex3f(this->dimension_.getX() / 2, this->dimension_.getY() / 2, 0.0f);

  /// Vertex inferieur droit
  glTexCoord2f(toX, toY);
  glVertex3f(this->dimension_.getX() / 2, - this->dimension_.getY() / 2, 0.0f);

  /// Vertex inferieur gauche
  glTexCoord2f(fromX, toY);
  glVertex3f(- this->dimension_.getX() / 2, - this->dimension_.getY() / 2, 0.0f);

  /// Fermeture du contexte de rendu
  glEnd();
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, 0);
}

void					Sprite::setColumn(int column)
{
  this->column_ = column;
}

void					Sprite::setRow(int row)
{
  this->row_ = row;
}

void					Sprite::setIndex(int index)
{
  this->index_ = index;
}
