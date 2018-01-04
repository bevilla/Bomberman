//
// Bomberman.cpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat May 23 16:50:53 2015 Alexis Bevillard
// Last update Sat Jun 13 01:08:29 2015 Louis Bouteillon
//

#include	"GameEngine.hpp"

GameEngine::GameEngine() :
  _isInit(false),
  _camera(glm::vec3(CAMERA_X, CAMERA_Y, CAMERA_Z))
{
  _player = NULL;
  _player2 = NULL;
}

GameEngine::~GameEngine()
{
  if (_isInit)
    _context.stop();
}

void		GameEngine::loadSounds()
{
  if (!_bombExplosion.loadFromFile("./sounds/bomb_explosion.wav"))
    throw BomberError("Error: cannot load bomb_explosion.wav");
  if (!_up.loadFromFile("./sounds/up.wav"))
    throw BomberError("Error: cannot load up.wav");
  if (!_battleTheme.openFromFile("./sounds/battle_theme.wav"))
    throw BomberError("Error: cannot load battle_theme.wav");
  if (!_loseTheme.openFromFile("./sounds/lose.wav"))
    throw BomberError("Error: cannot load lose.wav");
  if (!_deathTheme.openFromFile("./sounds/death_theme.wav"))
    throw BomberError("Error: cannot load death_theme.wav");
  _battleTheme.play();
  _battleTheme.setLoop(true);
  _battleTheme.setVolume(75.f);
}

void		GameEngine::loadGame()
{
  _menuTheme.stop();
  _menu.setGen(mode::gen::LOAD);
  _menu.setMode(mode::load::UNKNOWN);
  _menu.setSub(mode::load::SOLO);
  draw();

  std::ifstream file("saved/game");

  _map = new Map("saved/game", true);
  _map->loadFile(&file);
  loadObject(_map);
  _projection = glm::perspective(FOV,
  				 WIN_WIDTH / static_cast<float>(WIN_HEIGHT),
  				 MIN_RANGE,
  				 MAX_RANGE);
  _transformation = glm::lookAt(_camera, glm::vec3(_camera.x, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);

  loadObject((_player = new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::PLAY1, glm::vec3(1, 0, 1))));
  // if (nbPlayer == 2)
  //   loadObject((_player2 = new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::PLAY2, glm::vec3(_map->getWidth() - 2, 0, _map->getHeight() - 2))));
  for (int i = 0; i < _menu.getIA(); i++)
    loadObject(new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::CPU, glm::vec3(_map->getWidth() - 2, 0, 1)));
  loadSounds();
  played = true;
  _menu.setPlay(true);
  _menu.setGen(mode::gen::UNKNOWN);
}

void		GameEngine::saveGame()
{
  std::ofstream	file("saved/game");

  file << *_map;
  file.close();
}

void		GameEngine::game(int nbPlayer)
{
  _menuTheme.stop();
  if (_menu.getMap() != "")
    loadObject((_map = new Map(_menu.getMap())));
  else
    loadObject((_map = new Map(_menu.getX(), _menu.getY())));
  _projection = glm::perspective(FOV,
  				 WIN_WIDTH / static_cast<float>(WIN_HEIGHT),
  				 MIN_RANGE,
  				 MAX_RANGE);
  _transformation = glm::lookAt(_camera, glm::vec3(_camera.x, 0, 0), glm::vec3(0, 1, 0));
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);

  loadObject((_player = new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::PLAY1, glm::vec3(1, 0, 1))));
  if (nbPlayer == 2)
    loadObject((_player2 = new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::PLAY2, glm::vec3(_map->getWidth() - 2, 0, _map->getHeight() - 2))));
  for (int i = 0; i < _menu.getIA(); i++)
    loadObject(new Marvin(_bombExplosion, _up, _bombz, _objs, _map, Marvin::CPU, glm::vec3(_map->getWidth() - 2, 0, 1)));
  loadSounds();
}

bool		GameEngine::initialize()
{
  if (!_context.start(WIN_WIDTH, WIN_HEIGHT, "Bomberman"))
    throw BomberError("Error: cannot create a new window");
  glDisable(GL_DEPTH_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  _menu.initialize();
  _pause.initialize();
  _intro.initialize();
  if (!_shader.load("./lib/shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !_shader.load("./lib/shaders/basic.vp", GL_VERTEX_SHADER) ||
      !_shader.build())
    throw BomberError("Error: cannon load basid shader");
  _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
  _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
  _shader.bind();
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  played = false;
  if (!_menuTheme.openFromFile("./sounds/main_menu.wav"))
    throw BomberError("Error: cannot load main_menu.wav");
  return (true);
}

void		GameEngine::intro()
{
  _context.updateClock(_clock);
  _menuTheme.play();
  _menuTheme.setLoop(true);
  for (int i = 0; i < mode::intro::UNKNOWN; i++)
    {
      _context.updateInputs(_input);
      if (_input.getKey(SDLK_RETURN))
	{
	  usleep(100000);
	  return;
	}
      _intro.setAff(i);
      drawIntro();
      usleep(50000);
    }
}

bool		GameEngine::update()
{
  if (_deathTheme.getStatus() == sf::SoundSource::Playing and
       _menu.getGen() == mode::gen::MENU)
    {
      _deathTheme.stop();
      _menuTheme.play();
      _menuTheme.setLoop(true);
    }
  _isInit = true;
  _context.updateInputs(_input);
  _context.updateClock(_clock);
  if ((_input.getKey(SDLK_ESCAPE) and played == false) or
      _input.getInput(SDL_QUIT) or
      _menu.getMode() == mode::menu::QUIT or
      (_menu.getGen() == mode::gen::GAME_OVER and
       _menu.getMode() == mode::game_over::QUIT))
    return (false);
  if (_menu.getGen() == mode::gen::MENU and played == false)
    mainMenu();
  else if (_menu.getGen() == mode::gen::GAME)
    gameHandle();
  else if (_menu.getGen() == mode::gen::OPTION)
    optionHandle();
  else if (_menu.getGen() == mode::gen::CREDIT)
    creditHandle();
  if (_menu.getGen() == mode::gen::GAME_OVER)
    goHandle();
  if (_input.getKey(SDLK_ESCAPE) and _pause.getPause())
    {
      usleep(100000);
      _pause.stopPause();
      _pause.resetMode();
      _battleTheme.play();
      _battleTheme.setLoop(true);
    }
  else if (_pause.getPause())
    pauseHandle();
  else if (_input.getKey(SDLK_ESCAPE) and played == true)
    _pause.startPause();
  if (_pause.getPause())
    setPause();
  else if (played == true)
    affObj();
  if (_menu.getSubMode() == mode::load::SOLO and played and std::find(_objs.begin(), _objs.end(), _player) == _objs.end())
    soloEnd();
  else if (_menu.getSubMode() == mode::load::MULTI and played)
    multiEnd();
  return true;
}

void		GameEngine::mainMenu()
{
  if (_menu.getMode() == mode::menu::START and played == false)
    {
      _menu.setGen(mode::gen::GAME);
      _menu.setSub(mode::game::SOLO);
      _menu.setMode(mode::game::UNKNOWN);
    }
  else if (_menu.getMode() == mode::menu::LOAD && played == false)
    loadGame();
  else if (_menu.getMode() == mode::menu::OPTION && played == false)
    {
      _menu.setGen(mode::gen::OPTION);
      _menu.setSub(0);
      _menu.setMode(6);
    }
  else if (_menu.getMode() == mode::menu::CREDIT && played == false)
    {
      _menu.setGen(mode::gen::CREDIT);
      _menu.setSub(mode::credit::NM);
      _menu.setMode(mode::credit::UNKNOWN);
    }
  else
    _menu.update(_clock, _input);
}

void		GameEngine::creditHandle()
{
  if (_menu.getMode() == mode::credit::BACK)
    {
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
    }
  else
    _menu.update(_clock, _input);
}

void		GameEngine::optionHandle()
{
  if (_menu.getMode() == 6)
    _menu.update(_clock, _input);
  else
    {
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
    }
}

void		GameEngine::gameHandle()
{
  if (_menu.getMode() == mode::game::SOLO and played == false)
    {
      _menu.setGen(mode::gen::LOAD);
      _menu.setMode(mode::load::UNKNOWN);
      _menu.setSub(mode::load::SOLO);
      draw();
      game();
      played = true;
      _menu.setPlay(true);
      _menu.setGen(mode::gen::UNKNOWN);
    }
  else if (_menu.getMode() == mode::game::MULTI)
    {
      _menu.setGen(mode::gen::LOAD);
      _menu.setMode(mode::load::UNKNOWN);
      _menu.setSub(mode::load::MULTI);
      draw();
      game(2);
      played = true;
      _menu.setPlay(true);
      _menu.setGen(mode::gen::UNKNOWN);
    }
  else if (_menu.getMode() == mode::game::BACK)
    {
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
    }
  else
    _menu.update(_clock, _input);
}

void		GameEngine::goHandle()
{
  _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
  _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
  _shader.setUniform("view", _transformation);
  _shader.setUniform("projection", _projection);
  if (_menu.getMode() == mode::game_over::MAIN_MENU)
    {
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
      _menu.setcMode(mode::menu::START);
    }
  else
    _menu.update(_clock, _input);
}

void		GameEngine::pauseHandle()
{
  if (_pause.getMode() == mode::pause::RESUME)
    {
      _pause.stopPause();
      _pause.resetMode();
      _battleTheme.play();
      _battleTheme.setLoop(true);
    }
  else if (_pause.getMode() == mode::pause::RESTART)
    {
      if (_map)
	delete _map;
      if (_player)
	delete _player;
      if (_player2)
	delete _player2;
      _objs.clear();
      _bombz.clear();
      _pause.stopPause();
      if (_menu.getSubMode() == mode::load::SOLO)
	{
	  _menu.setGen(mode::gen::LOAD);
	  _menu.setMode(mode::load::UNKNOWN);
	  draw();
	  game();
	}
      else if (_menu.getSubMode() == mode::load::MULTI)
	{
	  _menu.setGen(mode::gen::LOAD);
	  _menu.setMode(mode::load::UNKNOWN);
	  draw();
	  game(2);
	}
      _pause.resetMode();
      played = true;
      _menu.setPlay(true);
      _menu.setGen(mode::gen::UNKNOWN);
    }
  else if (_pause.getMode() == mode::pause::S_C)
    {
      saveGame();
      _pause.stopPause();
      _pause.resetMode();
    }
  else if (_pause.getMode() == mode::pause::S_Q)
    {
      saveGame();
      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
      _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _pause.stopPause();
      _pause.resetMode();
      played = false;
      _menu.setPlay(false);
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
      _menu.setcMode(mode::menu::START);
      _menu.update(_clock, _input);
      if (_map)
	delete _map;
      _objs.clear();
      _bombz.clear();
      _menuTheme.play();
      _menuTheme.setLoop(true);
    }
  else if (_pause.getMode() == mode::pause::QUIT)
    {
      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
      _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _pause.stopPause();
      _pause.resetMode();
      played = false;
      _menu.setPlay(false);
      _menu.setGen(mode::gen::MENU);
      _menu.setMode(mode::menu::UNKNOWN);
      _menu.setcMode(mode::menu::START);
      _menu.update(_clock, _input);
      if (_map)
	delete _map;
      _objs.clear();
      _bombz.clear();
      _menuTheme.play();
      _menuTheme.setLoop(true);
    }
}

void		GameEngine::setPause()
{
  _battleTheme.pause();
  _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
  _shader.setUniform("view", _transformation);
  _pause.update(_clock, _input);
}

void		GameEngine::affObj()
{
  for (size_t i = 0; i < _objs.size(); i++)
    if (_objs[i])
      _objs[i]->update(_clock, _input);
}

void		GameEngine::soloEnd()
{
  _battleTheme.stop();
  _loseTheme.play();
  _deathTheme.play();
  _deathTheme.setLoop(true);
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  if (_map)
    delete _map;
  _objs.clear();
  _bombz.clear();
  played = false;
  _menu.setPlay(false);
  _menu.setGen(mode::gen::GAME_OVER);
  _menu.setMode(mode::game_over::UNKNOWN);
  _menu.setSub(mode::game_over::MAIN_MENU);
}

void		GameEngine::multiEnd()
{
  glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
  if (std::find(_objs.begin(), _objs.end(), _player) == _objs.end())
    {
      _battleTheme.stop();
      _loseTheme.play();
      _deathTheme.play();
      _deathTheme.setLoop(true);
      if (_map)
	delete _map;
      _objs.clear();
      _bombz.clear();
      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
      _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _menu.setSub(mode::win::WIN2);
      drawWin();
      sleep(2);
      played = false;
      _menu.setPlay(false);
      _menu.setGen(mode::gen::GAME_OVER);
      _menu.setMode(mode::game_over::UNKNOWN);
      _menu.setSub(mode::game_over::MAIN_MENU);
    }
  else if (std::find(_objs.begin(), _objs.end(), _player2) == _objs.end())
    {
      _battleTheme.stop();
      _loseTheme.play();
      _deathTheme.play();
      _deathTheme.setLoop(true);
      if (_map)
	delete _map;
      _objs.clear();
      _bombz.clear();
      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
      _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _menu.setSub(mode::win::WIN1);
      drawWin();
      sleep(2);
      played = false;
      _menu.setPlay(false);
      _menu.setGen(mode::gen::GAME_OVER);
      _menu.setMode(mode::game_over::UNKNOWN);
      _menu.setSub(mode::game_over::MAIN_MENU);
    }
}

void		GameEngine::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  if (_menu.getPlayed() == false or
      _menu.getGen() == mode::gen::LOAD)
    _menu.draw(_shader, _clock, _camera);
  else if (_pause.getPause())
    {
      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
      _transformation = glm::lookAt(glm::vec3(0,0,50), glm::vec3(0,0,0), glm::vec3(0,1,0));
      _shader.bind();
      _shader.setUniform("view", _transformation);
      _shader.setUniform("projection", _projection);
      _pause.draw(_shader, _clock, _camera);
    }
  else
    {
      if (_player)
	{
	  _camera.x = _player->getPos().x;
	  _camera.z = CAMERA_Z + _player->getPos().z;
	  if (std::find(_objs.begin(), _objs.end(), _player2) != _objs.end())
	    {
	      _projection = glm::perspective(60.0f, (WIN_WIDTH / 2) / WIN_HEIGHT, 0.1f, 100.0f);
	      glViewport(0, 0, WIN_WIDTH / 2, WIN_HEIGHT);
	    }
	  else
	    {
	      _player2 = NULL;
	      _projection = glm::perspective(60.0f, WIN_WIDTH / WIN_HEIGHT, 0.1f, 100.0f);
	      glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
	    }
	  _shader.bind();
	  _transformation = glm::lookAt(_camera, glm::vec3(_camera.x, 0, _player->getPos().z), glm::vec3(0, 1, 0));
	  _shader.setUniform("view", _transformation);
	  _shader.setUniform("projection", _projection);
	  for (size_t i = 0; i != _objs.size(); i++)
	    _objs[i]->draw(_shader, _clock, _camera);
	}
      if (_player2)
      	{
      	  _camera.x = _player2->getPos().x;
      	  _camera.z = CAMERA_Z + _player2->getPos().z;
      	  if (std::find(_objs.begin(), _objs.end(), _player) != _objs.end())
      	    glViewport(WIN_WIDTH / 2, 0, WIN_WIDTH / 2, WIN_HEIGHT);
      	  else
      	    {
      	      _player = NULL;
      	      glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
      	    }
      	  _shader.bind();
      	  _transformation = glm::lookAt(_camera, glm::vec3(_camera.x, 0, _player2->getPos().z), glm::vec3(0, 1, 0));
      	  _shader.setUniform("view", _transformation);
      	  for (size_t i = 0; i != _objs.size(); i++)
      	    _objs[i]->draw(_shader, _clock, _camera);
      	}
    }
  _context.flush();
}

void		GameEngine::drawIntro()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _intro.draw(_shader, _clock, _camera);
  _context.flush();
  usleep(10000);
}

void		GameEngine::drawWin()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();
  _menu.drawWin(_shader, _clock, _camera);
  _context.flush();
  usleep(10000);
}

void		GameEngine::loadObject(AObject *obj)
{
  obj->initialize();
  _objs.push_back(obj);
}
