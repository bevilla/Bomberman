//
// Bomb.cpp for  in /home/cesar_a/rendu/cpp_bomberman
//
// Made by aymeric cesar
// Login   <cesar_a@epitech.net>
//
// Started on  Thu Jun  4 15:33:38 2015 aymeric cesar
// Last update Fri Jun 12 12:18:38 2015 Alexis Bevillard
//

#include "Bomb.hpp"

void	myPop(std::vector<Bomb*> &vec , Bomb* val)
{
  size_t	i = 0;

  while (i < vec.size() && vec[i] != val)
    ++i;
  vec.erase(vec.begin() + i);
}

Bomb::Bomb(sf::Sound &bombExplosion, std::vector<Bomb *> &bombz, gdl::Model &model, Marvin *marvin, std::vector<AObject*> &objs, const glm::vec3 &position) :
  _model(model),
  _bombz(bombz),
  _objs(objs),
  _marvin(marvin),
  _bombExplosion(bombExplosion)
{
  _position = position;
  _remTime = 180;
  _range = _marvin->getRange();
  _crossable = false;
  _bombz.push_back(this);
}


Bomb::~Bomb()
{
  for (size_t i = 0; i < _cubes.size(); i++)
    delete _cubes[i];
  myPop(_bombz, this);
  _marvin->getBomb();
}

void	Bomb::initialize()
{
  scale(glm::vec3(0.003, 0.003, 0.003));
  translate(glm::vec3(0, 0.5, 0));
  if (_texture_c.load("./textures/boom_c.tga") == false or
      _texture_h.load("./textures/boom_h.tga") == false or
      _texture_v.load("./textures/boom_v.tga") == false)
    throw BomberError("Error: failed to load explosion texture");
}

void	Bomb::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
  --_remTime;
  if (_remTime == 0)
    {
      _bombExplosion.play();
      _bombExplosion.setPlayingOffset(sf::milliseconds(500));
    }
  if (_remTime <= 0)
    explode(); // affiche les cubes avec les textures de feu
  for (unsigned int i = 0; i != _cubes.size(); ++i)
    _cubes[i]->update(clock, input);
  if (_remTime == -Bomb::EXPLODE_LAST - 1)
    delete this;
}

void	Bomb::explode()
{
  //horizontal
  //std::cout << "pos0: " << _position[0] << " | pos2: " << _position[2] << std::endl;
  for (int i = 0; i <= _range; ++i)
    {
      if (dynamic_cast<Map *>(_objs[0])->destroyBlock(i + _position[0], _position[2], _remTime == (-Bomb::EXPLODE_LAST - 1)))
	{
	  if (_remTime == -1)
	    {
	      Cube *cube = new Cube(_texture_h, _texture_h, _texture_v, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]) + 0.1, (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), false, false, true);
	      cube->initialize();
	      _cubes.push_back(cube);
	    }
	  break;
	}
      for (unsigned int j = 1; j < _objs.size(); j++)
	if (_objs[j]->getType() == AObject::PLAYER &&
	    static_cast<int>(_objs[j]->getPos().x + 0.5f) == static_cast<int>(_position.x + i) &&
	    static_cast<int>(_objs[j]->getPos().z + 0.5f) == static_cast<int>(_position.z))
	  {
	    _objs[j] = NULL;
	    _objs.erase(_objs.begin() + j);
	    --j;
	  }
      for (unsigned int j = 0; j < _bombz.size(); j++)
	if (static_cast<int>(_bombz[j]->getPos().x + 0.5f) == static_cast<int>(_position.x + i) &&
	    static_cast<int>(_bombz[j]->getPos().z + 0.5f) == static_cast<int>(_position.z))
	  {
	    _bombz[j]->makeExplode();
	  }
      if (_objs[0]->isInside(_position, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), 1.0))
	break;
      if (_remTime == -1)
	{
	  Cube *cube = new Cube((i == 0 ? _texture_c : _texture_h), _texture_h, _texture_v, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), false, false, true);
	  cube->initialize();
	  _cubes.push_back(cube);
	}
    }

  for (int i = 0; i >= -_range; --i)
    {
      if (dynamic_cast<Map *>(_objs[0])->destroyBlock(i + _position[0], _position[2], _remTime == (-Bomb::EXPLODE_LAST - 1)))
	{
	  if (_remTime == -1)
	    {
	      Cube *cube = new Cube(_texture_h, _texture_h, _texture_v, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]) + 0.1, (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), false, false, true);
	      cube->initialize();
	      _cubes.push_back(cube);
	    }
	  break;
	}
      for (unsigned int j = 0; j < _objs.size(); j++)
	if (_objs[j]->getType() == AObject::PLAYER &&
	    static_cast<int>(_objs[j]->getPos().x + 0.5f) == static_cast<int>(_position.x + i) &&
	    static_cast<int>(_objs[j]->getPos().z + 0.5f) == static_cast<int>(_position.z))
	  {
	    _objs[j] = NULL;
	    _objs.erase(_objs.begin() + j);
	    --j;
	  }
      for (unsigned int j = 0; j < _bombz.size(); j++)
	if (static_cast<int>(_bombz[j]->getPos().x + 0.5f) == static_cast<int>(_position.x + i) &&
	    static_cast<int>(_bombz[j]->getPos().z + 0.5f) == static_cast<int>(_position.z))
	  {
	    _bombz[j]->makeExplode();
	  }
      if (_objs[0]->isInside(_position, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), 1.0))
        break;
      if (_remTime == -1)
	{
	  Cube *cube = new Cube(_texture_h, _texture_h, _texture_v, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])) + i, trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2]))), false, false, true);
	  cube->initialize();
	  _cubes.push_back(cube);
	}
    }

  //vertical
  for (int i = 0; i <= _range; ++i)
    {
      if (dynamic_cast<Map *>(_objs[0])->destroyBlock(_position[0], _position[2] + i, _remTime == (-Bomb::EXPLODE_LAST - 1)))
	{
	  if (_remTime == -1)
	    {
	      Cube *cube = new Cube(_texture_v, _texture_v, _texture_h, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]) + 0.1, (trunc(_position[2]) == 0 ? 1 : trunc(_position[2] + i))), false, false, true);
	      cube->initialize();
	      _cubes.push_back(cube);
	    }
	  break;
	}
      for (unsigned int j = 0; j < _objs.size(); j++)
	if (_objs[j]->getType() == AObject::PLAYER &&
	    static_cast<int>(_objs[j]->getPos().x + 0.5f) == static_cast<int>(_position.x) &&
	    static_cast<int>(_objs[j]->getPos().z + 0.5f) == static_cast<int>(_position.z + i))
	  {
	    _objs[j] = NULL;
	    _objs.erase(_objs.begin() + j);
	    --j;
	  }
      for (unsigned int j = 0; j < _bombz.size(); j++)
	if (static_cast<int>(_bombz[j]->getPos().x + 0.5f) == static_cast<int>(_position.x) &&
	    static_cast<int>(_bombz[j]->getPos().z + 0.5f) == static_cast<int>(_position.z + i))
	  {
	    _bombz[j]->makeExplode();
	  }
      if (_objs[0]->isInside(_position, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2])) + i), 1.0))
        break;
      if (_remTime == -1)
	{
	  Cube *cube = new Cube(_texture_v, _texture_v, _texture_h, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2])) + i), false, false, true);
	  cube->initialize();
	  _cubes.push_back(cube);
	}
    }

  for (int i = 0; i >= -_range; --i)
    {
      if (dynamic_cast<Map *>(_objs[0])->destroyBlock(_position[0], _position[2] + i, _remTime == (-Bomb::EXPLODE_LAST - 1)))
	{
	  if (_remTime == -1)
	    {
	      Cube *cube = new Cube(_texture_v, _texture_v, _texture_h, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]) + 0.1, (trunc(_position[2]) == 0 ? 1 : trunc(_position[2] + i))), false, false, true);
	      cube->initialize();
	      _cubes.push_back(cube);
	    }
	  break;
	}
      for (unsigned int j = 0; j < _objs.size(); j++)
	if (_objs[j]->getType() == AObject::PLAYER &&
	    static_cast<int>(_objs[j]->getPos().x + 0.5f) == static_cast<int>(_position.x) &&
	    static_cast<int>(_objs[j]->getPos().z + 0.5f) == static_cast<int>(_position.z + i))
	  {
	    _objs[j] = NULL;
	    _objs.erase(_objs.begin() + j);
	    --j;
	  }
      for (unsigned int j = 0; j < _bombz.size(); j++)
	if (static_cast<int>(_bombz[j]->getPos().x + 0.5f) == static_cast<int>(_position.x) &&
	    static_cast<int>(_bombz[j]->getPos().z + 0.5f) == static_cast<int>(_position.z) + i)
	  {
	    _bombz[j]->makeExplode();
	  }
      if (_objs[0]->isInside(_position, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2])) + i), 1.0))
        break;
      if (_remTime == -1)
	{
	  Cube *cube = new Cube(_texture_v, _texture_v, _texture_h, Cube::NOPE, glm::vec3((trunc(_position[0]) == 0 ? 1 : trunc(_position[0])), trunc(_position[1]), (trunc(_position[2]) == 0 ? 1 : trunc(_position[2])) + i), false, false, true);
	  cube->initialize();
	  _cubes.push_back(cube);
	}
    }
}

void    Bomb::makeExplode()
{
  if (_remTime > 0)
    _remTime = 0;
}

void	Bomb::draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera)
{
  (void)shader;
  (void)clock;
  (void)camera;
  _model.draw(shader, getTransformation(), clock.getElapsed());
  for (unsigned int i = 0; i != _cubes.size(); ++i)
    _cubes[i]->draw(shader, clock, camera);
}

bool	Bomb::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  int		x1 = (src.x + 0.5f);// + ((dest.x < src.x) ? -size : size));
  int		y1 = (src.z + 0.5f);// + ((dest.z < src.z) ? -size : size));
  int		x2 = (dest.x + 0.5f);// + ((dest.x < src.x) ? -size : size));
  int		y2 = (dest.z + 0.5f);// + ((dest.z <= src.z) ? -size : size));

  (void)size;
  if (static_cast<int>(_position.x) == x1 &&
      static_cast<int>(_position.z) == y1)
    return false;
  if (static_cast<int>(_position.x) == x2 &&
      static_cast<int>(_position.z) == y2)
    return true;
  return false;
}

int	Bomb::getRemtime() const
{
  return (_remTime);
}

int	Bomb::getRange() const
{
  return (_range);
}
