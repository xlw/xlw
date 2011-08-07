
#include<vector>
#include<xlw/MyContainers.h>
#include<xlw/CellMatrix.h>

using namespace xlw;

std::vector<double> GetSTDVector(const MyArray &m);


struct student
{
	student(const std::string &name_,  double age_):name(name_),age(age_){}
	const std::string & getName()const{return name;}
	double getAge()const{return age;}

private:
	std::string name;
	double age;
};

student GetStudent(const CellMatrix &m);