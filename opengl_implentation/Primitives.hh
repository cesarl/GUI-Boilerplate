#ifndef				__PRIMITIVES_HH__
# define			__PRIMITIVES_HH__

#include			<GL/gl.h>
#include			<GL/glu.h>
#include			"AObject.hpp"
#include			"MyColor.hpp"
#include			"ImageManager.hh"

namespace Primitive
{
  class Rectangle : public AObject
  {
  public:
    Rectangle();
    Rectangle(Rectangle const & o);
    virtual ~Rectangle();
    virtual void		initialize(void);
    virtual void		update(gdl::GameClock const &, gdl::Input &);
    virtual void		draw(void);
    void			setColor(Color const & color);
    void			setSize(Vector3d const & position);
  protected:
    Vector3d			dimension_;
    Color			color_;
  };

  class RectImage : public Rectangle
  {
  public:
    RectImage(std::string const & path = "assets/imgs/mummy.png");
    RectImage(RectImage const & o);
    virtual ~RectImage();
    virtual void		initialize(void);
    virtual void		draw(void);
    void			setImage(std::string const & path);
  protected:
    std::string			path_;
    gdl::Image			*image_;
  };

  class Sprite : public RectImage
  {
  public:
    Sprite(std::string const & path = "assets/imgs/mummy.png", int column = 1, int row = 1, int index = 0);
    Sprite(Sprite const & o);
    virtual ~Sprite();
    virtual void		initialize(void);
    virtual void		draw(void);
    void			setColumn(int column);
    void			setRow(int row);
    void			setIndex(int index);
  protected:
    int				column_;
    int				row_;
    int				index_;
  };
}


#endif				// __PRIMITIVES_HH__
