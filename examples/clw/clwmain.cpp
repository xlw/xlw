#include <clw/FileConverter.h>
#include <fstream>
#include <iostream>
#include <clw/Dispatcher.h>
using namespace std;
using namespace xlw;
using namespace clw;

void  addToOutput(ofstream& output, CellValue cell)
{
  if (cell.IsEmpty())
    output << " , ";
  else
  {
    output << " , ";
    if (cell.IsAString())
      output << cell.StringValue();
    else
      if (cell.IsANumber())
        output << static_cast<double>(cell);
      else
        if (cell.IsBoolean())
          output << static_cast<bool>(cell);
        else
          output << "other type";
  }

}


int main(int argc, char *argv[])
{
  try
  {

    if (argc <3 || argc > 3)
      throw("usage is inputfile outputfile ");
    std::string inputfile(argv[1]);
    std::string outputfile(argv[2]);

    ifstream input(inputfile.c_str());
    if (!input)
      throw("input file not found :"+inputfile+"\n");

    std::vector<char> inputvector;

    char c;
    while (input.get(c))
    {
      int i = static_cast<int>(c);
      if (i<32 && c!='\n')
        c=' '; // strip out special characters
      inputvector.push_back(c);
    }

    unsigned long gapSize=2UL;
    std::vector<ArgumentList> 
      functions(FileConversion(inputvector,gapSize));

    unsigned long failures =0;
    unsigned long successes=0;

    CellMatrix totalRes(1,4);

    for (unsigned long j=0; j < functions.size(); ++j)
    {
      CellMatrix results(2,2);
      results(1,0) = functions[j].GetStructureName();
      try
      {
        CellMatrix res(Dispatcher::Instance().CallFunction(functions[j]));
        results.PushBottom( res);
        ++successes;
      }
      catch(const char* c)
      {
        results(1,1) = CellValue(std::string(c));
        ++failures;
      }
      catch (std::string s)
      {
        results(1,1) = CellValue(s);
        ++failures;
      }
      catch (...)
      {
        results(1,1) = CellValue("exception thrown");
        ++failures;
      }

      totalRes.PushBottom(results);

    }

    totalRes(0,0) = std::string("Successes");
    totalRes(0,1) = CellValue(successes);

    totalRes(0,2) = std::string("Failures");
    totalRes(0,3) = CellValue(failures);

      
    ofstream output(outputfile.c_str());
    
    if (!output)
        throw("Couldn't open file for output.");

    for (unsigned long i=0; i < totalRes.RowsInStructure(); ++i)
    {
      for (unsigned long j=0; j < totalRes.ColumnsInStructure(); ++j)
        addToOutput(output, totalRes(i,j));

      output.put('\n');
    }

      
  }
  catch (const char *c)
  {
    std::cout << "***ERROR***\n" << c << "\n***ERROR***\n";
  }
  catch (std::string c)
  {
    std::cout << "***ERROR***\n" << c << "\n***ERROR***\n";
  }
  catch (...)
  {
    std::cout << "***ERROR***\n" << "exception thrown" << "\n***ERROR***\n";
  }

  return 0;
}

