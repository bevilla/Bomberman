//
// Mode.hpp for bomberman in /home/boutei_l/rendu/cpp_bomberman
//
// Made by Louis Bouteillon
// Login   <boutei_l@epitech.net>
//
// Started on  Wed Jun  3 14:12:13 2015 Louis Bouteillon
// Last update Wed Jun 10 18:20:35 2015 Louis Bouteillon
//

#pragma once

namespace	mode
{

  namespace	gen
  {
    enum	gen_mode
      {
	MENU,
	GAME,
	LOAD,
	CREDIT,
	OPTION,
	GAME_OVER,
	UNKNOWN
      };
  }

  namespace	menu
  {
    enum	menu_mode
      {
	START,
	LOAD,
	OPTION,
	CREDIT,
	QUIT,
	UNKNOWN
      };
  }

  namespace	game
  {
    enum	game_mode
      {
	SOLO,
	MULTI,
	BACK,
	UNKNOWN
      };
  }

  namespace	load
  {
    enum	load_mode
      {
	SOLO,
	MULTI,
	UNKNOWN
      };
  }

  namespace	win
  {
    enum	win_mode
      {
	WIN1,
	WIN2,
	UNKNOWN
      };
  }

  namespace	credit
  {
    enum	credit_mode
      {
	NM,
	BACK,
	UNKNOWN
      };
  }

  namespace	pause
  {
    enum	pause_mode
      {
	RESUME,
	RESTART,
	S_C,
	S_Q,
	QUIT,
	UNKNOWN
      };
  }

  namespace	game_over
  {
    enum	game_over_mode
      {
	MAIN_MENU,
	QUIT,
	UNKNOWN
      };
  }

  namespace	intro
  {
    enum	intro_mode
      {
	BB0,
	BB1,
	BB2,
	BB3,
	BB4,
	BB5,
	BB6,
	BB7,
	BB8,
	BB9,
	D0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	D8,
	D9,
	D10,
	D11,
	G0,
	G1,
	G2,
	G3,
	G4,
	G5,
	G6,
	G7,
	G8,
	G9,
	G10,
	G11,
	G12,
	L0,
	L1,
	L2,
	L3,
	L4,
	L5,
	UNKNOWN
      };
  }

}
