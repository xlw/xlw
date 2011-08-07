
#include"type_conversions.h"

std::vector<double> GetSTDVector(const MyArray &m)
{
	std::vector<double> v;
	for(size_t i(0); i< m.size(); ++i)
	{
		v.push_back(m[i]);
	}
	return v;
}


student GetStudent(const CellMatrix &m)
{
	if(m.ColumnsInStructure()!=1)
	{
		throw "Student must have 1 column";
	}
	if(m.RowsInStructure()!=2)
	{
		throw "Student must a name followed by an age";
	}
	if(!m(0,0).IsAString() && !m(0,0).IsAWstring())
	{
		throw "Expected name of student in first cell";
	}
	if(!m(1,0).IsANumber())
	{
		throw "Expected agent of student in second cell";
	}
	return student(m(0,0).StringValue(),m(1,0).NumericValue());

}
