#ifndef				__TEXT_HH__
# define			__TEXT_HH__

#include			<iostream> //for debug
#include			<vector>
#include			"AObject.hpp"
#include			"Primitives.hh"

namespace			Primitive
{

  class				Letter : public Sprite
  {
  public:
    Letter(std::string const & font, char c = '0', int size = 30);
    Letter(Letter const & letter);
    virtual ~Letter();
    // void			draw();
    void			setFontSize(int size);
    void			operator=(char c);
  private:
    int				fontSize_;
    char			letter_;
  };

  class				TextBlock : public Rectangle
  {
  public:
    TextBlock(std::string const & font, std::string const & str = 0, int size = 30);
    TextBlock();
    virtual ~TextBlock();
    void			initialize();
    void			draw();
    void			setFontSize(int size);
    void			setFont(std::string const & str);
    void			operator=(std::string const & str);
    void			operator+=(std::string const & str);
    void			updateString();
  private:
    std::string			text_;
    std::string			font_;
    int				fontSize_;
    Letter			letter_;
  };
}
#endif				// __TEXT_HH__
