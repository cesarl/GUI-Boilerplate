#ifndef					__GUI_COMPONENT_HH__
# define				__GUI_COMPONENT_HH__

#include				<string>
#include				<vector>
#include                                <allegro5/allegro.h>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_font.h>
#include				<allegro5/allegro_ttf.h>
#include				"Vector3d.hh"
#include				"OptionManager.hpp"

//////////////////
// GuiComponent //
//////////////////

class					GuiComponent
{
public:
  GuiComponent();
  virtual ~GuiComponent();
  void					setPosition(Vector3d const & pos);
  Vector3d				&getPosition();
  void					setVisible(bool val);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				event(ALLEGRO_EVENT *event);
  void					setParent(GuiComponent *parent);
  GuiComponent				*getParent() const;
  bool					isSelectable() const;
  virtual void				select(bool val);
  virtual void				attachOption(Option *option);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
protected:
  bool					visible_;
  GuiComponent				*parent_;
  bool					selectable_;
  Option				*option_;
  Vector3d				position_;
};

///////////////////
// GuiSelectable //
///////////////////

class					GuiSelectable : public GuiComponent
{
public:
  GuiSelectable();
  virtual ~GuiSelectable();
  virtual void				select(bool val);
  virtual void				pressed();
  void					setPressAction(void (*function)(GuiComponent *gui));
  void					setSelectAction(void (*function)(GuiComponent *gui));
  void					setUnselectAction(void (*function)(GuiComponent *gui));
  virtual void				event(ALLEGRO_EVENT *event);
protected:
  bool					selected_;
  void					(*pressAction_)(GuiComponent *gui);
  void					(*selectAction_)(GuiComponent *gui);
  void					(*unselectAction_)(GuiComponent *gui);
};

/////////////
// GuiText //
/////////////

class					GuiText : public GuiComponent
{
public:
  GuiText(std::string const & val = "");
  virtual ~GuiText();
  void					operator=(std::string const & str);
  void					operator+=(std::string const & str);
  void					setFont(ALLEGRO_FONT *font);
  void					setColor(ALLEGRO_COLOR color);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
private:
  std::string				val_;
  ALLEGRO_FONT				*font_;
  ALLEGRO_COLOR				color_;
};

///////////////
// GuiNumber //
///////////////

class					GuiNumber : public GuiComponent
{
public:
  GuiNumber(int val = 0);
  virtual ~GuiNumber();
  void					operator=(int val);
  void					operator+=(int val);
  void					operator-=(int val);
  void					operator/=(int val);
  void					operator*=(int val);
  void					setFont(ALLEGRO_FONT *font);
  void					setColor(ALLEGRO_COLOR color);
  virtual void				draw(Vector3d *position = NULL);
  void					updateStr();
  int					getVal() const;
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
protected:
  int					val_;
  ALLEGRO_FONT				*font_;
  ALLEGRO_COLOR				color_;
  std::string				strVal_;
};

///////////////////////
// GuiSelectableText //
///////////////////////

class					GuiSelectableText : public GuiSelectable
{
public:
  GuiSelectableText();
  virtual ~GuiSelectableText();
  void					setupText(std::string const & val, ALLEGRO_FONT *font);
  GuiText				*getText();
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
private:
  GuiText				text_;
};


/////////////////////////
// GuiSelectableNumber //
/////////////////////////

class					GuiSelectableNumber : public GuiSelectable
{
public:
  GuiSelectableNumber();
  virtual ~GuiSelectableNumber();
  void					setupNumber(int val, ALLEGRO_FONT *font);
  GuiNumber				*getNumber();
  int					getVal() const;
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
protected:
  GuiNumber				nbr_;
};

////////////////////////
// GuiSelectableGroup //
////////////////////////

class					GuiSelectableGroup : public GuiSelectable
{
public:
  GuiSelectableGroup();
  virtual ~GuiSelectableGroup();
  void					pushComponent(GuiComponent *component);
  virtual void				draw(Vector3d *position = NULL);
  void					setHorizontal(bool val);
  virtual void				event(ALLEGRO_EVENT *event);
  void					selectNext();
  void					selectPrev();
  void					selectFirst();
private:
  bool					horizontal_;
  std::vector<GuiComponent*>		list_;
  std::vector<GuiComponent*>::iterator	selected_;
  typedef std::vector<GuiComponent*>::iterator t_iter;
};

////////////////////
// GuiRangeNumber //
////////////////////

class					GuiRangeNumber : public GuiSelectableNumber
{
public:
  GuiRangeNumber();
  ~GuiRangeNumber();
  void					setBounds(int min, int max);
  virtual void				event(ALLEGRO_EVENT *event);
  void					increment(int n);
private:
  int					min_;
  int					max_;
};

#endif					// __GUI_COMPONENT_HH__
