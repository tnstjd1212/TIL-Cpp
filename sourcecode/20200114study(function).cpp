

#include <iostream>

using namespace std;

	/*
	함수 : 기능을 만들어준다. 일종의 부품을 만드는 것이다.
	형태 : 반환타입 함수명 (인자) {}
	반환타입: 이 함수가 기능을 수행하고, 기능의 결과를 반환할 경우
	반환하는 데이터의 타입
	함수명 : 함수의 이름, 함수명은 가급적으로 함수의 역할을
	정확하게 표시해 주어야한다.
	인자 : 해당함수에 넘겨줄 값이 있을경우 인자를 활용한다.
	인자는 없을 수도 있다.
	*/


	/*
	함수의 디폴트인자 : 인자는 기본적으로 값을 넘겨받게 되어있다.
	하지만 인자에 디폴트 값을 대입해 두면 인자를 넘겨주지 않을 경우
	이 디폴트 값을 넘겨받은 값으로 설정하는 기능
	주의사항 : 디폴트 값은 가장 오른쪽부터 지정해주어야 한다.
			오버로딩된 함수에 활용할 경우 주의 해야한다.
	*/
int Sum(int a, int b = 0) //b가 디폴트 인자
{
	//return 키워드를 사용하여 반환할 값을 반환한다.
	return a + b;
}
void OutputText()
{
	cout << "Text" << endl;
}

void ChangeNum(int* iNum)
{
	*iNum = 10;
}

void ChangeNum(int iNum)
{
	iNum = 10;
}

/*
함수의 오버로딩 : 같은 이름의 함수 지만 인자나 기능이 다른 것
오버로딩의 조건 : 함수 이름이 무조건 같아야 한다
                인자의 개수나 타입이 달라야 한다.
*/


int main() 
{


	//함수를 호출할때는 함수명(인자로 넘겨줄 값);의 형태로 호출한다.
	cout << Sum(10, 23) << endl;
	OutputText();


	//단, 함수에서 인자는 값을 복사해 가는 것이다.
	//(Call by value)
	//따라서 함수내에서 인자의 값을 변경해도 함수 밖에는 영향을 미치지 않는다.
	
	int iNum = 1;
	ChangeNum(iNum);//Call by Value
	cout << iNum << endl;

	//하지만 인자로 포인터로 지정하면 주소를 넘겨주게 되고,
	//이를 역참조해서 사용할 경우 전역 변수가 아니더라도 함수 밖에 영향을 미칠수 있다.
	//(Call by Address)

	ChangeNum(&iNum);//Call by Address
	cout << iNum << endl;
	

	return 0;
}