/*
 Copyright (C) 2006 Mark Joshi
 Copyright (C) 2011 Narinder Claire


 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#include <fstream>
#include"OutputterHelper.h"

void PushBack(std::string& str, char c)
{
  std::string tmp("0");
  tmp[0]=c;
  str.append(tmp);

}
void AddLine(std::vector<char>& file, std::string line)
{
  for (unsigned long i=0; i < line.size(); i++)
    file.push_back(line[i]);

  file.push_back('\n');
}

std::string strip(std::string in) {
  for (size_t i=in.length()-1; i; --i)
    if (in[i] == '/' || in[i] == '\\')
      return in.substr(i + 1, in.length() - i);
  return in;
}

std::string getdir(std::string in) {
  for (size_t i=in.length()-1; i; --i)
    if (in[i] == '/' || in[i] == '\\')
      return in.substr(0, i);
  return "";
}



void writeOutputFile(const std::string & outputfile, const std::vector<char> &theData)
{
    std::ofstream output(outputfile.c_str());
    if (!output)
      throw("output file not created");

    std::vector<char>::const_iterator it= theData.begin();
    while (it != theData.end())
    {
      output.put(*it);
      ++it;
    }

}
