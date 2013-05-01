#include			"Text.hh"

using namespace			Primitive;

Letter::Letter(std::string const & font, char c, int size) :
  Sprite(font, size),
  fontSize_(size),
  letter_(c)
{
  if (font.size() <= 0)
    {
      this->setImage("assets/imgs/font.png");
      this->initialize();
    }
  *this = c;
}

Letter::Letter(Letter const & letter) :
  Sprite(letter)
{
  *this = letter;
}

Letter::~Letter()
{}

void				Letter::setFontSize(int size)
{
  this->fontSize_ = size;
  this->dimension_ = Vector3d(size * 0.66, (double)size, 0.0f);
}

void				Letter::operator=(char c)
{
  this->letter_ = c;
  if (c >= '0' && c <= '9')
    {
      this->index_ = c + 4;
    }
  else if (c >= 'a' && c <= 'z')
    {
      this->index_ = c - 97 + 26;
    }
  else if (c >= 'A' && c <= 'Z')
    {
      this->index_ = c - 65;
    }
  else
    this->index_ = 70;
}

TextBlock::TextBlock(std::string const & font, std::string const & str, int size) :
  Rectangle(),
  text_(str),
  font_(font),
  fontSize_(size),
  letter_("assets/imgs/font.png", ' ', 30)
{
  this->updateString();
}

TextBlock::TextBlock() :
  Rectangle(),
  text_(""),
  font_(""),
  fontSize_(40),
  letter_("assets/imgs/font.png", ' ', 30)
{
}

TextBlock::~TextBlock()
{}

void				TextBlock::initialize()
{
}

void				TextBlock::draw()
{
  std::string::iterator		it;
  int				distance = 0;

  glPushMatrix();
  // glLoadIdentity();

  glTranslatef(this->position_.getX(), this->position_.getY(), this->position_.getZ());
  /// Rotation autour de l’axe X
  glRotatef(this->rotation_.getX(), 1.0f, 0.0f, 0.0f);

  /// Rotation autour de l’axe Y
  glRotatef(this->rotation_.getY(), 0.0f, 1.0f, 0.0f);

  /// Rotation autour de l’axe Z
  glRotatef(this->rotation_.getZ(), 0.0f, 0.0f, 1.0f);

  it = this->text_.begin();
  while (it != this->text_.end())
    {
      this->letter_ = *it;
      this->letter_.setPosition(Vector3d(distance, 0, 0));
      distance +=  this->fontSize_ * 0.66;
      this->letter_.setColor(this->color_);
      this->letter_.draw();
      ++it;
    }
  glPopMatrix();
}

void				TextBlock::setFontSize(int size)
{
  this->fontSize_ = size;
  this->updateString();
}

void				TextBlock::setFont(std::string const & path)
{
  this->font_ = path;
  this->updateString();
}

void				TextBlock::operator=(std::string const & str)
{
  this->text_ = str;
  this->updateString();
}

void				TextBlock::operator+=(std::string const & str)
{
  this->text_ += str;
  this->updateString();
}

void				TextBlock::updateString()
{
  this->letter_.setColumn(26);
  this->letter_.setRow(3);
  this->letter_.setFontSize(this->fontSize_);
  this->letter_.setImage(this->font_);
  this->letter_.initialize();
  // t_iter			it;
  // std::string::iterator		sit;
  // Letter			*letter;
  // int				distance;

  // it = this->list_.begin();
  // sit = this->text_.begin();
  // while (sit != this->text_.end())
  //   {
  //     distance = this->position_.getX() + std::distance(this->text_.begin(), sit) * this->fontSize_ * 0.66;
  //     if (it != this->list_.end())
  // 	{
  // 	  *(*it) = *sit;
  // 	  (*it)->setImage(this->font_);
  // 	  (*it)->setFontSize(this->fontSize_);
  // 	  (*it)->setPosition(Vector3d(distance, 0, 0));
  // 	  (*it)->initialize();
  // 	  ++it;
  // 	}
  //     else
  // 	{
  // 	  letter = new Letter(this->font_, *sit, this->fontSize_);
  // 	  letter->setPosition(Vector3d(distance, 0, 0));
  // 	  this->list_.push_back(letter);
  // 	  letter->setColumn(26);
  // 	  letter->setRow(3);
  // 	  letter->setFontSize(this->fontSize_);
  // 	  letter->initialize();
  // 	  it = this->list_.end()--;
  // 	}
  //     ++sit;
  //   }
}
