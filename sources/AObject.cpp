//
// AObject.cpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
// 
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
// 
// Started on  Sat May 23 17:28:03 2015 Alexis Bevillard
// Last update Tue Jun  9 13:55:04 2015 Alexis Bevillard
//

#include	<glm/gtc/matrix_transform.hpp>
#include	"AObject.hpp"

AObject::AObject() :
  _type(AObject::UNKNOW),
  _position(0, 0, 0),
  _rotation(0, 0, 0),
  _scale(1, 1, 1),
  _crossable(false)
{
}

AObject::~AObject()
{
}

void		AObject::initialize()
{
}

void		AObject::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
}

void		AObject::translate(const glm::vec3 &v)
{
  _position += v;
}

void	        AObject::rotate(const glm::vec3 &v, float angle)
{
  _rotation += (v * angle);
}

void		AObject::scale(const glm::vec3 &v)
{
  _scale *= v;
}

glm::mat4	AObject::getTransformation()
{
  glm::mat4	transform(1);

  transform = glm::translate(transform, _position);

  transform = glm::rotate(transform, _rotation.x, glm::vec3(1, 0, 0));
  transform = glm::rotate(transform, _rotation.y, glm::vec3(0, 1, 0));
  transform = glm::rotate(transform, _rotation.z, glm::vec3(0, 0, 1));

  transform = glm::scale(transform, _scale);

  return (transform);
}

const glm::vec3	&AObject::getPos() const
{
  return _position;
}

bool		AObject::isCrossable() const
{
  return _crossable;
}

AObject::type	AObject::getType() const
{
  return _type;
}
