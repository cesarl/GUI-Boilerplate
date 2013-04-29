#include			<iostream> // for debug
#include			"MyGame.hh"
#include			"Text.hpp"

void				MyGame::initialize(void)
{

  /// Creation du contexte OpenGL et de la fenetre

  window_.create();
  camera_.initialize();
  sceneManager_ = SceneManager::getInstance();
  /// Ajout des objets heritant de AObject dans la liste
  /// Appel de la methode initialize des objets
  t_iter			it;

  it = this->objects_.begin();
  for (; it != this->objects_.end(); ++it)
    (*it)->initialize();
  OptionManager::getInstance()->setOption<bool>("run", true);
  this->run_ = OptionManager::getInstance()->getOption<bool>("run");
  this->textDrawer_ = TextDrawer::getInstance();
}

void				MyGame::add(AObject * object)
{
  this->objects_.push_back(object);
  object->initialize();
}

void				MyGame::update(void)
{
  static float			time = 0;

  camera_.update(this->gameClock_, this->input_);
  if (this->gameClock_.getTotalGameTime() - time < 0.1)
    return;
  time = this->gameClock_.getTotalGameTime();
  this->sceneManager_->updateEvent(this->gameClock_, this->input_);
}

void				MyGame::draw(void)
{
  /// Vidage des buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.74f, 0.84f, 95.0f, 1.0f);
  glClearDepth(1.0f);

  /// Affichage des scenes actives && visibles
  this->sceneManager_->drawEvent();

  /// Affichage des elements textes
   this->textDrawer_->draw();

  /// Affichage du rendu dans la fenetre
  this->window_.display();
  if (!this->run_->getValue())
    this->unload();
}
void MyGame::unload(void)
{
  ////////////////////////////////////////////////////////////////////////////////
  /// Liberation memoire des ressources allouees.
  ////////////////////////////////////////////////////////////////////////////////
  std::cout << "Unload Game !!!!" << std::endl;
  // super dirty for test
  abort();
}
