//
// Marvin.hpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Mon May 25 12:20:13 2015 Alexis Bevillard
// Last update Sat Jun 13 00:09:50 2015 Louis Bouteillon
//

#pragma once

class Marvin;

#include		<vector>
#include		<Model.hh>
#include		"AObject.hpp"
#include		"Bomb.hpp"

# define PLAYER_SCALE	0.003

class			Marvin : public AObject
{
public:
  typedef enum		play
    {
      PLAY1,
      PLAY2,
      CPU
    }			t_play;
private:
  enum			direction
    {
      LEFT = 1,
      UP = 2,
      RIGHT = 4,
      DOWN = 8
    };

private:
  gdl::Model		_model;
  int			_direction;
  int			_direction2;
  float			_speed;
  const std::vector<AObject*>	&_objs;
  std::vector<Bomb*>	&_bombz;
  std::vector<Cube*>	_bonus;
  int			_nbBombz;
  int			_maxBombz;
  bool			_isRunning;
  gdl::Model		_bomb;
  gdl::Geometry		_nameGeometry;
  gdl::Texture		_nameTexture;
  Map			*_map;
  int			_range;
  sf::Sound		_bombExplosion;
  sf::Sound		_up;

public:
  Marvin(sf::SoundBuffer &bombExplosion, sf::SoundBuffer &up, std::vector<Bomb *> &bombz, const std::vector<AObject*> &objs, Map *map, t_play play, const glm::vec3 &position = glm::vec3(0, 0, 0));
  virtual ~Marvin();

public:
  void			initialize();
  void			update(const gdl::Clock &clock, gdl::Input &input);
  void			draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera);
  bool			isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  void			getBomb();
  int			getRange() const;

private:
  void			rotate_play1();
  void			rotate_play2();
  void			move_play1();
  void			move_play2();
  Marvin*		get_closest_player() const;
  bool			shoot_if_possible(Marvin *player);
  Bomb			*bomb_near_me() const;
  void			evade_from(Bomb *bomb);
  void			ia();

  t_play		_play;
};
