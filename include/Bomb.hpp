//
// Bomb.hpp for  in /home/cesar_a/rendu/cpp_bomberman
//
// Made by aymeric cesar
// Login   <cesar_a@epitech.net>
//
// Started on  Thu Jun  4 15:30:51 2015 aymeric cesar
// Last update Fri Jun 12 12:08:09 2015 Alexis Bevillard
// Last update Thu Jun 11 16:06:32 2015 Louis Bouteillon
//

#pragma	once

class Bomb;

#include			<SFML/Audio.hpp>
#include			<math.h>
#include			"AObject.hpp"
#include			"Cube.hpp"
#include			"Map.hpp"
#include			"Marvin.hpp"

# define BOOM_C			"./textures/boom_c.tga"
# define BOOM_H			"./textures/boom_h.tga"
# define BOOM_V			"./textures/boom_v.tga"

class				Bomb : public AObject
{
private:
  gdl::Model			&_model;
  gdl::Texture			_texture_c;
  gdl::Texture			_texture_h;
  gdl::Texture			_texture_v;
  int				_remTime;
  int				_range;
  std::vector<Bomb*>		&_bombz;
  std::vector<AObject*>		&_objs;
  std::vector<Cube*>		_cubes;
  Marvin			*_marvin;
  sf::Sound			&_bombExplosion;

public:
  Bomb(sf::Sound &bombExplosion, std::vector<Bomb *> &bombz, gdl::Model &model, Marvin *marvin, std::vector<AObject*> &objs, const glm::vec3 &position = glm::vec3(0, 0, 0));
  virtual ~Bomb();

public:
  void				initialize();
  void				update(const gdl::Clock &clock, gdl::Input &input);
  void				explode();
  void				draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera);
  bool				isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  int				getRemtime() const;
  int				getRange() const;
  void				makeExplode();
  enum InfoBomb {
    EXPLODE_LAST = 50
  };
};
