//
//
//                    FileConverter.h
//
//

#ifndef FILE_CONVERTER_H
#define FILE_CONVERTER_H

#include <vector>
#include <xlw/ArgList.h>

namespace clw
{
  std::vector<xlw::ArgumentList> FileConversion(const std::vector<char>& inputFile,
    unsigned long gapSize);
}

#endif
