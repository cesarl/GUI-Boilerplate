#include			"MyGame.hh"
#include			"Primitives.hh"
#include			"Object.hh"
#include			"MainMenu.hh"
#include			"NewGameMenu.hh"
#include			"ScoreMenu.hh"
#include			"GameScene.hh"

int				main()
{
  MyGame			game;
  SceneManager			*sceneManager;
  MainMenu			mainMenu;
  NewGameMenu			newGameMenu;
  ScoreMenu			scoreMenu;
  GameScene			gameScene;

  sceneManager = SceneManager::getInstance();

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

  sceneManager->add(&gameScene);
  gameScene.setActive(false);
  gameScene.setVisible(false);
  gameScene.setName("gameScene");

  game.run();
  return 0;
}
