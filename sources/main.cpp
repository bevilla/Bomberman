//
// main.cpp for bomberman in /home/feldma_a/rendu/cpp_bomberman/src_test
//
// Made by Alexis Feldmar
// Login   <feldma_a@epitech.net>
//
// Started on  Sat May 16 01:21:26 2015 Alexis Feldmar
// Last update Thu Jun 11 02:24:22 2015 Louis Bouteillon
//

#include <cstdlib>
#include "GameEngine.hpp"

int		main()
{
  GameEngine	engine;

  try
    {
      srand(time(NULL));
      engine.initialize();
      engine.intro();
      while (engine.update() == true)
	engine.draw();
    }
  catch (std::exception& e)
    {
      std::cerr << "Catched: " << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
