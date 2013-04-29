#ifndef					__ASCENE_HH__
# define				__ASCENE_HH__

#include				<string>
#include				<iostream> // pour debug - a enlever
#include				<Input.hpp>
#include				"SceneManager.hh"
#include				"EMessages.hh"

class					SceneManager;

class					AScene
{
protected:
  std::string				name_;
  bool					active_;
  bool					visible_;
  int					priority_;
public:
  AScene(std::string const & name = "Scene", bool active = false, bool visible = false);
  virtual ~AScene();
  std::string const &			getName() const;
  bool					getActive() const;
  bool					getVisible() const;
  int					getPriority() const;
  void					setName(std::string const name);
  void					setActive(bool active);
  void					setVisible(bool visible);
  void					setPriority(int priority);
  void					sendMessage(e_message type, bool active, std::string const & sceneTitle);
  void					sendMessage(e_message type, void *data, std::string const & sceneTitle);
  virtual void				receiveMessage(e_message type, bool activate) = 0;
  // very dirty need to use template
  virtual void				receiveMessage(e_message type, void *data) = 0;
  virtual void				update(gdl::GameClock const & gameClock, gdl::Input & input) = 0;
  virtual void				draw() = 0;
};

#endif					// __ASCENE_HH__
