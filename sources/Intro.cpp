//
// Intro.cpp for bomberman in /home/boutei_l/rendu/cpp_bomberman
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Mon Jun  8 22:05:24 2015 Louis Bouteillon
// Last update Wed Jun 10 17:56:51 2015 Louis Bouteillon
//

#include "Intro.hpp"

void		Intro::initialize()
{
  if (_texture_intro[mode::intro::BB0].load(INTRO_BB0) == false or
      _texture_intro[mode::intro::BB1].load(INTRO_BB1) == false or
      _texture_intro[mode::intro::BB2].load(INTRO_BB2) == false or
      _texture_intro[mode::intro::BB3].load(INTRO_BB3) == false or
      _texture_intro[mode::intro::BB4].load(INTRO_BB4) == false or
      _texture_intro[mode::intro::BB5].load(INTRO_BB5) == false or
      _texture_intro[mode::intro::BB6].load(INTRO_BB6) == false or
      _texture_intro[mode::intro::BB7].load(INTRO_BB7) == false or
      _texture_intro[mode::intro::BB8].load(INTRO_BB8) == false or
      _texture_intro[mode::intro::BB9].load(INTRO_BB9) == false or
      _texture_intro[mode::intro::D0].load(INTRO_D0) == false or
      _texture_intro[mode::intro::D1].load(INTRO_D1) == false or
      _texture_intro[mode::intro::D2].load(INTRO_D2) == false or
      _texture_intro[mode::intro::D3].load(INTRO_D3) == false or
      _texture_intro[mode::intro::D4].load(INTRO_D4) == false or
      _texture_intro[mode::intro::D5].load(INTRO_D5) == false or
      _texture_intro[mode::intro::D6].load(INTRO_D6) == false or
      _texture_intro[mode::intro::D7].load(INTRO_D7) == false or
      _texture_intro[mode::intro::D8].load(INTRO_D8) == false or
      _texture_intro[mode::intro::D9].load(INTRO_D9) == false or
      _texture_intro[mode::intro::D10].load(INTRO_D10) == false or
      _texture_intro[mode::intro::D11].load(INTRO_D11) == false or
      _texture_intro[mode::intro::G0].load(INTRO_G0) == false or
      _texture_intro[mode::intro::G1].load(INTRO_G1) == false or
      _texture_intro[mode::intro::G2].load(INTRO_G2) == false or
      _texture_intro[mode::intro::G3].load(INTRO_G3) == false or
      _texture_intro[mode::intro::G4].load(INTRO_G4) == false or
      _texture_intro[mode::intro::G5].load(INTRO_G5) == false or
      _texture_intro[mode::intro::G6].load(INTRO_G6) == false or
      _texture_intro[mode::intro::G7].load(INTRO_G7) == false or
      _texture_intro[mode::intro::G8].load(INTRO_G8) == false or
      _texture_intro[mode::intro::G9].load(INTRO_G9) == false or
      _texture_intro[mode::intro::G10].load(INTRO_G10) == false or
      _texture_intro[mode::intro::G11].load(INTRO_G11) == false or
      _texture_intro[mode::intro::G12].load(INTRO_G12) == false or
      _texture_intro[mode::intro::L0].load(INTRO_L0) == false or
      _texture_intro[mode::intro::L1].load(INTRO_L1) == false or
      _texture_intro[mode::intro::L2].load(INTRO_L2) == false or
      _texture_intro[mode::intro::L3].load(INTRO_L3) == false or
      _texture_intro[mode::intro::L4].load(INTRO_L4) == false or
      _texture_intro[mode::intro::L5].load(INTRO_L5) == false)
    throw BomberError("Error: cannot load intro texture");
  _geometry.pushVertex(glm::vec3(52, -29, 0));
  _geometry.pushVertex(glm::vec3(52, 29, 0));
  _geometry.pushVertex(glm::vec3(-52, 29, 0));
  _geometry.pushVertex(glm::vec3(-52, -29, 0));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  _aff = mode::intro::UNKNOWN;
}

void		Intro::update(gdl::Clock const &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
}

void		Intro::draw(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera)
{
  (void)clock;
  (void)camera;

  _texture_intro[getAff()].bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool		Intro::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  (void)src;
  (void)dest;
  (void)size;
  return false;
}

int		Intro::getAff() const
{
  return (_aff);
}

void		Intro::setAff(int aff)
{
  _aff = aff;
}
