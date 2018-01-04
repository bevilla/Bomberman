//
// Pause.hpp for bomberman in /home/boutei_l/rendu/cpp_bomberman
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Mon Jun  1 10:20:51 2015 Louis Bouteillon
// Last update Sat Jun 13 00:29:59 2015 Louis Bouteillon
//

#pragma once

# include <unistd.h>
# include <SFML/Audio.hpp>
# include "AObject.hpp"
# include "Mode.hpp"

# define PAUSE_RESUME	"./textures/pause_resume.tga"
# define PAUSE_RESTART	"./textures/pause_restart.tga"
# define PAUSE_SC	"./textures/pause_s&c.tga"
# define PAUSE_SQ	"./textures/pause_s&q.tga"
# define PAUSE_QUIT	"./textures/pause_quit.tga"

class	Pause : public AObject
{

public:

  Pause() {}
  virtual void	initialize();
  virtual void	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera);
  virtual bool  isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  bool		getPause() const;
  void		startPause();
  void		stopPause();
  int		getMode() const;
  int		getcMode() const;
  void		resetMode();

private:

  gdl::Texture		_texture_pause[5];
  gdl::Geometry		_geometry;
  sf::SoundBuffer	_pingBuff;
  sf::Sound		_ping;
  bool			_pause;
  int			_mode;
  int			_cMode;

};
