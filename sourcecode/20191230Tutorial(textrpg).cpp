
#include <iostream>
#include <time.h>

using namespace std;

#define NAME_SIZE 32

enum MAIN_MANU {
	MM_MAP = 1,
	MM_STORE,
	MM_BAG,
	MM_EXIT
};

enum MAP_TYPE {
	MT_EASY = 1,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};
enum JOB {
	J_KNIGHT = 1,
	J_ARCHER,
	J_WIZARD
};

struct _tagCharacter {
	char strName[NAME_SIZE];
	char strJob[NAME_SIZE];
	int iJobcode;
	int iHP;
	int iMP;
	int iAttack;
	int iDeffend;
};

//변수 선언
int iMenu;



int main() {

	// 캐릭터 만들기 : 직업선택



	while (true) {
		system("cls");
		cout << "=================메인메뉴==================" << endl;
		cout << "1. 지도" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택 하세요 : ";
		cin >> iMenu;

		if (cin.fail()) {
			//에러버퍼를 비워준다.
			cin.clear();
			//입력 버퍼에 \n을 삭제 한다.
			cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
			continue;
		}
		if (iMenu == MM_EXIT)
			break;
		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "=================맵메뉴===================" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로" << endl;
				cout << "메뉴를 선택 하세요 : ";
				cin >> iMenu;

				if (cin.fail()) {
					//에러버퍼를 비워준다.
					cin.clear();
					//입력 버퍼에 \n을 삭제 한다.
					cin.ignore(1024, '\n'); //넉넉하게 1024 바이트를 검사하여 \n을 지워준다.
					continue;
				}
				if (iMenu == MT_BACK)
					break;
				switch (iMenu) {
				case MT_EASY:
					break;
				case MT_NORMAL:
					break;
				case MT_HARD:
					break;
				default:
					cout << "메뉴를 잘못 선택했습니다." << endl;
					break;
				}
			}
			break;
		case MM_STORE:
			break;
		case MM_BAG:
			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}