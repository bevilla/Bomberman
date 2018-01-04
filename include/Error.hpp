//
// Error.hpp for  in /home/cesar_a/rendu/cpp_bomberman
// 
// Made by aymeric cesar
// Login   <cesar_a@epitech.net>
// 
// Started on  Wed Jun 10 00:45:19 2015 aymeric cesar
// Last update Wed Jun 10 00:45:21 2015 aymeric cesar
//

#pragma once

#include <exception>

class BomberError: public std::exception
{
  public:
    BomberError(const std::string& msg)
    : _msg(msg) {}
    virtual ~BomberError() throw (){}
    const char* what() const throw () {return _msg.c_str();}
  protected:
    const std::string _msg;
};
