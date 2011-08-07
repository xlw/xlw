
#ifndef CELLVALUE_HEADER_GUARD
#define CELLVALUE_HEADER_GUARD

#include <xlw/MyContainers.h>
#include <string>
#include <vector>

namespace xlw {

	    class CellValue
		{

		public:
			struct error_type
			{
				unsigned long value;
			};
			virtual bool IsAString() const=0;
			virtual bool IsAWstring() const=0;
			virtual bool IsANumber() const=0;
			virtual bool IsBoolean() const=0;
			virtual bool IsEmpty() const=0;
			virtual bool IsError() const=0;

			virtual const std::string & StringValue() const=0;
			virtual const std::wstring& WstringValue() const=0;
			virtual double NumericValue() const=0;
			virtual bool BooleanValue() const=0;
			virtual unsigned long ErrorValue() const=0;

			virtual operator std::string() const=0;
			virtual operator std::wstring() const=0;
			virtual operator bool() const=0;
			virtual operator double() const=0;
			virtual operator unsigned long() const=0;

			CellValue & operator=(const CellValue &value){return assign(value);}
			CellValue & operator=(const std::string &value){return assign(value);}
			CellValue & operator=(const std::wstring &value){return assign(value);}
			CellValue & operator=(double value){return assign(value);}
			CellValue & operator=(unsigned long  value){return assign(value);}
			CellValue & operator=(bool value){return assign(value);}
			CellValue & operator=(int value){return assign(value);}
			CellValue & operator=(error_type value){return assign(value);}

			virtual void clear()=0;

			virtual ~CellValue(){}

		private:
			CellValue & assign(const CellValue & data)
			{
				if(data.IsAString())
				{
					return assign(data.StringValue());
				}
				else if(data.IsAWstring())
				{
					return assign(data.WstringValue());
				}
				else if(data.IsANumber())
				{

					return assign(data.NumericValue());
				}
				else if(data.IsBoolean())
				{
					return assign(data.BooleanValue());
				}
				else if(data.IsEmpty())
				{
					clear();
					return *this;
				}
				else if(data.IsError())
				{
                    error_type e;
					e.value = data.ErrorValue();
					return assign(e);
				}
				return *this;
			}
			virtual CellValue & assign(const std::string&)=0;
			virtual CellValue & assign(const std::wstring&)=0;
			virtual CellValue & assign(double Number)=0;
			virtual CellValue & assign(unsigned long Code)=0; 
			virtual CellValue & assign(bool TrueFalse)=0;
			virtual CellValue & assign(int i)=0;
			virtual CellValue & assign(error_type)=0;

		};
}

#endif // CELLVALUE_HEADER_GUARD


