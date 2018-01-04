//
// Pause.cpp for bomberman in /home/boutei_l/rendu/cpp_bomberman/test_menu
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Mon Jun  1 10:30:21 2015 Louis Bouteillon
// Last update Sat Jun 13 00:28:05 2015 Louis Bouteillon
//

#include "Pause.hpp"

void	Pause::initialize()
{
  if (_texture_pause[mode::pause::RESUME].load(PAUSE_RESUME) == false or
      _texture_pause[mode::pause::RESTART].load(PAUSE_RESTART) == false or
      _texture_pause[mode::pause::S_C].load(PAUSE_SC) == false or
      _texture_pause[mode::pause::S_Q].load(PAUSE_SQ) == false or
      _texture_pause[mode::pause::QUIT].load(PAUSE_QUIT) == false)
    throw BomberError("Error: cannot load pause textures");
  if (!_pingBuff.loadFromFile("./sounds/ping.wav"))
    throw BomberError("Error: cannot load ping.wav");
  _ping.setBuffer(_pingBuff);
  _geometry.pushVertex(glm::vec3(52, -29, 0));
  _geometry.pushVertex(glm::vec3(52, 29, 0));
  _geometry.pushVertex(glm::vec3(-52, 29, 0));
  _geometry.pushVertex(glm::vec3(-52, -29, 0));
  _geometry.pushUv(glm::vec2(0.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 0.0f));
  _geometry.pushUv(glm::vec2(1.0f, 1.0f));
  _geometry.pushUv(glm::vec2(0.0f, 1.0f));
  _geometry.build();
  _pause = false;
  _mode = mode::pause::UNKNOWN;
  _cMode = mode::pause::RESUME;
}

void	Pause::update(gdl::Clock const & clock, gdl::Input & input)
{
  (void)clock;
  (void)input;
  if (input.getKey(SDLK_s))
    {
      _cMode != mode::pause::QUIT ? _cMode += 1 : _cMode = mode::pause::RESUME;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_z))
    {
      _cMode != mode::pause::RESUME ? _cMode -= 1 : _cMode = mode::pause::QUIT;
      _ping.play();
      usleep(100000);
    }
  else if (input.getKey(SDLK_RETURN, true))
    {
      _mode = _cMode;
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}

void	Pause::draw(gdl::AShader & shader, gdl::Clock const & clock, const glm::vec3 &camera)
{
  (void)clock;
  (void)camera;
  _texture_pause[getcMode()].bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
}

bool	Pause::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  (void)src;
  (void)dest;
  (void)size;
  return false;
}

bool	Pause::getPause() const
{
  return (_pause);
}

void	Pause::startPause()
{
  _pause = true;
  usleep(100000);
}

void	Pause::stopPause()
{
  _pause = false;
}

int	Pause::getcMode() const
{
  return (_cMode);
}

int	Pause::getMode() const
{
  return (_mode);
}

void	Pause::resetMode()
{
  _mode = mode::pause::UNKNOWN;
  _cMode = mode::pause::RESUME;
}
