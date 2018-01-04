//
// Menu.hpp for bomberman in /home/boutei_l/rendu/cpp_bomberman
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Fri May 29 15:28:07 2015 Louis Bouteillon
// Last update Sat Jun 13 00:22:05 2015 Louis Bouteillon
//

#pragma once

# include <unistd.h>
# include <SFML/Audio.hpp>
# include "AObject.hpp"
# include "Mode.hpp"

# define MENU_START	"./textures/menu_start.tga"
# define MENU_LOAD	"./textures/menu_load.tga"
# define MENU_OPTION	"./textures/menu_option.tga"
# define MENU_CREDIT	"./textures/menu_credit.tga"
# define MENU_QUIT	"./textures/menu_quit.tga"
# define CREDIT_NM	"./textures/credit.tga"
# define CREDIT_BACK	"./textures/credit_back.tga"
# define GAME_SOLO	"./textures/game_solo.tga"
# define GAME_MULTI	"./textures/game_multi.tga"
# define GAME_BACK	"./textures/game_back.tga"
# define LOAD_SOLO	"./textures/load_solo.tga"
# define LOAD_MULTI	"./textures/load_multi.tga"
# define GO_MM		"./textures/game_over_mm.tga"
# define GO_Q		"./textures/game_over_quit.tga"
# define WIN_WIN1	"./textures/win1.tga"
# define WIN_WIN2	"./textures/win2.tga"
# define OPTION_0	"./textures/option.tga"
# define OPTION_1	"./textures/option_0.tga"
# define OPTION_2	"./textures/option_1.tga"
# define OPTION_3	"./textures/option_2.tga"
# define OPTION_4	"./textures/option_3.tga"
# define OPTION_5	"./textures/option_4.tga"
# define OPTION_6	"./textures/option_5.tga"
# define NUMBER_0	"./textures/0.tga"
# define NUMBER_1	"./textures/1.tga"
# define NUMBER_2	"./textures/2.tga"
# define NUMBER_3	"./textures/3.tga"
# define NUMBER_4	"./textures/4.tga"
# define NUMBER_5	"./textures/5.tga"
# define NUMBER_6	"./textures/6.tga"
# define NUMBER_7	"./textures/7.tga"
# define NUMBER_8	"./textures/8.tga"
# define NUMBER_9	"./textures/9.tga"
# define NUMBER_10	"./textures/10.tga"
# define ARROW_RIGHT	"./textures/right_arrow.tga"
# define ARROW_TOPBOT	"./textures/topbot_arrow.tga"


class			Menu : public AObject
{

 public:

  Menu() {}
  virtual void		initialize();
  virtual void		update(gdl::Clock const &clock, gdl::Input &input);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera);
  virtual void		drawWin(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera);
  virtual bool		isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  bool			getPlayed() const;
  int			getMode() const;
  int			getcMode() const;
  int			getSubMode() const;
  int			getGen() const;
  void			setGen(int);
  void			setSub(int);
  void			setMode(int);
  void			setcMode(int);
  void			setPlay(bool);
  std::string		getMap();
  int			getX();
  int			getY();
  int			getIA();
  void			menuHandle(gdl::Input &);
  void			creditHandle(gdl::Input &);
  void			gameHandle(gdl::Input &);
  void			goHandle(gdl::Input &);
  void			opt0Handle(gdl::Input &);
  void			opt1Handle(gdl::Input &);
  void			opt2Handle(gdl::Input &);
  void			opt3Handle(gdl::Input &);
  void			initGeo(int, int, gdl::Geometry &);
  void			initGeoNb(int, int, gdl::Geometry &);
  void			initGeoA(int, int, gdl::Geometry &);
  void			initGeoTBA(int, int, gdl::Geometry &);
  void			loadTexture();
  void			loadOptTexture();

 private:

  gdl::Texture		_texture_go[2];
  gdl::Texture		_texture_win[2];
  gdl::Texture		_texture_menu[5];
  gdl::Texture		_texture_credit[2];
  gdl::Texture		_texture_loading[2];
  gdl::Texture		_texture_gamemode[3];
  gdl::Texture		_texture_option[7];
  gdl::Texture		_texture_number[11];
  gdl::Texture		_texture_arrow[2];
  gdl::Geometry		_geometry;
  gdl::Geometry		_geometry2;
  gdl::Geometry		_geometryNb1;
  gdl::Geometry		_geometryX1;
  gdl::Geometry		_geometryX2;
  gdl::Geometry		_geometryY1;
  gdl::Geometry		_geometryY2;
  gdl::Geometry		_geometryA1;
  gdl::Geometry		_geometryA2;
  gdl::Geometry		_geometryTBA1;
  gdl::Geometry		_geometryTBA2;
  gdl::Geometry		_geometryTBA3;
  sf::SoundBuffer	_pingBuff;
  sf::Sound		_ping;
  bool			_played;
  int			_mode;
  int			_cMode;
  int			_subMode;
  int			_gen;
  int			_nbIA;
  int			_optView;
  int			x_ten;
  int			x_unit;
  int			y_ten;
  int			y_unit;
  std::string		_map;

};
