//
//  
//                                  CellMatrix.h
//
//

#ifndef CELL_MATRIX_H
#define CELL_MATRIX_H

#include <string>
#include <vector>

class CellValue
{

public:
    bool IsAString() const;
    bool IsANumber() const;
  	bool IsBoolean() const;
	bool IsError() const;

    bool IsEmpty() const;


    CellValue(const std::string&);
    CellValue(double Number);
	CellValue(unsigned long Code, bool Error); //Error = true if you want an error code
	CellValue(bool TrueFalse);
	CellValue(const char* values);

    CellValue();

    const std::string& StringValue() const;
    double NumericValue() const;
	bool BooleanValue() const;
	unsigned long ErrorValue() const;

	std::string StringValueLowerCase() const;

	enum ValueType 
	{
		string, number, boolean, error, empty
	};

	operator std::string() const;
	operator bool() const;
	operator double() const;
	operator unsigned long() const;

	void clear();


private:
	ValueType Type;
  
    std::string ValueAsString;
    double ValueAsNumeric;
	bool ValueAsBool;
	unsigned long ValueAsErrorCode;


};

class CellMatrix
{
public:

    CellMatrix(unsigned long rows, unsigned long columns);
    
    const CellValue& operator()(unsigned long i, unsigned long j) const;
    CellValue& operator()(unsigned long i, unsigned long j);

    unsigned long RowsInStructure() const;
    unsigned long ColumnsInStructure() const;

	void PushBottom(const CellMatrix& newRows);



private:

	std::vector<std::vector<CellValue> > Cells;
    unsigned long Rows;
    unsigned long Columns;

};


CellMatrix MergeCellMatrices(const CellMatrix& Top, const CellMatrix& Bottom);



#endif
