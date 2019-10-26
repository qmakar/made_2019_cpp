//
//  main.cpp
//  01
//
//  Created by qmakar on 25.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.

#include <iostream>
#include <sstream>

#include "main.h"



bool split(std::string source, std::string operations, std::string& lex1, std::string& lex2, char& op)
{
  long i = source.length() - 1;
  bool t;
  std::string all_oper = "*/-+";
  do
  {
    t = (i > 0) &&
        (operations.find(source[i]) != std::string::npos) &&
        (all_oper.find(source[i-1]) == std::string::npos);
    i--;
  }
  while ((i >= 0) && (!t));
  if (t)
  {
    i++;
    lex1 = source.substr(0, i);
    lex2 = source.substr(i + 1);
    op=source[i];
//    std::cout << lex1 << " " << lex2 << std::endl;
    return true;
  }
  return false;
  
}

double expr(std::string source, unsigned long pos)
{
  std::string lex1, lex2;
  char op;
  if (!split(source, "+-", lex1, lex2, op))
  {
//    std::cout << lex1 << " !!! " << lex2 << " " <<source << std::endl;
    return item(source, pos);
    
  }
  else
  {
    if (!isdigit(lex2[0]) && lex2[0] != '-')
    {
      throw pos - lex2.length();
    }
    switch(op)
    {
      case '+':
        return expr(lex1, pos - lex2.length()) + item(lex2, pos);
      default: // case '-':
        if (lex2.length()>=2 && lex2[0] == '-' && !isdigit(lex2[1]))
        {
          throw pos - lex2.length();
        }
        return expr(lex1, pos - lex2.length()) - item(lex2, pos);
    }
  }
}

double item(std::string source, unsigned long pos)
{
  std::string lex1, lex2;
  char op;
  
  if (!split(source, "*/", lex1, lex2, op))
  {
//      std::cout << lex1 << " !!! " << lex2 << " " <<source << std::endl;
      return str_to_double(source, pos);
  }
  else
  {
    if (!isdigit(lex2[0]) && lex2[0] != '-')
    {
      throw pos - lex2.length();
    }
    switch(op)
    {
      case '*':
        return item(lex1, pos - lex2.length() - 1) * str_to_double(lex2, pos);
      default: // case '/':
        return item(lex1, pos - lex2.length() - 1) / str_to_double(lex2, pos);
    }
  }
}

int main(int argc, const char * argv[])
{
  std::string str(argv[1]);
  str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
  
  unsigned long pos = str.length();
  if (not(check(str, pos)))
  {
    error_msg(str, pos);
    return -1;
  }
  
  try
  {
    double result = expr(str, pos-1);
    std::cout << std::fixed << result << std::endl;
  }
  catch(unsigned long bad_pos)
  {
    error_msg(str, bad_pos);
    return -1;
  }
  
  return 0;
}
