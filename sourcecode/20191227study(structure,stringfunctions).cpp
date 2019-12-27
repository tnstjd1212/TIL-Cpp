

#include <iostream>

using namespace std;


#define NAME_SIZE 32

/*
구조체 : 관련있는 변수들을 모아서 하나의 새로운 타입을 만들어주는 기능이다.
사용자정의 변수 타입이다.

struct 구조체명 {};

배열과 구조체의 공통점
1. 데이터 집합이다.
2. 연속된 메모리 블럭에 할당된다. 
(구조체 멤버들은 연속된 메모리 블럭으로 잡히게 된다.)

*/

struct _tagStudent {
	char strName[NAME_SIZE];
	int iNum;
	int iKorScore;
	int iMathScore;
	int iTotalScore;
	float fAvg;
};

int main() {
	_tagStudent tStudent = {}; //모든 멤버 0으로 초기화 가능
	//구조체 배열도 선언이 가능하다
	// _tagStudent tStudentArr[100] = {};
	//구조체 멤버로 잡근할 때는 . 을 이용한다.
	tStudent.iKorScore = 100;

	//문자열을 배열에 넣어줄 때에는 단순 대입으로는 불가능하다.
	//strcpy_s로 복사해 주어야 한다.
	//이 함수는 오른쪽에 있는 문자열을 왼쪽으로 복사해준다.
	strcpy_s(tStudent.strName, "박순성");
	
	//문자열의 끝은 항상 0(NULL)로 끝나야한다.
	//아니라면 출력할 때 문자열의 끝을 인식할 수 없기때문에 쓰레기 값으로 출력된다.
	
	//strcat_s() 문자열을 붙여주는 함수
	//오른쪽에 있는 문자열을 왼쪽 문자열뒤에 붙여준다,
	strcat_s(tStudent.strName, " SoonSung");
	
	//strlen() 문자열의 크기를 구해주는 함수
	cout << "이름 길이  : " << strlen(tStudent.strName) << endl;
	cout << "이름 : " << tStudent.strName << endl;

	//strcmp 함수는 두 문자열을 비교하여 같을 경우 0을 반환 하고 다를경우
	//0이 아닌 값을 반환한다.
	strcpy_s(tStudent.strName, "Soonsung");

	cout << "비교할 이름을 입력하세요 : ";
	char strCmp[NAME_SIZE] = {};
	cin >> strCmp;
	if (strcmp(tStudent.strName, strCmp)) {
		cout << "같지 않습니다" << endl;
	}
	else
		cout << "같습니다" << endl;
	
	
	
	
	
	return 0;
}