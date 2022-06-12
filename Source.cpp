#include <iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		printf("Base()\n");
	}
	Base(Base *obj) //��������� �� ������ Base 
	{
		printf("Base(Base *obj)\n");
	}
	Base(Base &obj) //������ �� ������ Base						 
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

//��������� ����� ������, ���������� ������ ���������� � ����, ����� ������ ��������� �� �������, ���������� ����������
void func1(Base  obj) 
{ 
	printf("void func1(Base  obj)\n"); 
	obj.OK(); 
	if (dynamic_cast<Desc*>(&obj) != nullptr) dynamic_cast<Desc*>(&obj)->OK2();
}

//��������� ������ �� ���������, ���������� ���� ����� ����� ������� ������������ ������
void func2(Base* obj) 
{ 
	printf("void func2(Base*  obj)\n"); 
	obj->OK();
	if (dynamic_cast<Desc*>(obj) != nullptr) dynamic_cast<Desc*>(obj)->OK2();
} 

//��������� ������ �� ���������, ���������� ���� ���������� ������, ������� ����� �������� ������ �������, �������� ����� � ������
void func3(Base& obj) 
{ 
	printf("void func3(Base&  obj)\n"); 
	obj.OK();
	if (dynamic_cast<Desc*>(&obj) != nullptr) dynamic_cast<Desc*>(&obj)->OK2();
} 
//����� ���������� �� ����������� ������ � ������ ���� ������ �� ����� �������� ������ �������

Base f1() //�������� ����� ������ �� ���������� 2 ������������ � 2 �����������
{ 
	printf("Base f1()\n"); 
	Base base;
	return base;
}
Base* f2() //�� ������� �������� ��������������� ������� ���� ������, ����� ������ ������
{ 
	printf("Base* f2()\n"); 
	Base* base = new Base();
	return base;
}
Base& f3() 
{ 
	printf("Base& f3()\n"); 
	Base base;
	return base; //��������� � ������� ������ ���������, ���������� �������
}
Base f4() //�������� ����� ������ �� ���������� 2 ������������ � 2 �����������
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
		Base base2(base); printf("\n"); //��������� ��������� �� ������
		func1(base2); 
		func2(&base2);
		func3(base2); printf("\n");
	} printf("\n\n");

	{
		Base base3(*base); printf("\n"); //��������� ������ �� ������
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

	Base b3; b3 = f3(); printf("\n"); // � ������ ���������� �������
	//Base b3 = f3(); printf("\n"); //� ���� ������ ������ b3 ��������� ����� ���� ��� � ���� �������� �������

	Base b4; b4 = f4(); printf("\n");

	return 0;
}
