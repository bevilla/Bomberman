//
// Intro.hpp for bomberman in /home/boutei_l/rendu/cpp_bomberman
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Mon Jun  8 22:05:02 2015 Louis Bouteillon
// Last update Tue Jun  9 11:43:48 2015 Louis Bouteillon
//

#pragma once

# include <unistd.h>
# include "AObject.hpp"
# include "Mode.hpp"

# define INTRO_BB0	"./textures/bb0.tga"
# define INTRO_BB1	"./textures/bb1.tga"
# define INTRO_BB2	"./textures/bb2.tga"
# define INTRO_BB3	"./textures/bb3.tga"
# define INTRO_BB4	"./textures/bb4.tga"
# define INTRO_BB5	"./textures/bb5.tga"
# define INTRO_BB6	"./textures/bb6.tga"
# define INTRO_BB7	"./textures/bb7.tga"
# define INTRO_BB8	"./textures/bb8.tga"
# define INTRO_BB9	"./textures/bb9.tga"
# define INTRO_D0	"./textures/d0.tga"
# define INTRO_D1	"./textures/d1.tga"
# define INTRO_D2	"./textures/d2.tga"
# define INTRO_D3	"./textures/d3.tga"
# define INTRO_D4	"./textures/d4.tga"
# define INTRO_D5	"./textures/d5.tga"
# define INTRO_D6	"./textures/d6.tga"
# define INTRO_D7	"./textures/d7.tga"
# define INTRO_D8	"./textures/d8.tga"
# define INTRO_D9	"./textures/d9.tga"
# define INTRO_D10	"./textures/d10.tga"
# define INTRO_D11	"./textures/d11.tga"
# define INTRO_G0	"./textures/g0.tga"
# define INTRO_G1	"./textures/g1.tga"
# define INTRO_G2	"./textures/g2.tga"
# define INTRO_G3	"./textures/g3.tga"
# define INTRO_G4	"./textures/g4.tga"
# define INTRO_G5	"./textures/g5.tga"
# define INTRO_G6	"./textures/g6.tga"
# define INTRO_G7	"./textures/g7.tga"
# define INTRO_G8	"./textures/g8.tga"
# define INTRO_G9	"./textures/g9.tga"
# define INTRO_G10	"./textures/g10.tga"
# define INTRO_G11	"./textures/g11.tga"
# define INTRO_G12	"./textures/g12.tga"
# define INTRO_L0	"./textures/l0.tga"
# define INTRO_L1	"./textures/l1.tga"
# define INTRO_L2	"./textures/l2.tga"
# define INTRO_L3	"./textures/l3.tga"
# define INTRO_L4	"./textures/l4.tga"
# define INTRO_L5	"./textures/l5.tga"

class			Intro : public AObject
{

 public:

  Intro() {}
  virtual void		initialize();
  virtual void		update(gdl::Clock const &clock, gdl::Input &input);
  virtual void		draw(gdl::AShader &shader, gdl::Clock const &clock, const glm::vec3 &camera);
  virtual bool		isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  int			getAff() const;
  void			setAff(int);

 private:

  gdl::Texture		_texture_intro[41];
  gdl::Geometry		_geometry;
  int			_aff;

};
