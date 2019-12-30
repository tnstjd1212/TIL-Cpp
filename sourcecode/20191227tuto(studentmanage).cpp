// 구조체를 이용한 학생 관리
// 주소를 추가해 보자


#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10
#define ADDRESS_SIZE 64

struct _tagStudent
{
	char strName[NAME_SIZE];
	char strAddress[ADDRESS_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

enum MENU {
	MENU_INSERT = 1,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

//변수 선언
int iMenu; //메뉴 선택용
_tagStudent tStudentArr[STUDENT_MAX] = {};//학생 저장용
int iStudentCount = 0; //저장된 학생의 수
int iStudentNumber = 1; //학번 배정 용
char strSearchName[NAME_SIZE] = {};
int iSearchCount = 0;


int main()
{
	

	while (true) {
		system("cls");

		//menu
		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : " << endl;
		cin >> iMenu;

		//cin에 오른쪽 변수 타입과 맞지 않는 입력이 들어올 경우
		//에러가 발생한다. 이를 해결해보자.
		//에러 발생을 확인한다.
		if (cin.fail()) {
			//에러버퍼를 비워준다.
			cin.clear();
			//입력 버퍼에 \n을 삭제 한다.
			cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;
		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			iSearchCount = 0;
			cout << "==============학생 추가==============" << endl;

			//등록된 학생 수가 최대치일 경우 등록을 막는다.
			if (iStudentCount == STUDENT_MAX) {
				cout << "더 이상 등록할 수 없습니다." << endl;
				break;
			}

			//학생 정보를 추가 한다. 이름 점수 3가지는 입력 받고
			//학번 총점 평균은 계산한다.
			cout << "이름 : ";
			cin >> tStudentArr[iStudentCount].strName;
			for (int i = 0; i < iStudentCount; ++i) {
				if (strcmp(tStudentArr[i].strName, tStudentArr[iStudentCount].strName) == 0) {
					cout << "같은 이름이 있습니다." << endl;
					iSearchCount = 1;
					system("pause");
				}
			}
			if (iSearchCount == 1) {
				continue;
			}
			// cin은 spacebar도 입력의 끝으로 인식한다.
			//만약 enter까지를 입력의 끝으로 사용하고 싶을 경우
			//cin.getline을 사용해야 한다.
			//하지만 cin과 cin.getline을 동시에 사용할 경우
			//	cin.ignore(1024, '\n'); 입력 버퍼에 \n을 삭제 한다.
			//를 사용 하지 않을 경우 error가 발생할 수 있다.
			cin.ignore(1024, '\n');
			cout << "주소 : ";
			cin.getline (tStudentArr[iStudentCount].strAddress, streamsize (ADDRESS_SIZE));

			cout << "국어 : ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "영어 : ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "수학 : ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal = tStudentArr[iStudentCount].iKor + tStudentArr[iStudentCount].iEng + tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].fAvg = tStudentArr[iStudentCount].iTotal / 3.f;

			tStudentArr[iStudentCount].iNumber = iStudentNumber;

			++iStudentCount;
			++iStudentNumber;

			cout << "학생 추가 완료" << endl;
			break;
		case MENU_DELETE:
			iSearchCount = 0;
			system("cls");
			cout << "==============학생 삭제==============" << endl;
			cout << "삭제할 학생의 이름 : ";
			cin >> strSearchName;
			for (int i = 0; i < iStudentCount; ++i) {
				//학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					//삭제 하는 방법은 없다. 뒤에 있는 학생정보를 한칸씩 당기고 학생수(iStudentCount)를 1감소 시킨다.
					for (int j = i; j < iStudentCount; ++j) {
						if (j == (STUDENT_MAX - 1))
							break;
						tStudentArr[j] = tStudentArr[j + 1];
					}
					--iStudentCount;
					cout << "학생을 삭제 했습니다." << endl;
					break;
				}
				else
					++iSearchCount;
			}
			if (iSearchCount == iStudentCount)
				cout << "삭제하려는 학생이 없습니다." << endl;
			break;
		case MENU_SEARCH:
			system("cls");
			iSearchCount = 0;
			cout << "==============학생 탐색==============" << endl;
			cout << "탐색할 학생의 이름 : ";
			cin >> strSearchName;
			for (int i = 0; i < iStudentCount; ++i) {
				//학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "주소 : " << tStudentArr[i].strAddress << endl;
					cout << "학번 : " << tStudentArr[i].iNumber << endl;
					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "총점 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;
					break;
				}
				else
					++iSearchCount;
			}
			//학생을 못찾았을 경우
			if (iSearchCount == iStudentCount)
				cout << "찾으려는 학생이 없습니다." << endl;
			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "==============학생 출력==============" << endl;
			//등록된 학생 수 만큼 반복하면서 학생 정보를 출력한다.
			for (int i = 0; i < iStudentCount; ++i) {
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "주소 : " << tStudentArr[i].strAddress << endl;
				cout << "학번 : " << tStudentArr[i].iNumber << endl;
				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "총점 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].fAvg << endl << endl;

			}
			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}
		system("pause");

	}



	return 0;
}