
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

//���� ����
int iMenu;



int main() {

	// ĳ���� ����� : ��������



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