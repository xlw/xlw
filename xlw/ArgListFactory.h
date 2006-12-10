//
//
//                           ArgListFactory.h
//
//
#ifndef ARG_LIST_FACTORY_H
#define ARG_LIST_FACTORY_H
#ifdef _MSC_VER
#if _MSC_VER < 1250
#pragma warning(disable:4786)
#define VC6
#endif
#endif

#include <xlw/ArgList.h>
#include <map>
#include <string>

template<class T>
class ArgListFactory;

// friend rather than method to avoid bug in VC6.0 with static data in member template functions
template<class T>
ArgListFactory<T>& FactoryInstance()
{
	static ArgListFactory<T> object;
	return object;
}

template<typename T>
class ArgListFactory  
{
public:
#ifndef VC6
	friend ArgListFactory<T>& FactoryInstance<>();
#else
	friend ArgListFactory<T>& FactoryInstance();
#endif
	typedef T* (*CreateTFunction)(const ArgumentList& );
   void RegisterClass(std::string ClassId, CreateTFunction);
    T* CreateT(ArgumentList args);
	~ArgListFactory(){};

private:
    std::map<std::string, CreateTFunction> TheCreatorFunctions;
	std::string KnownTypes;
	ArgListFactory(){}
	ArgListFactory(const ArgListFactory&){}
    ArgListFactory& operator=(const ArgListFactory&){ return *this;}

};




template<typename T>
void ArgListFactory<T>::RegisterClass(std::string ClassId, CreateTFunction CreatorFunction)
{
	 MakeLowerCase(ClassId);
     TheCreatorFunctions.insert(std::pair<std::string,CreateTFunction>(ClassId,CreatorFunction));
	 KnownTypes+=" "+ClassId;
}

template<typename T>
T* ArgListFactory<T>::CreateT(ArgumentList args)
{
	
	std::string Id = args.GetStringArgumentValue("name");

	
    if  (TheCreatorFunctions.find(Id) == TheCreatorFunctions.end())
    {
		throw(Id+" is an unknown class. Known types are "+KnownTypes);
	}

	return (TheCreatorFunctions.find(Id)->second)(args);
}


// easy access function
template<class T>
T* GetFromFactory(const ArgumentList& args)
{
	return FactoryInstance<T>().CreateT(args);
}
#endif 
