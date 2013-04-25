#ifndef					__GUI_COMPONENT_HH__
# define				__GUI_COMPONENT_HH__

#include				<string>
#include				<vector>
#include                                <allegro5/allegro.h>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_font.h>
#include				<allegro5/allegro_ttf.h>
#include				"Vector3d.hh"

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
protected:
  bool					visible_;
  GuiComponent				*parent_;
  bool					selectable_;
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
private:
  std::string				val_;
  ALLEGRO_FONT				*font_;
  ALLEGRO_COLOR				color_;
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
private:
  GuiText				text_;
};

////////////////////////
// GuiSelectableGroup //
////////////////////////

class					GuiSelectableGroup : public GuiSelectable
{
public:
  GuiSelectableGroup();
  virtual ~GuiSelectableGroup();
  void					pushComponent(GuiSelectable *component);
  virtual void				draw(Vector3d *position = NULL);
  void					setHorizontal(bool val);
  virtual void				event(ALLEGRO_EVENT *event);
  void					selectNext();
  void					selectPrev();
private:
  bool					horizontal_;
  std::vector<GuiSelectable*>		list_;
  std::vector<GuiSelectable*>::iterator	selected_;
  typedef std::vector<GuiSelectable*>::iterator t_iter;
};

#endif					// __GUI_COMPONENT_HH__
