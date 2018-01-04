//
// Cube.cpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sun May 24 15:06:36 2015 Alexis Bevillard
// Last update Thu Jun 11 17:42:01 2015 Louis Bouteillon
//

#include	"Cube.hpp"

Cube::Cube(const gdl::Texture &texture, const gdl::Texture &texture2, const gdl::Texture &texture3, const t_bonus &bonus, const glm::vec3 &position, bool breakable, bool isBonus, bool isBomb) :
  _texture(texture),
  _texture_bonus(texture2),
  _texture_ext(texture3),
  _breakable(breakable),
  _isBonus(isBonus),
  _bonus(bonus),
  _isBomb(isBomb)
{
  _position = position;
  _type = AObject::CUBE;
  _crossable = false;
}

Cube::~Cube() {}

void		Cube::initialize()
{
  if (_isBonus)
    {
      _geometry2.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry2.pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
      _geometry2.pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
      _geometry2.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry2.pushUv(glm::vec2(0.f, 0.f));
      _geometry2.pushUv(glm::vec2(0.f, 1.f));
      _geometry2.pushUv(glm::vec2(1.f, 1.f));
      _geometry2.pushUv(glm::vec2(1.f, 0.f));
      _geometry2.build();
    }
  else
    {
      _geometry.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry.pushUv(glm::vec2(0.f, 0.f));
      _geometry.pushUv(glm::vec2(0.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 0.f));
    }
  if (_isBomb)
    {
      _geometry2.pushVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
      _geometry2.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry2.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry2.pushVertex(glm::vec3(0.5f, -0.5f, -0.5f));
      _geometry2.pushUv(glm::vec2(0.f, 0.f));
      _geometry2.pushUv(glm::vec2(0.f, 1.f));
      _geometry2.pushUv(glm::vec2(1.f, 1.f));
      _geometry2.pushUv(glm::vec2(1.f, 0.f));
      _geometry2.build();
      _geometry3.pushVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
      _geometry3.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry3.pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
      _geometry3.pushVertex(glm::vec3(-0.5f, -0.5f, 0.5f));
      _geometry3.pushUv(glm::vec2(0.f, 0.f));
      _geometry3.pushUv(glm::vec2(0.f, 1.f));
      _geometry3.pushUv(glm::vec2(1.f, 1.f));
      _geometry3.pushUv(glm::vec2(1.f, 0.f));
      _geometry3.pushVertex(glm::vec3(0.5f, -0.5f, -0.5f));
      _geometry3.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry3.pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
      _geometry3.pushVertex(glm::vec3(0.5f, -0.5f, 0.5f));
      _geometry3.pushUv(glm::vec2(0.f, 0.f));
      _geometry3.pushUv(glm::vec2(0.f, 1.f));
      _geometry3.pushUv(glm::vec2(1.f, 1.f));
      _geometry3.pushUv(glm::vec2(1.f, 0.f));
      _geometry3.build();
    }
  else
    {
      _geometry.pushVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(-0.5f, 0.5f, 0.5f));
      _geometry.pushVertex(glm::vec3(-0.5f, -0.5f, 0.5f));
      _geometry.pushUv(glm::vec2(0.f, 0.f));
      _geometry.pushUv(glm::vec2(0.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 0.f));
      _geometry.pushVertex(glm::vec3(0.5f, -0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, 0.5f, 0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, -0.5f, 0.5f));
      _geometry.pushUv(glm::vec2(0.f, 0.f));
      _geometry.pushUv(glm::vec2(0.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 0.f));
      _geometry.pushVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(-0.5f, 0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, 0.5f, -0.5f));
      _geometry.pushVertex(glm::vec3(0.5f, -0.5f, -0.5f));
      _geometry.pushUv(glm::vec2(0.f, 0.f));
      _geometry.pushUv(glm::vec2(0.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 1.f));
      _geometry.pushUv(glm::vec2(1.f, 0.f));
    }
  _geometry.build();
}

bool		Cube::initialize(const glm::vec3 &position)
{
  return (position == _position ? false : true);
}

void		Cube::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
}

void		Cube::draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera)
{
  (void)clock;
  (void)camera;
  (void)shader;
  if (_isBomb)
    {
      _texture.bind();
      _geometry.draw(shader, getTransformation(), GL_QUADS);
      _texture_bonus.bind();
      _geometry2.draw(shader, getTransformation(), GL_QUADS);
      _texture_ext.bind();
      _geometry3.draw(shader, getTransformation(), GL_QUADS);
    }
  else
    {
      _texture.bind();
      _geometry.draw(shader, getTransformation(), GL_QUADS);
      if (_isBonus)
	{
	  _texture_bonus.bind();
	  _geometry2.draw(shader, getTransformation(), GL_QUADS);
	}
    }
}

bool	        Cube::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  (void)src;
  (void)dest;
  (void)size;
  return false;
}

Cube::t_bonus	Cube::getBonus() const
{
  return (_bonus);
}
