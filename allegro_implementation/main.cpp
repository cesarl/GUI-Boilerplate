#include                                <allegro5/allegro.h>
#include				"AScene.hh"
#include				"EventManager.hh"
#include				"SceneManager.hh"
#include				"SceneMenu.hh"
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
  SceneMenu				menu;

  eventManager = EventManager::getInstance();
  sceneManager = SceneManager::getInstance();

  sceneManager->add(&menu);
  menu.setActive(true);
  menu.setVisible(true);
  menu.setDisplay(display);
  menu.setName("menu");

  eventManager->play();
  al_destroy_display(display);
  return (1);
}
