#ifndef					__GUI_COMPONENT_HH__
# define				__GUI_COMPONENT_HH__

#include				<string>
#include				<vector>
#include				<Color.hpp>
#include				<Text.hpp>
#include				<GameClock.hpp>
#include				<Input.hpp>
#include				"Vector3d.hh"
#include				"OptionManager.hpp"
#include				"TextDrawer.hh"

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
  void					setParent(GuiComponent *parent);
  GuiComponent				*getParent() const;
  bool					isSelectable() const;
  void					setId(int id);
  int					getId() const;
  virtual void				draw(Vector3d *position = NULL);
  virtual void				update(gdl::GameClock const &, gdl::Input &);
  virtual void				select(bool val);
  virtual void				attachOption(Option *option);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
  virtual void				setColor(gdl::Color const & color);
  virtual void				setFont(std::string const & font);
  virtual void				setSize(int size);
protected:
  bool					visible_;
  GuiComponent				*parent_;
  bool					selectable_;
  Option				*option_;
  gdl::Color				color_;
  std::string				font_;
  int					size_;
  Vector3d				position_;
  int					id_;
  TextDrawer				*drawer_;
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
  void					setDeleteAction(void (*function)(GuiComponent *gui));
  virtual void				update(gdl::GameClock const &, gdl::Input &);
protected:
  bool					selected_;
  void					(*pressAction_)(GuiComponent *gui);
  void					(*selectAction_)(GuiComponent *gui);
  void					(*unselectAction_)(GuiComponent *gui);
  void					(*deleteAction_)(GuiComponent *gui);
};

/////////////
// GuiText //
/////////////

class					GuiText : public GuiComponent
{
public:
  GuiText(std::string const & val = "");
  virtual ~GuiText();
  virtual void				operator=(std::string const & str);
  virtual void				operator+=(std::string const & str);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
  virtual void				setColor(gdl::Color const & color);
  virtual void				setFont(std::string const & font);
  virtual void				setSize(int size);
protected:
  gdl::Text				text_;
  std::string				val_;
};

///////////////
// GuiNumber //
///////////////

class					GuiNumber : public GuiText
{
public:
  GuiNumber(int nb = 0);
  virtual ~GuiNumber();
  void					operator-=(int val);
  void					operator/=(int val);
  void					operator*=(int val);
  void					updateStr();
  int					getVal() const;
  virtual void				operator=(int val);
  virtual void				operator+=(int val);
  virtual void				draw(Vector3d *position = NULL);
  virtual void				saveOptionValue();
  virtual void				importOptionValue();
protected:
  int					nb_;
};

///////////////////////
// GuiSelectableText //
///////////////////////

class					GuiSelectableText : public GuiSelectable
{
public:
  GuiSelectableText();
  virtual ~GuiSelectableText();
  void					setText(std::string const & text);
  GuiText				*getText();
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
  virtual void				setColor(gdl::Color const & color);
  virtual void				setFont(std::string const & font);
  virtual void				setSize(int size);
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
  void					setNbr(int nb);
  GuiNumber				*getNumber();
  int					getVal() const;
  virtual void				draw(Vector3d *position = NULL);
  virtual void				attachOption(Option *option);
  virtual void				select(bool val);
  virtual void				setColor(gdl::Color const & color);
  virtual void				setFont(std::string const & font);
  virtual void				setSize(int size);
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
  void					clear();
  void					pushComponent(GuiComponent *component);
  void					setHorizontal(bool val);
  void					selectNext();
  void					selectPrev();
  void					selectFirst();
  virtual void				draw(Vector3d *position = NULL);
  virtual void				update(gdl::GameClock const &, gdl::Input &);
  virtual void				setColor(gdl::Color const & color);
private:
  bool					horizontal_;
  std::vector<GuiComponent*>		sellist_;
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
  void					increment(int n);
  virtual void				update(gdl::GameClock const &, gdl::Input &);
private:
  int					min_;
  int					max_;
};

#endif					// __GUI_COMPONENT_HH__
