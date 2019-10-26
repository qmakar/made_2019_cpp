//
//  main.h
//  01
//
//  Created by qmakar on 25.10.2019.
//  Copyright © 2019 qmakar. All rights reserved.
//

#ifndef main_h
#define main_h

bool split(std::string, std::string, std::string&, std::string&, char&, bool&); // Разделение строки на 2 лексемы
double expr(std::string, unsigned long); // Вычисление выражения. Разделение по +-
double item(std::string, unsigned long); // Разделение по */

double str_to_double(std::string, unsigned long);  // Перевод строки в число
int check(std::string, unsigned long&); // Проверка строки на посторонние символы
void error_msg(std::string, unsigned long);


double str_to_double(std::string s, unsigned long pos)
{
  double result;
  std::stringstream convert(s);
  if (!(convert >> result))
  {
    for (long i = s.length() - 1; i >= 0; i-- )
    {
      if (!isdigit(s[i]))
      {
        throw pos - (s.length() - i - 1);
      }
    }
    throw pos;
  }
  return result;
}


int check(std::string str, unsigned long& pos)
{
  std::string all_oper = "*/-+";
  for (int i = 0; i < str.length(); i++)
  {
    if (not(isdigit(str[i]) || all_oper.find(str[i])!=std::string::npos))
    {
      pos = i;
      return 0;
    }
  }
  return 1;
}


void error_msg(std::string str, unsigned long pos)
{
  std::cout << "Can't parse string:" << std::endl;
  std::cout << str << std::endl;
  std::string stuff(pos, ' ');
  std::cout << stuff  << '^' << std::endl;
  std::cout << "Please, check your data!" << std::endl;
}


#endif /* main_h */
