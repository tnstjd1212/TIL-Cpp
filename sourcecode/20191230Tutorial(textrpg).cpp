
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
	J_NONE,
	J_KNIGHT,
	J_ARCHER,
	J_WIZARD,
	J_END   // END값을 코드에 추가함으로써 직업을 나중에 추가 해도 다른 코드를 변경할 필요 없음
};

struct _tagPlayer {
	int iExp;
	int iLevel;
	char strName[NAME_SIZE];
	JOB eJob;
	char strJob[NAME_SIZE];
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iAttackMin;
	int iAttackMax;
	int iArmor;
};

struct _tagMonster
{
	char strName[NAME_SIZE];
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iGetExp;
	int iGetGold;
	int iLevel;
	int iAttackMin;
	int iAttackMax;
	int iArmor;
};

//변수 선언
int iMenu;
int iJob = J_NONE;



int main() {

	srand((unsigned int)time(0));

	// 게임시작 시 플레이어 정보 설정
	_tagPlayer tPlayer = {};
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	cout << "이름 : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요 : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iJob <= J_NONE || iJob >= J_END)
			iJob - J_NONE;
	}

	tPlayer.eJob = (JOB)iJob;
	switch (tPlayer.eJob)
	{
	case J_KNIGHT:
		strcpy_s(tPlayer.strJob, "기사");
		tPlayer.iArmor = 5;
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iHPMax = 75;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 25;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(tPlayer.strJob, "궁수");
		tPlayer.iArmor = 3;
		tPlayer.iAttackMin = 7;
		tPlayer.iAttackMax = 13;
		tPlayer.iHPMax = 60;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 35;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(tPlayer.strJob, "마법사");
		tPlayer.iArmor = 1;
		tPlayer.iAttackMin = 7;
		tPlayer.iAttackMax = 17;
		tPlayer.iHPMax = 55;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 55;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	}



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