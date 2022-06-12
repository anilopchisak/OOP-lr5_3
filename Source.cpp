#include <iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		printf("Base()\n");
	}
	Base(Base *obj) //указатель на объект Base 
	{
		printf("Base(Base *obj)\n");
	}
	Base(Base &obj) //ссылка на объект Base						 
	{															
		printf("Base(Base &obj)\n");	
	}									
	virtual ~Base()												
	{																							
		printf("~Base()\n");									
	}
	void OK()
	{
		printf("OK\n");
	}
};
class Desc : public Base
{
public:
	Desc()
	{
		printf("Desc()\n");
	}
	Desc(Desc *obj)
	{
		printf("Desc(Desc *obj)\n");
	}
	Desc(Desc &obj)
	{
		printf("Desc(Desc &obj)\n");
	}
	~Desc()
	{
		printf("~Desc()\n");
	}
	void OK2()
	{
		printf("OK2\n");
	}
};

//создается новый объект, переданный объект копируется в него, новый объект независим от первого, вызывается деструктор
void func1(Base  obj) 
{ 
	printf("void func1(Base  obj)\n"); 
	obj.OK(); 
	if (dynamic_cast<Desc*>(&obj) != nullptr) dynamic_cast<Desc*>(&obj)->OK2();
}

//локальный объект не создается, необходимо если нужно чтобы менялся передаваемый объект
void func2(Base* obj) 
{ 
	printf("void func2(Base*  obj)\n"); 
	obj->OK();
	if (dynamic_cast<Desc*>(obj) != nullptr) dynamic_cast<Desc*>(obj)->OK2();
} 

//локальный объект не создается, необходимо если передается объект, который может меняться внутри функции, экономит время и память
void func3(Base& obj) 
{ 
	printf("void func3(Base&  obj)\n"); 
	obj.OK();
	if (dynamic_cast<Desc*>(&obj) != nullptr) dynamic_cast<Desc*>(&obj)->OK2();
} 
//можно передавать по константной ссылке в случае если объект не будет меняться внутри функции

Base f1() //занимает много памяти тк вызывается 2 конструктора и 2 деструктора
{ 
	printf("Base f1()\n"); 
	Base base;
	return base;
}
Base* f2() //за кодером остается ответственность удалить этот объект, иначе утечка памяти
{ 
	printf("Base* f2()\n"); 
	Base* base = new Base();
	return base;
}
Base& f3() 
{ 
	printf("Base& f3()\n"); 
	Base base;
	return base; //созданный в функции объект удаляется, передается пустота
}
Base f4() //занимает много памяти тк вызывается 2 конструктора и 2 деструктора
{
	printf("Base f4()\n");
	Base* base = new Base();
	return *base;
}



int main()
{
	printf("passing an object to a function\n\n");

	Base* base = new Base(); printf("\n");
	func1(base); 
	func2(base); 
	func3(*base); printf("\n\n");

	{
		Base base1; printf("\n");
		func1(base1);
		func2(&base1);
		func3(base1); printf("\n");
	} printf("\n\n");

	{
		Base base2(base); printf("\n"); //создается указатель на объект
		func1(base2); 
		func2(&base2);
		func3(base2); printf("\n");
	} printf("\n\n");

	{
		Base base3(*base); printf("\n"); //создается ссылка на объект
		func1(base3);
		func2(&base3);
		func3(base3); printf("\n");
	} printf("\n\n");
	

	Desc* desc = new Desc(); printf("\n");
	func1(desc);
	func2(desc);
	func3(*desc); printf("\n\n");

	{
		Desc desc1; printf("\n");
		func1(desc1);
		func2(&desc1);
		func3(desc1); printf("\n");
	} printf("\n\n");

	{
		Desc desc2(desc); printf("\n");
		func1(desc2);
		func2(&desc2);
		func3(desc2); printf("\n");
	} printf("\n\n");

	{
		Desc desc3(*desc); printf("\n");
		func1(desc3);
		func2(&desc3);
		func3(desc3); printf("\n");
	} printf("\n\n");
	
	delete desc; printf("\n\n");
	delete base; printf("\n\n");

	printf("returning from the function\n\n");

	Base b1;		
	b1 = f1(); printf("\n");

	Base* b2 = f2(); delete b2; printf("\n"); 

	Base b3; b3 = f3(); printf("\n"); // в объект передается пустота
	//Base b3 = f3(); printf("\n"); //в этом случае объект b3 создается после того как в него передали пустоту

	Base b4; b4 = f4(); printf("\n");

	return 0;
}
