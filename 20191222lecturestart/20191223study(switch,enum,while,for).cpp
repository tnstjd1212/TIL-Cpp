
#include <iostream>
#include <time.h>

using namespace std;

/*
switch문과 영혼의 듀오
열거체 : 연속된 숫자에 이름을 부여할 수 있는 기능이다.
enum 열거체명 {}
열거체명을 이용해서 열거체 타입의 변수를 선언도 가능하다.
즉, 열거체 자체가 사용자 정의 변수 타입이 될수도 있다.
열거체는 숫자에 이름을 붙여주는 기능이다.
*/

enum NUM {
	NUM_0,     //아무것도 부여하지 않을 경우 0부터
	NUM_1,     //1씩 차례로 값이 부여된다.
	NUM_2,     //중간에도 원하는 숫자를 넣을수 있다.
	NUM_3,
	NUM_4,
	NUM_5
};

#define NUM_6 6

enum SRP
{
	SRP_S = 1,
	SRP_R,
	SRP_P,
	SRP_END
};


int main() {

	/*
	switch 문 : 값이 뭔지를 체크하는 분기문
	switch(변수) {
	case 상수 :
	}
	코드 블럭 안에는 case break 구문이 들어간다.
	변수의 값이 같은 상수의 케이스를 실행한다.
	*/

	int iNumber;
	cout << "숫자를 입력하세요 : ";
	cin >> iNumber;

	switch (iNumber)
	{
	case NUM_1: // iNumber 값에 따라 실행되는 case 구문이 결정된다.
		cout << "입력된 숫자는 1 입니다." << endl;
		break; //break를 만나면 스위치문을 빠져 나간다.
	case NUM_2:
		cout << "입력된 숫자는 2 입니다." << endl;
		break; 
	case NUM_3:
		cout << "입력된 숫자는 3 입니다." << endl;
		break; 
	case NUM_4:
		cout << "입력된 숫자는 4 입니다." << endl;
		break; 
	case NUM_5:
		cout << "입력된 숫자는 5 입니다." << endl;
		break;
	case NUM_6:
		cout << "입력된 숫자는 6 입니다." << endl;
		break;
	default: //case로 지정되지 않은 숫자가 들어올 경우
		cout << " 1에서 5사이의 숫자가 아닙니다." << endl;
		break;
	}

	// 열거체 타입의 변수 선언. 열거체 타입의 변수는 무조건 4byte
	//열거체를 이용해서 선언한 변수는 값의 표현 범위가 열거체에
	//나열된 값이다.
	NUM eNum;
	//타입 or변수의 크기를 알아보는 함수
	cout << sizeof(NUM) << endl;
	//타입or변수의 type을 문자열로 반환 하는 함수
	cout << typeid(eNum).name() << endl;



	/*
	반복문 : 특정 작업을 반복해서 수행해주는 기능 이다.
	종류 : for , while , do while

	while(조건식){}
	조건식을 체크해서 true 이면 코드블럭 안의 코드가 동작하고,
	다시 조건식을 체크한다. 
	조건식이 false가 되면 반복문을 빠져나온다.
	혹은 반복문 안에서 break문을 만나면 빠져나온다.

	보통 무한 루프(조건식에 그냥 True를 넣는것)에 특정 조건이 되면
	break문을 만나게 해서 프로그램을 만든다.
	*/

	iNumber = 0;
	while (iNumber < 10)
	{
		cout << iNumber << endl;
		++iNumber;

		if (iNumber == 4)//보통 예외 처리 용으로 사용
			break;
	}

	//가위바위보 게임을 만들어 보자

	//화면을 깨끗이 지워준다.
	system("cls");
	//난수 테이블 생성
	srand((unsigned int)time(0));

	int iPlayer, iComputer;

	while (true){
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3, 보" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요 : " << endl;
		cin >> iPlayer;

		if (iPlayer<SRP_S || iPlayer > SRP_END) {
			cout << "잘못된 값을 입력 하였습니다." << endl;
			//일시정지
			system("pause");
			//continue : 반복문의 시작점으로 이동
			continue;
		}
		else if (iPlayer == SRP_END)
			break;
		else {
			iComputer = (rand() % 3 + SRP_S);
			switch (iComputer)
			{
			case SRP_S:
				cout << "컴퓨터 : 가위" << endl;
				break;
			case SRP_R:
				cout << "컴퓨터 : 비위" << endl;
				break;
			case SRP_P:
				cout << "컴퓨터 : 보" << endl;
				break;
			}

			int iWin = iPlayer - iComputer;

			// if 문일 경우
			/*if (iWin == 1 || iWin == -2)
				cout << "승리" << endl;
			else if (iWin == 0)
				cout << "비김" << endl;
			else
				cout << "패배" << endl;*/

			//switch 문일 경우
			switch (iWin)
			{
			case 1:
			case -2:
				cout << "승리" << endl;
				break;
			case 0:
				cout << "비김" << endl;
				break;
			default:
				cout << "패배" << endl;
				break;
			}
			system("pause");
		}
	}

	/*
		for문
		for(초기값; 조건식; 증감값){}
		무한루프를 돌릴 때는 for(;;) {} 을 사용한다.
		초기값은 for 문에 처음 진입할 때 딱 1번만 동작하며,
		그 후에는 조건식을 체크하고 true 이면
		코드블럭 안의 코드 동작 후
		증감값이 동작한다. 그 후 조건식을 다시 체크한다.
		만약 조건식이 false이거나 break를 만나면
		for문을 빠져 나간다.5
		*/


	//구구단 2단 출력

	for (int i = 1; i <= 9; ++i) {
		cout << "2 * " << i << " = " << 2*i << endl;
	}

	
	//for 으로 1~20사이의 숫자중 짝수만 출력하는 코드
	//증감값 안에는 식도 들어갈수있다
	for (int i = 2; i <= 20; i += 2) { 
		cout << i << endl;
	}

	//1~100사이의 숫자 중에 3과 7의 공배수만 출력
	for (int i = 1; i <= 100; ++i) {
		if ((i % 3 == 0) && (i % 7 == 0)) {
			cout << i << endl;
		}
	}

	//중첩 for문 : for문안에 for문이 있는것
	
	return 0;
}