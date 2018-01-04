//
// Bomberman.hpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sat May 23 16:47:59 2015 Alexis Bevillard
// Last update Sat Jun 13 00:38:39 2015 Louis Bouteillon
//

#pragma	once

#include		<SFML/Audio.hpp>
#include		<vector>
#include		<algorithm>
#include		<glm/gtc/matrix_transform.hpp>
#include		<BasicShader.hh>
#include		<SdlContext.hh>
#include		<glm/glm.hpp>
#include		<Clock.hh>
#include		<Input.hh>
#include		<Game.hh>
#include		<unistd.h>
#include		"AObject.hpp"
#include		"Marvin.hpp"
#include		"Map.hpp"
#include		"Menu.hpp"
#include		"Pause.hpp"
#include		"Intro.hpp"

#define FOV		60.f
#define MIN_RANGE	0.1f
#define MAX_RANGE       100.f
#define	WIN_WIDTH       1280.f
#define	WIN_HEIGHT      720.f
#define CAMERA_X	1
#define CAMERA_Y	15
#define CAMERA_Z	-10

class			GameEngine : public gdl::Game
{
private:
  sf::Music		_battleTheme;
  sf::Music		_menuTheme;
  sf::Music		_loseTheme;
  sf::Music		_deathTheme;
  sf::SoundBuffer	_bombExplosion;
  sf::SoundBuffer	_up;
  bool			_isInit;
  gdl::SdlContext	_context;
  gdl::BasicShader	_shader;
  glm::mat4		_projection;
  glm::mat4		_transformation;
  glm::vec3		_camera;
  gdl::Input		_input;
  gdl::Clock		_clock;
  std::vector<AObject*>	_objs;
  Marvin		*_player;
  Marvin		*_player2;
  Map			*_map;
  Menu			_menu;
  Pause			_pause;
  Intro			_intro;
  std::vector<Bomb *>	_bombz;
  bool			played;

public:
  GameEngine();
  virtual ~GameEngine();

public:
  bool			initialize();
  bool			update();
  void		        draw();
  void		        drawIntro();
  void		        drawWin();
  void			loadObject(AObject *obj);
  void			intro();
  void			mainMenu();
  void			creditHandle();
  void			optionHandle();
  void			gameHandle();
  void			goHandle();
  void			pauseHandle();
  void			setPause();
  void			affObj();
  void			soloEnd();
  void			multiEnd();
  void			saveGame();
  void			loadGame();

private:
  void			game(int nbPlayer = 1);
  void			loadSounds();
};
