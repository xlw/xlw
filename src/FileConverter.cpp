//
//
//            FileConverter.cpp
//
//
#include <clw/FileConverter.h>
#include <xlw/CellMatrix.h>
#include <xlw/ArgList.h>
#include <cstdlib>
using namespace xlw;

namespace
{
  CellValue CellFromString(const std::string value)
  {
    std::string::const_iterator it = value.begin();

    bool nonnumber = false;
    bool decpointfound = false;

    while (it != value.end())
    {
      if (*it != '.' || decpointfound)
        if ( *it < '0' || *it > '9' )
          nonnumber = true;

      if (*it == '.')
        decpointfound = true;

      ++it;
    }


    if (nonnumber)
      return CellValue(value);
    else
      return CellValue(atof(value.c_str()));

  }
}

namespace clw
{
  std::vector<ArgumentList> FileConversion(const std::vector<char>& inputFile,
    unsigned long gapSize)
  {
    std::vector<char>::const_iterator it = inputFile.begin();


    std::vector<std::vector<std::string> > Cells;
    Cells.resize(1);
    std::string currentCell;

    while (it != inputFile.end())
    {
      char c = *it;
      ++it;

      switch (c)
      {
      case  ',' : // end of cell but not line
        { 
          (*Cells.rbegin()).push_back(currentCell);
          currentCell = "";
          break;
        } 
      case '\n' : // new line so move on;
        {
          Cells.push_back(std::vector<std::string>());
          if (currentCell != "") 
          {
            (*Cells.rbegin()).push_back(currentCell);
            currentCell = "";
          }
          break;
        }
      default:
        {
          currentCell.push_back(c);
        }
      }

    }


    std::vector<std::vector<CellValue> > cellValues(Cells.size());
    for (unsigned long i=0; i < Cells.size(); ++i)
    {
      
      cellValues[i].reserve(Cells[i].size());
      for (unsigned long j=0; j < Cells[i].size(); ++j)
        cellValues[i].push_back( CellFromString(Cells[i][j]));
    }


    unsigned long rows =cellValues.size();
    std::vector<CellMatrix> cellMatrices;

    unsigned long currentRow=0;


    // now divide into CellMatrices

    while (currentRow < rows)
    {
      while( currentRow < rows && cellValues[currentRow].size() == 0) 
        ++currentRow;

      unsigned long startRow = currentRow;


      if (currentRow < rows)
      {
        unsigned long firstEmpty;
        bool endNotFound = true;  
        do
        {
          while( currentRow < rows && cellValues[currentRow].size() != 0) 
            ++currentRow;

          if (currentRow < rows)
          {
            firstEmpty = currentRow;

            while( currentRow < rows && cellValues[currentRow].size() == 0) 
              ++currentRow;

            if (currentRow == rows || (currentRow - firstEmpty) >=gapSize)
              endNotFound = false;

          }
          else
            endNotFound=false;
        }
        while (endNotFound);

        if (currentRow == rows)
          firstEmpty = rows;

        if (startRow < firstEmpty)
        {
          unsigned long maxColSize=0;

          for (unsigned long j=startRow; j < firstEmpty; ++j)
            maxColSize = std::max<unsigned long>(maxColSize, cellValues.size());

          CellMatrix thisOne(firstEmpty-startRow,maxColSize);

          for (unsigned long i=startRow; i < firstEmpty; ++i)
            for (unsigned long j=0; j < cellValues[i].size(); ++j)
              thisOne(i-startRow,j) = cellValues[i][j];

          cellMatrices.push_back(thisOne);

        }
      }
    }

    std::vector<ArgumentList> args;
    for (unsigned long i=0; i < cellMatrices.size(); ++i)
      args.push_back(ArgumentList(cellMatrices[i],"clw"));

    return args;


  }




}
