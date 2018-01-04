//
// Cube.hpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sun May 24 15:06:43 2015 Alexis Bevillard
// Last update Thu Jun 11 17:37:44 2015 Louis Bouteillon
//

#pragma once

#include		<Geometry.hh>
#include		<Texture.hh>
#include		"AObject.hpp"

class			Cube : public AObject
{
public:
  typedef enum		bonus
  {
    SPEED,
    RANGE,
    BOMB,
    NOPE
  }			t_bonus;
private:
  const gdl::Texture	&_texture;
  const gdl::Texture	&_texture_bonus;
  const gdl::Texture	&_texture_ext;
  gdl::Geometry		_geometry;
  gdl::Geometry		_geometry2;
  gdl::Geometry		_geometry3;
  bool			_breakable;
  bool			_isBonus;
  t_bonus		_bonus;
  bool			_isBomb;

public:
  Cube(const gdl::Texture &texture,
       const gdl::Texture &texture2,
       const gdl::Texture &texture3,
       const t_bonus &bonus = NOPE,
       const glm::vec3 &position = glm::vec3(0, 0, 0),
       bool breakable = false,
       bool isBonus = false,
       bool isBomb = false);
  virtual ~Cube();

public:
  void		initialize();
  bool		initialize(const glm::vec3 &position);
  void		update(const gdl::Clock &clock, gdl::Input &input);
  void		draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera);
  bool		isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  t_bonus	getBonus() const;
};
