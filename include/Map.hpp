//
// Map.hpp for bomberman in /home/bevill_a/rendu/cpp_bomberman
//
// Made by Alexis Bevillard
// Login   <bevill_a@epitech.net>
//
// Started on  Sun May 24 15:05:48 2015 Alexis Bevillard
// Last update Fri Jun 12 14:52:01 2015 Louis Bouteillon
//

#pragma once

class Map;

#include		<fstream>
#include		<vector>
#include		<map>
#include		<glm/glm.hpp>
#include		<Geometry.hh>
#include		<Texture.hh>
#include		"AObject.hpp"

#define MAGIC_SIZE_X    50
#define MAGIC_SIZE_Z	30
#define CAMERA_Z	-10

#define RATIO_BLOCK	40

class			Map : public AObject
{
private:
  enum			type
    {
      MAP,
      BREAKABLE_CUBE,
      COUNT
    };

private:
  AObject		***_breakableCube;
  bool			**_map;
  gdl::Geometry		_geometry;
  std::string		_textureName[Map::COUNT];
  gdl::Texture		_texture[Map::COUNT];
  // gdl::Texture		_texture_speed;
  // gdl::Texture		_texture_range;
  // gdl::Texture		_texture_bomb;
  gdl::Texture		_texture_bonus[6];
  size_t		_width;
  size_t		_height;
  bool			_loadFile;
  const std::string	*_filename;
  std::vector<Cube*>	_objs;
  bool			_fromSave;

public:
  Map(size_t width,  size_t height);
  Map(const std::string &filename, bool fromSave = false);
  ~Map();

public:
  void			initialize();
  void			update(const gdl::Clock &clock, gdl::Input &input);
  void			draw(gdl::AShader &shader, const gdl::Clock &clock, const glm::vec3 &camera);
  bool			isInside(const glm::vec3 &src, const glm::vec3 &dest, float size) const;
  bool			destroyBlock(int x, int y, bool destroyIt);
  std::vector<Cube*>	getVec();
  void			deleteBonus(int i);
  int			getWidth() const;
  int			getHeight() const;
  std::string		getTextures() const;
  std::string		getLine(int i) const;
  void			loadFile(std::ifstream* saved = NULL);

private:
  void		        loadLine(int y, const std::string &line);
};

std::ostream&  operator<<(std::ostream &os, const Map &);