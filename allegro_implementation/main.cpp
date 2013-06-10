#include                                <allegro5/allegro.h>
#include				"AScene.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"SceneMenu.hh"
#include				"MainMenu.hh"
#include				"NewGameMenu.hh"
#include				"ScoreMenu.hh"
#include				"MainManager.hh"

int					main()
{
  if (!MainManager::getInstance()->initialize(50 * 20, 50 * 20))
    return -1;

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
  mainMenu.setName("mainMenu");

  sceneManager->add(&newGameMenu);
  newGameMenu.setActive(false);
  newGameMenu.setVisible(false);
  newGameMenu.setName("newGameMenu");

  sceneManager->add(&scoreMenu);
  scoreMenu.setActive(false);
  scoreMenu.setVisible(false);
  scoreMenu.setName("scoreMenu");

  if (!sceneManager->initialize())
    return -1;

  eventManager->play();

  MainManager::getInstance()->deInitialize();

  return (1);
}
