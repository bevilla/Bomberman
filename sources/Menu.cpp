//
// Menu.cpp for bomberman in /home/boutei_l/rendu/cpp_bomberman/boutei_l/sources
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Fri May 29 15:27:44 2015 Louis Bouteillon
// Last update Sat Jun 13 00:29:48 2015 Louis Bouteillon
//

#include "Menu.hpp"

void		Menu::initialize()
{
  loadTexture();
  loadOptTexture();
  if (!_pingBuff.loadFromFile("./sounds/ping.wav"))
    throw BomberError("Error: cannot load ping.wav");
  _ping.setBuffer(_pingBuff);
  initGeo(52, -29, _geometry);
  initGeo(60, -29, _geometry2);
  initGeoNb(4, 16, _geometryNb1);
  initGeoNb(4, -19, _geometryX1);
  initGeoNb(12, -19, _geometryX2);
  initGeoNb(28, -19, _geometryY1);
  initGeoNb(36, -19, _geometryY2);
  initGeoA(-7, 16, _geometryA1);
  initGeoA(-10, -19, _geometryA2);
  initGeoTBA(4, 16, _geometryTBA1);
  initGeoTBA(8, -19, _geometryTBA2);
  initGeoTBA(32, -19, _geometryTBA3);
  _played = false;
  _mode = mode::menu::UNKNOWN;
  _cMode = mode::menu::START;
  _subMode = mode::menu::UNKNOWN;
  _gen = mode::gen::MENU;
  _nbIA = 0;
  _optView = 0;
  x_ten = 0;
  x_unit = 0;
  y_ten = 0;
  y_unit = 0;
  _map = "./maps/map1.map";
}

void		Menu::loadTexture()
{
  if (_texture_menu[mode::menu::START].load(MENU_START) == false or
      _texture_menu[mode::menu::LOAD].load(MENU_LOAD) == false or
      _texture_menu[mode::menu::OPTION].load(MENU_OPTION) == false or
      _texture_menu[mode::menu::CREDIT].load(MENU_CREDIT) == false or
      _texture_menu[mode::menu::QUIT].load(MENU_QUIT) == false or
      _texture_credit[mode::credit::NM].load(CREDIT_NM) == false or
      _texture_credit[mode::credit::BACK].load(CREDIT_BACK) == false or
      _texture_loading[mode::load::SOLO].load(LOAD_SOLO) == false or
      _texture_loading[mode::load::MULTI].load(LOAD_MULTI) == false or
      _texture_gamemode[mode::game::SOLO].load(GAME_SOLO) == false or
      _texture_gamemode[mode::game::MULTI].load(GAME_MULTI) == false or
      _texture_gamemode[mode::game::BACK].load(GAME_BACK) == false or
      _texture_go[mode::game_over::MAIN_MENU].load(GO_MM) == false or
      _texture_go[mode::game_over::QUIT].load(GO_Q) == false or
      _texture_win[mode::win::WIN1].load(WIN_WIN1) == false or
      _texture_win[mode::win::WIN2].load(WIN_WIN2) == false)
    throw BomberError("Error: cannot load menu texture");
}

void		Menu::loadOptTexture()
{
  if (_texture_option[0].load(OPTION_1) == false or
      _texture_option[1].load(OPTION_2) == false or
      _texture_option[2].load(OPTION_3) == false or
      _texture_option[3].load(OPTION_4) == false or
      _texture_option[4].load(OPTION_5) == false or
      _texture_option[5].load(OPTION_6) == false or
      _texture_option[6].load(OPTION_0) == false or
      _texture_number[0].load(NUMBER_0) == false or
      _texture_number[1].load(NUMBER_1) == false or
      _texture_number[2].load(NUMBER_2) == false or
      _texture_number[3].load(NUMBER_3) == false or
      _texture_number[4].load(NUMBER_4) == false or
      _texture_number[5].load(NUMBER_5) == false or
      _texture_number[6].load(NUMBER_6) == false or
      _texture_number[7].load(NUMBER_7) == false or
      _texture_number[8].load(NUMBER_8) == false or
      _texture_number[9].load(NUMBER_9) == false or
      _texture_number[10].load(NUMBER_10) == false or
      _texture_arrow[0].load(ARROW_RIGHT) == false or
      _texture_arrow[1].load(ARROW_TOPBOT) == false)
    throw BomberError("Error: cannot load menu texture");
}

void		Menu::initGeo(int x, int y, gdl::Geometry & _geo)
{
  _geo.pushVertex(glm::vec3(x, y, 0));
  _geo.pushVertex(glm::vec3(x, -y, 0));
  _geo.pushVertex(glm::vec3(-x, -y, 0));
  _geo.pushVertex(glm::vec3(-x, y, 0));
  _geo.pushUv(glm::vec2(0.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 1.0f));
  _geo.pushUv(glm::vec2(0.0f, 1.0f));
  _geo.build();
}

void		Menu::initGeoNb(int x, int y, gdl::Geometry & _geo)
{
  _geo.pushVertex(glm::vec3(x + 2, y - 1, 0));
  _geo.pushVertex(glm::vec3(x + 2, y + 7, 0));
  _geo.pushVertex(glm::vec3(x - 10, y + 7, 0));
  _geo.pushVertex(glm::vec3(x - 10, y - 1, 0));
  _geo.pushUv(glm::vec2(0.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 1.0f));
  _geo.pushUv(glm::vec2(0.0f, 1.0f));
  _geo.build();
}

void		Menu::initGeoA(int x, int y, gdl::Geometry & _geo)
{
  _geo.pushVertex(glm::vec3(x + 2, y - 1, 0));
  _geo.pushVertex(glm::vec3(x + 2, y + 7, 0));
  _geo.pushVertex(glm::vec3(x - 4, y + 7, 0));
  _geo.pushVertex(glm::vec3(x - 4, y - 1, 0));
  _geo.pushUv(glm::vec2(0.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 1.0f));
  _geo.pushUv(glm::vec2(0.0f, 1.0f));
  _geo.build();
}

void		Menu::initGeoTBA(int x, int y, gdl::Geometry & _geo)
{
  _geo.pushVertex(glm::vec3(x - 1, y - 5, 0));
  _geo.pushVertex(glm::vec3(x - 1, y + 11, 0));
  _geo.pushVertex(glm::vec3(x - 7, y + 11, 0));
  _geo.pushVertex(glm::vec3(x - 7, y - 5, 0));
  _geo.pushUv(glm::vec2(0.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 0.0f));
  _geo.pushUv(glm::vec2(1.0f, 1.0f));
  _geo.pushUv(glm::vec2(0.0f, 1.0f));
  _geo.build();
}

void		Menu::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  if (_gen == mode::gen::MENU)
    menuHandle(input);
  else if (_gen == mode::gen::CREDIT)
    creditHandle(input);
  else if (_gen == mode::gen::GAME)
    gameHandle(input);
  else if (_gen == mode::gen::GAME_OVER)
    goHandle(input);
  else if (_gen == mode::gen::OPTION)
    {
      if (_optView == 0)
	opt0Handle(input);
      else if (_optView == 1)
	opt1Handle(input);
      else if (_optView == 2)
	opt2Handle(input);
      else if (_optView == 3)
	opt3Handle(input);
    }
}

void		Menu::menuHandle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      _cMode < mode::menu::QUIT ? _cMode += 1 : _cMode = mode::menu::START;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _cMode > mode::menu::START ? _cMode -= 1 : _cMode = mode::menu::QUIT;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true))
    {
      _mode = _cMode;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void		Menu::creditHandle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      _subMode < mode::credit::BACK ? _subMode += 1 : _subMode = mode::credit::NM;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _subMode > mode::credit::NM ? _subMode -= 1 : _subMode = mode::credit::BACK;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true))
    {
      _mode = _subMode;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void		Menu::gameHandle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      _subMode < mode::game::BACK ? _subMode += 1 : _subMode = mode::game::SOLO;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _subMode > mode::game::SOLO ? _subMode -= 1 : _subMode = mode::game::BACK;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true))
    {
      _mode = _subMode;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void		Menu::goHandle(gdl::Input &input)
{
  if (input.getKey(SDLK_d))
    {
      _played = false;
      _subMode < mode::game_over::QUIT ? _subMode += 1 : _subMode = mode::game_over::MAIN_MENU;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_q))
    {
      _subMode > mode::game_over::MAIN_MENU ? _subMode -= 1 : _subMode = mode::game_over::QUIT;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true))
    {
      _mode = _subMode;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void		Menu::opt0Handle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      _subMode < 5 ? _subMode += 1 : _subMode = 0;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _subMode > 0 ? _subMode -= 1 : _subMode = 5;
      _ping.play();
      usleep(100000);
    }
  else if (_subMode == 0 and input.getKey(SDLK_d))
    {
      _optView = 1;
      _ping.play();
      usleep(100000);
    }
  else if (_subMode == 5 and input.getKey(SDLK_d))
    {
      _optView = 2;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true) and _subMode != 0)
    {
      _mode = 0;
      if (_subMode == 1)
	_map = "./maps/map1.map";
      else if (_subMode == 2)
	_map = "./maps/map2.map";
      else if (_subMode == 3)
	_map = "./maps/map3.map";
      else if (_subMode == 4)
	_map = "./maps/map4.map";
      else
	_map = "";
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void		Menu::opt1Handle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      _nbIA > 0 ? _nbIA -= 1 : _nbIA = 10;
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _nbIA < 10 ? _nbIA += 1 : _nbIA = 0;
      usleep(100000);
    }
  if (input.getKey(SDLK_q))
    {
      _optView = 0;
      usleep(100000);
    }
}

void		Menu::opt2Handle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      if (x_unit > 0)
	x_unit--;
      else if (x_unit == 0 and x_ten == 0)
	x_ten = 10;
      else if (x_ten > 0)
	{
	  x_ten--;
	  x_unit = 9;
	}
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      if (x_unit < 9 and x_ten < 10)
	x_unit++;
      else if (x_unit == 0 and x_ten == 10)
	x_ten = 0;
      else if (x_ten < 10)
	{
	  x_ten++;
	  x_unit = 0;
	}
      usleep(100000);
    }
  else if (input.getKey(SDLK_d))
    {
      _optView = 3;
      usleep(100000);
    }
  else if (input.getKey(SDLK_q))
    {
      _optView = 0;
      usleep(100000);
    }
}

void		Menu::opt3Handle(gdl::Input &input)
{
  if (input.getKey(SDLK_s))
    {
      if (y_unit > 0)
	y_unit--;
      else if (y_unit == 0 and y_ten == 0)
	y_ten = 10;
      else if (y_ten > 0)
	{
	  y_ten--;
	  y_unit = 9;
	}
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      if (y_unit < 9 and y_ten < 10)
	y_unit++;
      else if (y_unit == 0 and y_ten == 0)
	y_ten = 10;
      else if (y_ten < 10)
	{
	  y_ten++;
	  y_unit = 0;
	}
      usleep(100000);
    }
  else if (input.getKey(SDLK_q))
    {
      _optView = 2;
      usleep(100000);
    }
}

void		Menu::draw(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera)
{
  (void)clock;
  (void)camera;
  if (_gen == mode::gen::MENU)
    _texture_menu[getcMode()].bind();
  else if (_gen == mode::gen::CREDIT)
    _texture_credit[getSubMode()].bind();
  else if (_gen == mode::gen::GAME)
    _texture_gamemode[getSubMode()].bind();
  else if (_gen == mode::gen::LOAD)
    _texture_loading[getSubMode()].bind();
  else if (_gen == mode::gen::GAME_OVER)
    _texture_go[getSubMode()].bind();
  else if (_gen == mode::gen::OPTION)
    {
      if (getSubMode() == 0 and _optView == 0)
	{
	  _texture_arrow[0].bind();
	  _geometryA1.draw(shader, getTransformation(), GL_QUADS);
	}
      else if (getSubMode() == 5 and _optView == 0)
	{
	  _texture_arrow[0].bind();
	  _geometryA2.draw(shader, getTransformation(), GL_QUADS);
	}
      else if (getSubMode() == 0 and _optView == 1)
	{
	  _texture_arrow[1].bind();
	  _geometryTBA1.draw(shader, getTransformation(), GL_QUADS);
	}
      else if (getSubMode() == 5 and _optView == 2)
	{
	  _texture_arrow[1].bind();
	  _geometryTBA2.draw(shader, getTransformation(), GL_QUADS);
	}
      else if (getSubMode() == 5 and _optView == 3)
	{
	  _texture_arrow[1].bind();
	  _geometryTBA3.draw(shader, getTransformation(), GL_QUADS);
	}
      _texture_number[_nbIA].bind();
      _geometryNb1.draw(shader, getTransformation(), GL_QUADS);
      _texture_number[x_ten].bind();
      _geometryX1.draw(shader, getTransformation(), GL_QUADS);
      _texture_number[x_unit].bind();
      _geometryX2.draw(shader, getTransformation(), GL_QUADS);
      _texture_number[y_ten].bind();
      _geometryY1.draw(shader, getTransformation(), GL_QUADS);
      _texture_number[y_unit].bind();
      _geometryY2.draw(shader, getTransformation(), GL_QUADS);
      _texture_option[getSubMode()].bind();
    }
  else
    _texture_loading[getSubMode()].bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

void		Menu::drawWin(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera)
{
  (void)clock;
  (void)camera;
  _texture_win[getSubMode()].bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool		Menu::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  (void)src;
  (void)dest;
  (void)size;
  return false;
}

bool		Menu::getPlayed() const
{
  return (_played);
}

int		Menu::getcMode() const
{
  return (_cMode);
}

int		Menu::getMode() const
{
  return (_mode);
}

int		Menu::getSubMode() const
{
  return (_subMode);
}

int		Menu::getGen() const
{
  return (_gen);
}

void		Menu::setGen(int gen)
{
  _gen = gen;
}

void		Menu::setSub(int sub)
{
  _subMode = sub;
}

void		Menu::setMode(int mode)
{
  _mode = mode;
}

void		Menu::setcMode(int mode)
{
  _cMode = mode;
}

void		Menu::setPlay(bool _bool)
{
  _played = _bool;
}

std::string	Menu::getMap()
{
  return (_map);
}

int		Menu::getX()
{
  return (x_ten * 10 + x_unit);
}

int		Menu::getY()
{
  return (y_ten * 10 + y_unit);
}

int		Menu::getIA()
{
  return (_nbIA);
}
