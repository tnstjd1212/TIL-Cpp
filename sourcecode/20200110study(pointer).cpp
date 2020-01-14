

#include <iostream>

using namespace std;

struct _tagStudent
{
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() 
{
	/*
	포인터 : 일반 변수는 값을 저장하지만, 포인터 변수는 메모리주소를 저장한다.
	모든 변수 타입은 포인터 타입을 선언할 수 있다. 
	포인터는 메모리 주소를 담아 놓는 변수이기 때문에  x86에서는 크기가 4byte가 나오고,
	x64는 8byte가 나온다.

	포인터는 가지고 있는 주소에 접근하여 값을 제어할 수 있다.
	형태 : 변수타입 *변수명;
	*/
	int iNum = 100;
	//변수 앞에 &를 붙여주면 해당 변수의 메모리 주소가 된다.
	int* pNum = &iNum;
	cout << *pNum << endl;
	*pNum = 1234;
	cout << iNum << endl;

	//배열명은 배열의 시작주소
	int iArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 ,0 };
	int* pArray = iArray;
	//pArray로 iArray 제어가능

	/*
	포인터 연산 : +- 연산을 제공한다. ++, -- 도 사용가능한데
	단순히 메모리 주소값이 1증가하는 것이 아닌 포인터 타입의
	변수 타입의 크기만큼 증가 한다.
	즉, 포인터에 숫자를 더해서 배열의 요소에 접근할 수 있다.
	*/

	cout << *(pArray + 2) << endl;
	cout << *(pArray + 6) << endl;

	const char *pText = "테스트"; 
	//상수문자열을 저장하고 메모리 주소를 가져오는것
	//이름을 바꾸기 위해서는 배열을 선언해서 이름을 저장해야 함

	cout << pText << endl;
	cout << (int*)pText << endl;

	//하지만 주소를 바꾸는 것은 가능하다.
	pText = "asd";

	cout << pText << endl;
	cout << (int*)pText << endl;
	//같은 상수 문자열 일 경우 주소가 바뀌지 않는다.
	pText = "asd";

	cout << pText << endl;
	cout << (int*)pText << endl;

	//이것은 배열을 선언하고 값을 집어넣는 것이기 때문에 주소가 다르다.
	char str[4] = "asd";

	cout << str << endl;
	cout << (int*)str << endl;

	_tagStudent tStudent = {};

	tStudent.iKor = 100;

	cout << tStudent.iKor << endl;


	_tagStudent* pStudent = &tStudent;

	//*연산자 보다 .연산자가 우선순위가 높으므로
	//포인터로 구조체 멤버에 접근할 경우 ()를 꼭 사용해야 한다.

	(*pStudent).iKor = 50;

	cout << tStudent.iKor << endl;

	//혹은 메모리주소-> 를 통해 멤버에 접근할 수 있다.

	pStudent->iKor = 80;

	cout << tStudent.iKor << endl;

	//void : 타입이 없다. void의 포인터타입을 활용할 수 있다.
	//void* 변수를 선언할 경우 어떤 타입의 메모리 주소든
	//모두 저장가능하다. 단, 역참조를 할 수 없다.
	//즉, 메모리주소를 저장하는 버퍼로 활용 해야한다.


	//이중포인터 : 포인터의 포인터이다.
	//포인터의 메모리 주소를 저장한다.

	int iNum1 = 111;
	int* pNum1 = &iNum1;
	int** ppNum = &pNum1; //**을 두개 붙이면 이중 포인터가 만들어진다.

	cout << ppNum << "=" << &pNum1 << endl; //int 이중 포인터 변수
	cout << *ppNum << "=" << pNum1 << endl; //int 포인터 변수
	cout << **ppNum << "=" << *pNum1 << endl; //int 변수



	return 0;
}