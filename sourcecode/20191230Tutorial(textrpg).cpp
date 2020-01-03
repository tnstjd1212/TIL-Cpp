
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
	J_END   // END���� �ڵ忡 �߰������ν� ������ ���߿� �߰� �ص� �ٸ� �ڵ带 ������ �ʿ� ����
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

//���� ����
int iMenu;
int iJob = J_NONE;



int main() {

	srand((unsigned int)time(0));

	// ���ӽ��� �� �÷��̾� ���� ����
	_tagPlayer tPlayer = {};
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	cout << "�̸� : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	while (iJob == J_NONE)
	{
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ��� : ";
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
		strcpy_s(tPlayer.strJob, "���");
		tPlayer.iArmor = 5;
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iHPMax = 75;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 25;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_ARCHER:
		strcpy_s(tPlayer.strJob, "�ü�");
		tPlayer.iArmor = 3;
		tPlayer.iAttackMin = 7;
		tPlayer.iAttackMax = 13;
		tPlayer.iHPMax = 60;
		tPlayer.iHP = tPlayer.iHPMax;
		tPlayer.iMPMax = 35;
		tPlayer.iMP = tPlayer.iMPMax;
		break;
	case J_WIZARD:
		strcpy_s(tPlayer.strJob, "������");
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
		cout << "=================���θ޴�==================" << endl;
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� ���� �ϼ��� : ";
		cin >> iMenu;

		if (cin.fail()) {
			//�������۸� ����ش�.
			cin.clear();
			//�Է� ���ۿ� \n�� ���� �Ѵ�.
			cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
			continue;
		}
		if (iMenu == MM_EXIT)
			break;
		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "=================�ʸ޴�===================" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷ�" << endl;
				cout << "�޴��� ���� �ϼ��� : ";
				cin >> iMenu;

				if (cin.fail()) {
					//�������۸� ����ش�.
					cin.clear();
					//�Է� ���ۿ� \n�� ���� �Ѵ�.
					cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
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
					cout << "�޴��� �߸� �����߽��ϴ�." << endl;
					break;
				}
			}
			break;
		case MM_STORE:
			break;
		case MM_BAG:
			break;
		default:
			cout << "�޴��� �߸� �����߽��ϴ�." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}