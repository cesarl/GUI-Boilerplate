#include                                <allegro5/allegro.h>
#include				"AScene.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"SceneMenu.hh"
#include				"MainMenu.hh"
#include				"NewGameMenu.hh"
#include				"ScoreMenu.hh"
#include				"FontManager.hh"
#include				"ScoreManager.hh"
#include				"OptionManager.hpp"

static ALLEGRO_DISPLAY			*init(int width, int height)
{
  ALLEGRO_DISPLAY			*display;

  assert(al_init());
  assert(display = al_create_display(width, height));
  return display;
}

int					main()
{
  ALLEGRO_DISPLAY			*display = init(64 * 20, 64 * 10);
  SceneManager				*sceneManager;
  EventManager				*eventManager;
  OptionManager				*optionManager;

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();
  optionManager = OptionManager::getInstance();

  optionManager->create<int>("nbHuman", 3);
  optionManager->create<int>("nbPnj", 2);
  optionManager->create<std::string>("level", "");

  MainMenu				mainMenu;
  NewGameMenu				newGameMenu;
  ScoreMenu				scoreMenu;

  sceneManager->add(&mainMenu, LOW);
  mainMenu.setActive(true);
  mainMenu.setVisible(true);
  mainMenu.setDisplay(display);
  mainMenu.setName("mainMenu");

  sceneManager->add(&newGameMenu);
  newGameMenu.setActive(false);
  newGameMenu.setVisible(false);
  newGameMenu.setDisplay(display);
  newGameMenu.setName("newGameMenu");

  sceneManager->add(&scoreMenu);
  scoreMenu.setActive(false);
  scoreMenu.setVisible(false);
  scoreMenu.setDisplay(display);
  scoreMenu.setName("scoreMenu");

  eventManager->play();
  al_destroy_display(display);
  return (1);
}
