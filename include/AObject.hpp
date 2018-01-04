//
// AObject.hpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
// 
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
// 
// Started on  Sat May 23 17:26:28 2015 Alexis Bevillard
// Last update Wed Jun 10 12:57:34 2015 Louis Bouteillon
//

#pragma once

#include	<iostream>
#include	<AShader.hh>
#include	<Clock.hh>
#include	<Input.hh>
#include	<Texture.hh>
#include	<Model.hh>
#include	<Geometry.hh>
#include	<SdlContext.hh>
#include	"Error.hpp"

class		AObject
{
public:
  enum		type
    {
      UNKNOW,
      GROUND,
      CUBE,
      BOMB,
      MAP,
      MAP_PIECE,
      PLAYER
    };

protected:
  AObject::type	_type;
  glm::vec3	_position;
  glm::vec3	_rotation;
  glm::vec3	_scale;
  bool		_crossable;
  int		_width;
  int		_height;

public:
  AObject();
  virtual ~AObject();

public:
  virtual void	initialize();
  virtual void	update(const gdl::Clock &clock, gdl::Input &input);
  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera) = 0;
  virtual bool  isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const = 0;
  void		translate(const glm::vec3 &v);
  void	        rotate(const glm::vec3 &v, float angle);
  void		scale(const glm::vec3 &v);
  glm::mat4	getTransformation();
  const glm::vec3 &getPos() const;
  bool		isCrossable() const;
  AObject::type getType() const;
};
