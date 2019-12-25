
#include <iostream>
#include <time.h>

using namespace std;

/*
switch���� ��ȥ�� ���
����ü : ���ӵ� ���ڿ� �̸��� �ο��� �� �ִ� ����̴�.
enum ����ü�� {}
����ü���� �̿��ؼ� ����ü Ÿ���� ������ ���� �����ϴ�.
��, ����ü ��ü�� ����� ���� ���� Ÿ���� �ɼ��� �ִ�.
����ü�� ���ڿ� �̸��� �ٿ��ִ� ����̴�.
*/

enum NUM {
	NUM_0,     //�ƹ��͵� �ο����� ���� ��� 0����
	NUM_1,     //1�� ���ʷ� ���� �ο��ȴ�.
	NUM_2,     //�߰����� ���ϴ� ���ڸ� ������ �ִ�.
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
	switch �� : ���� ������ üũ�ϴ� �б⹮
	switch(����) {
	case ��� :
	}
	�ڵ� �� �ȿ��� case break ������ ����.
	������ ���� ���� ����� ���̽��� �����Ѵ�.
	*/

	int iNumber;
	cout << "���ڸ� �Է��ϼ��� : ";
	cin >> iNumber;

	switch (iNumber)
	{
	case NUM_1: // iNumber ���� ���� ����Ǵ� case ������ �����ȴ�.
		cout << "�Էµ� ���ڴ� 1 �Դϴ�." << endl;
		break; //break�� ������ ����ġ���� ���� ������.
	case NUM_2:
		cout << "�Էµ� ���ڴ� 2 �Դϴ�." << endl;
		break; 
	case NUM_3:
		cout << "�Էµ� ���ڴ� 3 �Դϴ�." << endl;
		break; 
	case NUM_4:
		cout << "�Էµ� ���ڴ� 4 �Դϴ�." << endl;
		break; 
	case NUM_5:
		cout << "�Էµ� ���ڴ� 5 �Դϴ�." << endl;
		break;
	case NUM_6:
		cout << "�Էµ� ���ڴ� 6 �Դϴ�." << endl;
		break;
	default: //case�� �������� ���� ���ڰ� ���� ���
		cout << " 1���� 5������ ���ڰ� �ƴմϴ�." << endl;
		break;
	}

	// ����ü Ÿ���� ���� ����. ����ü Ÿ���� ������ ������ 4byte
	//����ü�� �̿��ؼ� ������ ������ ���� ǥ�� ������ ����ü��
	//������ ���̴�.
	NUM eNum;
	//Ÿ�� or������ ũ�⸦ �˾ƺ��� �Լ�
	cout << sizeof(NUM) << endl;
	//Ÿ��or������ type�� ���ڿ��� ��ȯ �ϴ� �Լ�
	cout << typeid(eNum).name() << endl;



	/*
	�ݺ��� : Ư�� �۾��� �ݺ��ؼ� �������ִ� ��� �̴�.
	���� : for , while , do while

	while(���ǽ�){}
	���ǽ��� üũ�ؼ� true �̸� �ڵ�� ���� �ڵ尡 �����ϰ�,
	�ٽ� ���ǽ��� üũ�Ѵ�. 
	���ǽ��� false�� �Ǹ� �ݺ����� �������´�.
	Ȥ�� �ݺ��� �ȿ��� break���� ������ �������´�.

	���� ���� ����(���ǽĿ� �׳� True�� �ִ°�)�� Ư�� ������ �Ǹ�
	break���� ������ �ؼ� ���α׷��� �����.
	*/

	iNumber = 0;
	while (iNumber < 10)
	{
		cout << iNumber << endl;
		++iNumber;

		if (iNumber == 4)//���� ���� ó�� ������ ���
			break;
	}

	//���������� ������ ����� ����

	//ȭ���� ������ �����ش�.
	system("cls");
	//���� ���̺� ����
	srand((unsigned int)time(0));

	int iPlayer, iComputer;

	while (true){
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3, ��" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ��� : " << endl;
		cin >> iPlayer;

		if (iPlayer<SRP_S || iPlayer > SRP_END) {
			cout << "�߸��� ���� �Է� �Ͽ����ϴ�." << endl;
			//�Ͻ�����
			system("pause");
			//continue : �ݺ����� ���������� �̵�
			continue;
		}
		else if (iPlayer == SRP_END)
			break;
		else {
			iComputer = (rand() % 3 + SRP_S);
			switch (iComputer)
			{
			case SRP_S:
				cout << "��ǻ�� : ����" << endl;
				break;
			case SRP_R:
				cout << "��ǻ�� : ����" << endl;
				break;
			case SRP_P:
				cout << "��ǻ�� : ��" << endl;
				break;
			}

			int iWin = iPlayer - iComputer;

			// if ���� ���
			/*if (iWin == 1 || iWin == -2)
				cout << "�¸�" << endl;
			else if (iWin == 0)
				cout << "���" << endl;
			else
				cout << "�й�" << endl;*/

			//switch ���� ���
			switch (iWin)
			{
			case 1:
			case -2:
				cout << "�¸�" << endl;
				break;
			case 0:
				cout << "���" << endl;
				break;
			default:
				cout << "�й�" << endl;
				break;
			}
			system("pause");
		}
	}

	/*
		for��
		for(�ʱⰪ; ���ǽ�; ������){}
		���ѷ����� ���� ���� for(;;) {} �� ����Ѵ�.
		�ʱⰪ�� for ���� ó�� ������ �� �� 1���� �����ϸ�,
		�� �Ŀ��� ���ǽ��� üũ�ϰ� true �̸�
		�ڵ�� ���� �ڵ� ���� ��
		�������� �����Ѵ�. �� �� ���ǽ��� �ٽ� üũ�Ѵ�.
		���� ���ǽ��� false�̰ų� break�� ������
		for���� ���� ������.5
		*/


	//������ 2�� ���

	for (int i = 1; i <= 9; ++i) {
		cout << "2 * " << i << " = " << 2*i << endl;
	}

	
	//for ���� 1~20������ ������ ¦���� ����ϴ� �ڵ�
	//������ �ȿ��� �ĵ� �����ִ�
	for (int i = 2; i <= 20; i += 2) { 
		cout << i << endl;
	}

	//1~100������ ���� �߿� 3�� 7�� ������� ���
	for (int i = 1; i <= 100; ++i) {
		if ((i % 3 == 0) && (i % 7 == 0)) {
			cout << i << endl;
		}
	}

	//��ø for�� : for���ȿ� for���� �ִ°�
	
	return 0;
}