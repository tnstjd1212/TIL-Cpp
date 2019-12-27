// ����ü�� �̿��� �л� ����
// �ּҸ� �߰��� ����


#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 10


struct _tagStudent
{
	char strName[NAME_SIZE];
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

//���� ����
int iMenu; //�޴� ���ÿ�
_tagStudent tStudentArr[STUDENT_MAX] = {};//�л� �����
int iStudentCount = 0; //����� �л��� ��
int iStudentNumber = 1; //�й� ���� ��



int main()
{
	

	while (true) {
		system("cls");

		//menu
		cout << "1. �л����" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л�Ž��" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : " << endl;
		cin >> iMenu;

		//cin�� ������ ���� Ÿ�԰� ���� �ʴ� �Է��� ���� ���
		//������ �߻��Ѵ�. �̸� �ذ��غ���.
		//���� �߻��� Ȯ���Ѵ�.
		if (cin.fail()) {
			//�������۸� ����ش�.
			cin.clear();
			//�Է� ���ۿ� \n�� ���� �Ѵ�.
			cin.ignore(1024, '\n'); //�˳��ϰ� 1024 ����Ʈ�� �˻��Ͽ� \n�� �����ش�.
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;
		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "==============�л� �߰�==============" << endl;

			//��ϵ� �л� ���� �ִ�ġ�� ��� ����� ���´�.
			if (iStudentCount == STUDENT_MAX)
				break;

			//�л� ������ �߰� �Ѵ�. �̸� ���� 3������ �Է� �ް�
			//�й� ���� ����� ����Ѵ�.
			cout << "�̸� : ";
			cin >> tStudentArr[iStudentCount].strName;
			// cin�� spacebar�� �Է��� ������ �ν��Ѵ�.
			//���� enter������ �Է��� ������ ����ϰ� ���� ���
			//cin.getline�� ����ؾ� �Ѵ�.
			//������ cin�� cin.getline�� ���ÿ� ����� ���
			//	cin.ignore(1024, '\n'); �Է� ���ۿ� \n�� ���� �Ѵ�.
			//�� ��� ���� ���� ��� error�� �߻��� �� �ִ�.

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iEng;

			cout << "���� : ";
			cin >> tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].iTotal = tStudentArr[iStudentCount].iKor + tStudentArr[iStudentCount].iEng + tStudentArr[iStudentCount].iMath;

			tStudentArr[iStudentCount].fAvg = tStudentArr[iStudentCount].iTotal / 3.f;

			++iStudentCount;

			tStudentArr[iStudentCount].iNumber = iStudentNumber;

			cout << "�л� �߰� �Ϸ�" << endl;
			break;
		case MENU_DELETE:
			break;
		case MENU_SEARCH:
			break;
		case MENU_OUTPUT:
			system("cls");
			cout << "==============�л� ���==============" << endl;
			//��ϵ� �л� �� ��ŭ �ݺ��ϸ鼭 �л� ������ ����Ѵ�.
			for (int i = 0; i < iStudentCount; ++i) {
				cout << "�̸� : " << tStudentArr[i].strName << endl;
				cout << "�й� : " << tStudentArr[i].iNumber << endl;
				cout << "���� : " << tStudentArr[i].iKor << endl;
				cout << "���� : " << tStudentArr[i].iEng << endl;
				cout << "���� : " << tStudentArr[i].iMath << endl;
				cout << "���� : " << tStudentArr[i].iTotal << endl;
				cout << "��� : " << tStudentArr[i].fAvg << endl << endl;

			}
			break;
		default:
			cout << "�޴��� �߸� �����߽��ϴ�." << endl;
			break;
		}
		system("pause");

	}



	return 0;
}