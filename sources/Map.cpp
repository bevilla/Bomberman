//
// Map.cpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sun May 24 15:05:32 2015 Alexis Bevillard
// Last update Sat Jun 13 01:09:34 2015 Louis Bouteillon
//

#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	"Cube.hpp"
#include	"Map.hpp"

Map::Map(size_t width, size_t height) :
  _width(width),
  _height(height),
  _filename(NULL)
{
  _type = AObject::MAP;
  _loadFile = false;
  _textureName[Map::MAP] = "./textures/map.tga";
  _textureName[Map::BREAKABLE_CUBE] = "./textures/breakable_cube.tga";

  _map = new bool*[_width];
  for (size_t i = 0; i < _width; i++)
    {
      _map[i] = new bool[_height];
      for (size_t j = 0; j < _height; j++)
	_map[i][j] = false;
    }

  _breakableCube = new AObject**[_width];
  for (size_t i = 0; i < _width; i++)
    {
      _breakableCube[i] = new AObject*[_height];
      for (size_t j = 0; j < _height; j++)
	_breakableCube[i][j] = NULL;
    }
}

Map::Map(const std::string &filename, bool fromSave) :
  _loadFile(true),
  _filename(&filename),
  _fromSave(fromSave)
{
}

Map::~Map()
{
  for (size_t i = 0; i < _width; i++)
    delete[] _map[i];
  delete[] _map;

  for (size_t i = 0; i < _width; i++)
    {
      for (size_t j = 0; j < _height; j++)
	if (_breakableCube[i][j])
	  delete _breakableCube[i][j];
      delete[] _breakableCube[i];
    }
  delete[] _breakableCube;
}

void		Map::initialize()
{
  if (_loadFile && !_fromSave)
    loadFile();
  _geometry.pushVertex(glm::vec3(-0.5f, -0.5f, -0.5f));
  _geometry.pushVertex(glm::vec3(_width - 0.5f, -0.5f, -0.5f));
  _geometry.pushVertex(glm::vec3(_width - 0.5f, -0.5f, _height - 0.5f));
  _geometry.pushVertex(glm::vec3(-0.5f, -0.5f, _height - 0.5f));
  _geometry.pushUv(glm::vec2(0.f, 0.f));
  _geometry.pushUv(glm::vec2(0.f, 1.f));
  _geometry.pushUv(glm::vec2(0.5f, 1.f));
  _geometry.pushUv(glm::vec2(0.5f, 0.f));

  if (!_texture[Map::MAP].load(_textureName[Map::MAP]))
    throw BomberError("Error: cannot load map texture '" + _textureName[Map::MAP] + "'");
  if (!_texture[Map::BREAKABLE_CUBE].load(_textureName[Map::BREAKABLE_CUBE]))
    throw BomberError("Error: cannot load breakable texture '" + _textureName[Map::BREAKABLE_CUBE] + "'");
  if (!_texture_bonus[0].load("./textures/bonus_speed.tga") or
      !_texture_bonus[1].load("./textures/bonus_range.tga") or
      !_texture_bonus[2].load("./textures/bonus_bomb.tga") or
      !_texture_bonus[3].load("./textures/bonus_speed_top.tga") or
      !_texture_bonus[4].load("./textures/bonus_range_top.tga") or
      !_texture_bonus[5].load("./textures/bonus_bomb_top.tga"))
    throw BomberError("Error: cannot load Bonus textures");
  if (!_loadFile)
    {
      for (size_t y = 0; y < _height; y++)
	for (size_t x = 0; x < _width; x++)
	  {
	    if (y == 0 || x == 0 || y == _height - 1 || x == _width - 1 ||
		((_width % 2 ? x % 2 == 0 : (x < _width / 2 ? x % 2 == 0: x % 2)) &&
		 (_height % 2 ? y % 2 == 0 : (y < _height / 2 ? y % 2 == 0: y % 2))))
	      {
		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
		_geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
		_geometry.pushUv(glm::vec2(0.5f, 0.f));
		_geometry.pushUv(glm::vec2(0.5f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 1.f));
		_geometry.pushUv(glm::vec2(1.f, 0.f));

		_map[x][y] = true;
	      }
	    else if (rand() % 100 < RATIO_BLOCK)
	      {
		_breakableCube[x][y] = new Cube(_texture[Map::BREAKABLE_CUBE], _texture[Map::BREAKABLE_CUBE], _texture[Map::BREAKABLE_CUBE], Cube::NOPE, glm::vec3(x, 0, y), true, false, false);
		_breakableCube[x][y]->initialize();
		_map[x][y] = true;
	      }
	  }
    }
  _geometry.build();
}

void		Map::update(const gdl::Clock &clock, gdl::Input &input)
{
  (void)clock;
  (void)input;
}

void		Map::draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera)
{
  _texture[Map::MAP].bind();
  _geometry.draw(shader, getTransformation(), GL_QUADS);
  for (size_t y = 0; y < _height; y++)
    for (size_t x = 0; x < _width; x++)
      if (x > (camera.x - MAGIC_SIZE_X) && x < (camera.x + MAGIC_SIZE_X) &&
	  y > (camera.z - CAMERA_Z - MAGIC_SIZE_Z) && y < (camera.z - CAMERA_Z + MAGIC_SIZE_Z) &&
	  _breakableCube[x][y])
	_breakableCube[x][y]->draw(shader, clock, camera);
  for (size_t i = 0; i < _objs.size(); i++)
    _objs[i]->draw(shader, clock, camera);
}

bool		Map::isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const
{
  int		x1 = (src.x + 0.5f);// + ((dest.x < src.x) ? -size : size));
  int		y1 = (src.z + 0.5f);// + ((dest.z < src.z) ? -size : size));
  int		x2 = (dest.x + 0.5f);// + ((dest.x < src.x) ? -size : size));
  int		y2 = (dest.z + 0.5f);// + ((dest.z <= src.z) ? -size : size));

  (void)size;
  if (x2 < 0 || y2 < 0 || x2 >= static_cast<int>(_width) || y2 >= static_cast<int>(_height))
    return true;
  if (_map[x1][y1])
    return false;
  if (_map[x2][y2])
    return true;
  return false;
}

bool		Map::destroyBlock(int x, int y, bool destroyIt)
{
  if (x < 0 || y < 0 || x >= static_cast<int>(_width) || y >= static_cast<int>(_height))
    return false;
  if (_map[x][y] && _breakableCube[x][y] && destroyIt)
    {
      _map[x][y] = false;
      delete _breakableCube[x][y];
      _breakableCube[x][y] = NULL;
      int bonus = rand() % 100;
      if (bonus < 10)
	{
	  Cube *Bonus = new Cube(_texture_bonus[0], _texture_bonus[3], _texture_bonus[3], Cube::SPEED, glm::vec3(x, 0, y), false, true, false);
	  Bonus->initialize();
	  _objs.push_back(Bonus);
	}
      else if (bonus >= 30 && bonus < 40)
	{
	  Cube *Bonus = new Cube(_texture_bonus[1], _texture_bonus[4], _texture_bonus[4], Cube::RANGE, glm::vec3(x, 0, y), false, true, false);
	  Bonus->initialize();
	  _objs.push_back(Bonus);
	}
      else if (bonus >= 80 && bonus < 90)
	{
	  Cube *Bonus = new Cube(_texture_bonus[2], _texture_bonus[5], _texture_bonus[5], Cube::BOMB, glm::vec3(x, 0, y), false, true, false);
	  Bonus->initialize();
	  _objs.push_back(Bonus);
	}
      return true;
    }
  return ((_map[x][y] && _breakableCube[x][y]));
}

void		Map::loadFile(std::ifstream *saved)
{
  std::ifstream	*file;
  std::string	line;
  int		nbline = 0;

  if (_fromSave)
    file = saved;
  else
    file = new std::ifstream(_filename->c_str());
  if (!file->is_open())
    throw BomberError("Error: cannot open '" + *_filename + "'");
  while (getline(*file, line))
    {
      if (nbline == static_cast<int>(_height) + Map::COUNT + 2)
	throw BomberError("Error: map too big");
      if (nbline < Map::COUNT + 2)
	{
	  if (nbline == 0)
	    _width = atoi(line.c_str());
	  else if (nbline == 1)
	    _height = atoi(line.c_str());
	  else
	    _textureName[nbline - 2] = line;
	  if (nbline == 2)
	    {
	      _map = new bool*[_width];
	      for (size_t i = 0; i < _width; i++)
		{
		  _map[i] = new bool[_height];
		  for (size_t j = 0; j < _height; j++)
		    _map[i][j] = false;
		}

	      _breakableCube = new AObject**[_width];
	      for (size_t i = 0; i < _width; i++)
		{
		  _breakableCube[i] = new AObject*[_height];
		  for (size_t j = 0; j < _height; j++)
		    _breakableCube[i][j] = NULL;
		}
	    }
	}
      else
	loadLine(nbline - Map::COUNT - 2, line);
      nbline++;
    }
  if (!_fromSave)
    (file->close(), delete file);
}

void		Map::loadLine(int y, const std::string &line)
{
  if (line.size() != _width)
    throw BomberError("Error: here line " + std::to_string(y + Map::COUNT + 3) + ": line too long (length " + std::to_string(line.size()) + ") " + line);
  for (size_t x = 0; x < line.size(); x++)
    {
      if (line[x] == '1')
	{
	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, -0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, -0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _geometry.pushVertex(glm::vec3(-0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(-0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, 0.5f, 0.5f + y));
	  _geometry.pushVertex(glm::vec3(0.5f + x, -0.5f, 0.5f + y));
	  _geometry.pushUv(glm::vec2(0.5f, 0.f));
	  _geometry.pushUv(glm::vec2(0.5f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 1.f));
	  _geometry.pushUv(glm::vec2(1.f, 0.f));

	  _map[x][y] = true;
	}
      else if (line[x] == '2')
	{
	  _breakableCube[x][y] = new Cube(_texture[Map::BREAKABLE_CUBE], _texture[Map::BREAKABLE_CUBE], _texture[Map::BREAKABLE_CUBE], Cube::NOPE, glm::vec3(x, 0, y), true, false, false);
	  _breakableCube[x][y]->initialize();
	  _map[x][y] = true;
	}
      else if (line[x] != '0')
	throw BomberError("Error: " + std::to_string(y + Map::COUNT + 3) + "," + std::to_string(x) + ": invalid character '" + line[x] + "'");
    }
}

std::vector<Cube*>	Map::getVec()
{
  return (_objs);
}

void			Map::deleteBonus(int pos)
{
  int i = -1;
  while (++i != pos);
  _objs.erase(_objs.begin() + i);
}

int			Map::getWidth() const
{
  return (_width);
}

int			Map::getHeight() const
{
  return (_height);
}

std::string		Map::getLine(int i) const
{
  std::string	str("");

  for (unsigned int j = 0; j < _width; ++j)
  {
    str += (_map[j][i] ? (_breakableCube[j][i] == NULL ? "1" : "2") : "0");
  }
  return str;
}

std::string		Map::getTextures() const
{
  return (_textureName[Map::MAP] + "\n" + _textureName[Map::BREAKABLE_CUBE]);
}

std::ostream&  operator<<(std::ostream &os, const Map &map)
{
  os << map.getWidth() << "\n";
  os << map.getHeight() << "\n";
  os << map.getTextures() << "\n";

  for (int i = 0; i < map.getHeight(); ++i)
  {
    os << map.getLine(i) << "\n";
  }
  return os;
}
