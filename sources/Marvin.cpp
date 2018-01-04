//
// Marvin.cpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Mon May 25 12:21:01 2015 Alexis Bevillard
// Last update Sat Jun 13 00:11:40 2015 Louis Bouteillon
//

#include	<glm/gtc/matrix_transform.hpp>
#include	<SdlContext.hh>
#include	"Marvin.hpp"

Marvin::Marvin(sf::SoundBuffer &bombExplosion, sf::SoundBuffer &up, std::vector<Bomb *> &bombz, const std::vector<AObject*> &objs, Map *map, t_play play, const glm::vec3 &position) :
  _speed(0.06f),
  _objs(objs),
  _bombz(bombz),
  _isRunning(false),
  _map(map),
  _play(play)
{
  _position = position;
  _type = AObject::PLAYER;
  _crossable = true;
  _maxBombz = 2;
  _nbBombz = 0;
  _range = 2;
  _bombExplosion.setBuffer(bombExplosion);
  _up.setBuffer(up);
  if (_play == Marvin::PLAY2)
    _rotation = glm::vec3(0, 1, 0) * 180.f;
}

Marvin::~Marvin()
{
}

void		Marvin::initialize()
{
  if (_model.load("./lib/assets/marvin.fbx") == false)
    throw BomberError("Error: cannot load Marvin model");
  scale(glm::vec3(PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE));
  translate(glm::vec3(0, -0.5, 0));
  _model.createSubAnim(0, "idle", 0, 0);
  _model.createSubAnim(0, "start_run", 0, 31);
  _model.createSubAnim(0, "run", 35, 53);
  _model.createSubAnim(0, "end_run", 57, 120);
  for (unsigned int i = 0; i != _objs.size(); ++i)
    std::cout << "marvin: " << (_objs[i]->getPos())[0] << std::endl;
  if (_bomb.load("./lib/assets/bomb.fbx") == false)
    throw BomberError("Error: cannot load Bomb model");

  if (_play == PLAY1)
  {
    if (!_nameTexture.load("./textures/player1.tga"))
      throw BomberError("Error: cannot load Player1 texture");
  }
  else if (_play == PLAY2)
  {
    if (!_nameTexture.load("./textures/player2.tga"))
      throw BomberError("Error: cannot load Player2 texture");
  }
  else if (!_nameTexture.load("./textures/CPU.tga"))
    throw BomberError("Error: cannot load CPU texture");
  _nameGeometry.pushVertex(glm::vec3(-0.6f, 0.f, -0.2f));
  _nameGeometry.pushVertex(glm::vec3(0.6f, 0.f, -0.2f));
  _nameGeometry.pushVertex(glm::vec3(0.6f, 0.f, 0.2f));
  _nameGeometry.pushVertex(glm::vec3(-0.6f, 0.f, 0.2f));
  _nameGeometry.pushUv(glm::vec2(1.f, 0.f));
  _nameGeometry.pushUv(glm::vec2(0.f, 0.f));
  _nameGeometry.pushUv(glm::vec2(0.f, 1.f));
  _nameGeometry.pushUv(glm::vec2(1.f, 1.f));
  _nameGeometry.build();
}
/*
int		get_dist(const glm::vec3 &v1, const glm::vec3 &v2)
{
  int		dist;

  dist = v1.x - v2.x;
  if (dist != 0)
    dist = dist * dist;
  else
    return (sqrt((v1.z - v2.z) * (v1.z - v2.z)));
  if ((v1.z - v2.z) == 0)
    return (sqrt(dist));
  dist = dist / ((v1.z - v2.z) * (v1.z - v2.z));
  return (sqrt(dist));
}

Marvin		*Marvin::get_closest_player() const
{
  Marvin	*closest;
  Marvin	*tmp;
  int		dist;
  int		tmpdist;
  size_t	i;

  if (_players[0] == this)
    i++;
  closest = _players[i];
  i++;
  dist = get_dist(_position, closest->getPos());
  for (; i < _players.size(); ++i)
    {
      tmp = _players[i];
      if ((tmpdist = get_dist(_position, tmp->getPos())) < dist)
	{
	  dist = tmpdist;
	  closest = tmp;
	}
    }
  return (closest);
}

bool		Marvin::shoot_if_possible(Marvin *player)
{
  std::cout << "j'essaye de tirer" << std::endl;
  if (get_dist(_position, player->getPos()) <= _range)
    if (player->getPos().x == _position.x || player->getPos().z == _position.z)
      {
	Bomb *bomb = new Bomb(_bombz, _bomb, this, const_cast<std::vector<AObject*>&>(_objs), _position);
	bomb->initialize();
	_bombz.push_back(bomb);
	++_nbBombz;
	std::cout << "Ca marche ! =)" << std::endl;
	return (true);
      }
  std::cout << "Ca vaut pas le coup en fait" << std::endl;
  return (false);
}

Bomb		*Marvin::bomb_near_me() const
{
  for (size_t i = 0; i < _bombz.size(); ++i)
    {
      if (_bombz[i]->getPos().x == _position.x ||
	  _bombz[i]->getPos().z == _position.z)
	if (get_dist(_bombz[i]->getPos(), _position) < _bombz[i]->getRange())
	  return (_bombz[i]);
    }
  return (NULL);
}

void		Marvin::evade_from(Bomb *bomb)
{
  int		x;
  int		z;

  x = bomb->getPos().x - _position.x;
  z = bomb->getPos().z - _position.z;
  if (x == 0)
    {
      if (z < 0)
	z = 1;
      else
	z = -1;
    }
  else if (z == 0)
    {
      if (z < 0)
	x = 1;
      else
	x = -1;
    }
  std::cout << "je m'echappe d'une bombe" << std::endl;
  if (isInside(_position, glm::vec3(_position.x + (x * _speed),
				    _position.y, _position.z + (z * _speed)), 0.f))
    translate(glm::vec3(x * _speed, 0, z * _speed));
}

void		Marvin::ia()
{
  Bomb		*bomb;
  Marvin	*tmp;
  int		pm;

  pm = 1;
  if (_nbBombz < _maxBombz)
    {
      tmp = get_closest_player();
      if (!shoot_if_possible(tmp))
	{
	  //move_towards(tmp);
	  std::cout << "je bouge après avoir voulu tirer" << std::endl;
	  pm--;
	  shoot_if_possible(tmp);
	}
    }
  if (pm && (bomb = bomb_near_me()))
    evade_from(bomb);
  else if (pm)
    {
      std::cout << "je bouge parce que j'ai que ça a foutre" << std::endl;
      //move_towards(tmp);
      pm--;
    }
  //(Map*)_map;
  //(std::vector<Cube*>)_bonus;
  //(std::vector<AObject*>)_objs;
  //_nbBombz;
  //_maxBombz;
  //_range;
  //isInside(_position, glm::ve3c(_position.x, _position.y, _position.z + _speed), 0.f);
  //translate(glm::vec3(0, 0, _speed));
}
*/
void		Marvin::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  // if (_play == CPU)
  //   ia();
  if (_play != CPU)
    {
      _direction = 0;
      _direction |= input.getInput(SDLK_q) ? Marvin::LEFT : 0;
      _direction |= input.getInput(SDLK_z) ? Marvin::UP : 0;
      _direction |= input.getInput(SDLK_d) ? Marvin::RIGHT : 0;
      _direction |= input.getInput(SDLK_s) ? Marvin::DOWN : 0;
      _direction2 = 0;
      _direction2 |= input.getInput(SDLK_LEFT) ? Marvin::LEFT : 0;
      _direction2 |= input.getInput(SDLK_UP) ? Marvin::UP : 0;
      _direction2 |= input.getInput(SDLK_RIGHT) ? Marvin::RIGHT : 0;
      _direction2 |= input.getInput(SDLK_DOWN) ? Marvin::DOWN : 0;
      if (((input.getInput(SDLK_SPACE) && _nbBombz < _maxBombz) && _play == PLAY1)
	  || ((input.getInput(SDLK_KP_0) && _nbBombz < _maxBombz) && _play == PLAY2))
	{
	  glm::vec3 pos =  glm::vec3(static_cast<int>(_position.x + 0.5f),
				     _position.y,
				     static_cast<int>(_position.z + 0.5f));
	  bool	flag = true;

	  for (size_t i = 0; i < _bombz.size(); i++)
	    if (static_cast<int>(_bombz[i]->getPos().x) == static_cast<int>(pos.x) &&
		static_cast<int>(_bombz[i]->getPos().y) == static_cast<int>(pos.y) &&
		static_cast<int>(_bombz[i]->getPos().z) == static_cast<int>(pos.z))
	      {
		flag = false;
		break;
	      }
	  if (flag)
	    {
	      Bomb *bomb = new Bomb(_bombExplosion, _bombz, _bomb, this, const_cast<std::vector<AObject*>&>(_objs), pos);
	      bomb->initialize();
	      //_bombz.push_back(bomb);
	      ++_nbBombz;
	    }
	}
      if (_play == PLAY1)
	{
	  move_play1();
	  rotate_play1();
	}
      else if (_play == PLAY2)
	{
	  move_play2();
	  rotate_play2();
	}
      if (((_direction && _play == PLAY1) || (_direction2 && _play == PLAY2)) && !_isRunning)
	{
	  _model.setCurrentSubAnim("run");
	  _isRunning = true;
	}
      else if ((!_direction && _play == PLAY1) || (!_direction2 && _play == PLAY2))
	{
	  _model.setCurrentSubAnim("idle");
	  _isRunning = false;
	}
    }
  unsigned int i = 0;
  while (i < _bombz.size())
    {
      unsigned int save = _bombz.size();
      _bombz[i]->update(clock, input);
      if (_bombz.size() == save)
        ++i;
    }
  _bonus = _map->getVec();
  glm::vec3 pos =  glm::vec3(static_cast<int>(_position.x + 0.5f),
			     _position.y,
			     static_cast<int>(_position.z + 0.5f));
  for (size_t i = 0; i < _bonus.size(); i++)
    if (static_cast<int>(_bonus[i]->getPos().x) == static_cast<int>(pos.x) &&
	static_cast<int>(_bonus[i]->getPos().y) == static_cast<int>(pos.y) &&
	static_cast<int>(_bonus[i]->getPos().z) == static_cast<int>(pos.z))
      {
	if (_bonus[i]->getBonus() == Cube::SPEED)
	  {
	    _speed *= 1.2f;
	    _map->deleteBonus(i);
	  }
	else if (_bonus[i]->getBonus() == Cube::RANGE)
	  {
	    ++_range;
	    _map->deleteBonus(i);
	  }
	else if (_bonus[i]->getBonus() == Cube::BOMB)
	  {
	    ++_maxBombz;
	    _map->deleteBonus(i);
	  }
	_up.play();
      }
}
      /*if (_bombz[i]->getRemtime() < -Bomb::EXPLODE_LAST)
	{
	  delete _bombz[i];
	  _bombz.erase(_bombz.begin() + i);
	  --i;
	  --_nbBombz;
	}
	else*/

void		Marvin::draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera)
{
  (void)camera;
  _model.draw(shader, getTransformation(), clock.getElapsed());
  for (unsigned int i = 0; i != _bombz.size(); ++i)
    _bombz[i]->draw(shader, clock, camera);
  _nameTexture.bind();
  glm::mat4 lel(1);
  glm::vec3 prout = glm::vec3(_position.x, _position.y + 2.5, _position.z);
  lel = glm::translate(lel, prout);
  lel = glm::rotate(lel, -45.f, glm::vec3(1, 0, 0));
  _nameGeometry.draw(shader, lel, GL_QUADS);
}

bool		Marvin::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
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

void		Marvin::rotate_play1()
{
  if ((_direction & Marvin::UP) && (_direction & Marvin::RIGHT))
    _rotation = glm::vec3(0, 1, 0) * -45.f;
  else if ((_direction & Marvin::DOWN) && (_direction & Marvin::RIGHT))
    _rotation = glm::vec3(0, 1, 0) * -135.f;
  else if ((_direction & Marvin::DOWN) && (_direction & Marvin::LEFT))
    _rotation = glm::vec3(0, 1, 0) * 135.f;
  else if ((_direction & Marvin::UP) && (_direction & Marvin::LEFT))
    _rotation = glm::vec3(0, 1, 0) * 45.f;
  else if (_direction & Marvin::LEFT)
    _rotation = glm::vec3(0, 1, 0) * 90.f;
  else if (_direction & Marvin::UP)
    _rotation = glm::vec3(0, 1, 0);
  else if (_direction & Marvin::RIGHT)
    _rotation = glm::vec3(0, 1, 0) * -90.f;
  else if (_direction & Marvin::DOWN)
    _rotation = glm::vec3(0, 1, 0) * 180.f;
}

void		Marvin::rotate_play2()
{
  if ((_direction2 & Marvin::UP) && (_direction2 & Marvin::RIGHT))
    _rotation = glm::vec3(0, 1, 0) * -45.f;
  else if ((_direction2 & Marvin::DOWN) && (_direction2 & Marvin::RIGHT))
    _rotation = glm::vec3(0, 1, 0) * -135.f;
  else if ((_direction2 & Marvin::DOWN) && (_direction2 & Marvin::LEFT))
    _rotation = glm::vec3(0, 1, 0) * 135.f;
  else if ((_direction2 & Marvin::UP) && (_direction2 & Marvin::LEFT))
    _rotation = glm::vec3(0, 1, 0) * 45.f;
  else if (_direction2 & Marvin::LEFT)
    _rotation = glm::vec3(0, 1, 0) * 90.f;
  else if (_direction2 & Marvin::UP)
    _rotation = glm::vec3(0, 1, 0);
  else if (_direction2 & Marvin::RIGHT)
    _rotation = glm::vec3(0, 1, 0) * -90.f;
  else if (_direction2 & Marvin::DOWN)
    _rotation = glm::vec3(0, 1, 0) * 180.f;
}

void		Marvin::move_play1()
{
  glm::vec3	tmp = _position;

  if (_direction & Marvin::UP)
    {
      tmp = _position;
      translate(glm::vec3(0, 0, _speed));
      for (size_t i = 0; i < _objs.size(); i++)
	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction & Marvin::DOWN)
    {
      tmp = _position;
      translate(glm::vec3(0, 0, -_speed));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
       	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction & Marvin::LEFT)
    {
      tmp = _position;
      translate(glm::vec3(_speed, 0, 0));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
       	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction & Marvin::RIGHT)
    {
      tmp = _position;
      translate(glm::vec3(-_speed, 0, 0));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
}

void		Marvin::move_play2()
{
  glm::vec3	tmp = _position;

  if (_direction2 & Marvin::UP)
    {
      tmp = _position;
      translate(glm::vec3(0, 0, _speed));
      for (size_t i = 0; i < _objs.size(); i++)
	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction2 & Marvin::DOWN)
    {
      tmp = _position;
      translate(glm::vec3(0, 0, -_speed));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
       	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction2 & Marvin::LEFT)
    {
      tmp = _position;
      translate(glm::vec3(_speed, 0, 0));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
       	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
  if (_direction2 & Marvin::RIGHT)
    {
      tmp = _position;
      translate(glm::vec3(-_speed, 0, 0));
      for (size_t i = 0; i < _objs.size(); i++)
       	if (!_objs[i]->isCrossable() && _objs[i]->isInside(tmp, _position, 0.2f))
       	  _position = tmp;
      for (unsigned int i = 0; i != _bombz.size(); ++i)
	if (_bombz[i]->isInside(tmp, _position, 0.2f))
	  _position = tmp;
    }
}

void		Marvin::getBomb()
{
  --_nbBombz;
}

int		Marvin::getRange() const
{
  return (_range);
}
