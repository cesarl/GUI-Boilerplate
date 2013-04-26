#include                                <allegro5/allegro.h>
#include				"AScene.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"SceneMenu.hh"
#include				"MainMenu.hh"
#include				"NewGameMenu.hh"
#include				"FontManager.hh"

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
  // SceneMenu				menu;
  MainMenu				mainMenu;
  NewGameMenu				newGameMenu;

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();

  // sceneManager->add(&menu);
  // menu.setActive(true);
  // menu.setVisible(true);
  // menu.setDisplay(display);
  // menu.setName("menu");

  sceneManager->add(&mainMenu);
  mainMenu.setActive(true);
  mainMenu.setVisible(true);
  mainMenu.setDisplay(display);
  mainMenu.setName("mainMenu");

  sceneManager->add(&newGameMenu);
  newGameMenu.setActive(false);
  newGameMenu.setVisible(false);
  newGameMenu.setDisplay(display);
  newGameMenu.setName("newGameMenu");

  eventManager->play();
  al_destroy_display(display);
  return (1);
}
