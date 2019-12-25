// ���� ����



#include <iostream>
#include <time.h>
#include <conio.h>
//console input output

using namespace std;

int main() {

	srand((unsigned int)time(0));

	int iNum[16] = {};

	for (int i = 0; i < 15; ++i) {
		iNum[i] = i + 1;
	}
	//���� ������ ĭ�� ����
	//(������ INT_MAX ��� Ư���� ���� ���)
	//INT_MAX : �̹� ���� �Ǿ� �ִ� ��
	//          int�� �ִ�
	iNum[15] = INT_MAX;

	/*������ �����ϰ� 1~24 ������ ���ڸ� 
	�����ش�. (�ε��� 0~23)
	*/
	int iTemp, idx1, idx2;
	int ientrp = 0;
	do {
		for (int i = 0; i < 100; ++i) { //shuffle
			idx1 = rand() % 15;
			idx2 = rand() % 15;

			iTemp = iNum[idx1];
			iNum[idx1] = iNum[idx2];
			iNum[idx2] = iTemp;
		}
		
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < i; j++) {
				if (iNum[i] < iNum[j])
					++ientrp;
			}
		}
	} while (ientrp % 2); // ���������� ¦���� �� ���� �ٽ� ����

	char cinput;
	int iStar = 15;// ���� ������ġ

	while (true) {
		system("cls");
		cout << ientrp << endl;
		for (int i = 0; i < 4; ++i) {           // 5*5 ��� ó�� ���
			for (int j = 0; j < 4; ++j) {
				if (iNum[j + i * 4] == INT_MAX) {
					cout << "*\t";
					iStar = j + i * 4;  //���� ��ġ üũ
				}
				else {
					cout << iNum[j + i * 4] << "\t";
				}
			}
			cout << endl;
		}


		//������ ���߾����� üũ
		bool bWin = true; // �ϴ� �� �¾Ҵٰ� ����
		for (int i = 0; i < 15; ++i)
		{
			if (iNum[i] != (i + 1)) { // �ϳ��� Ʋ�ȴٸ� false
				bWin = false;
				break;
			}
		}
		if (bWin) { // ��� �¾Ҵٸ� ����
			break;
		}


		cout << "w : ��, s :�Ʒ�, a : ����, d : ������, q : ����"; //key guide
		cinput = _getch();

		if (cinput == 'q' || cinput == 'Q') { 
			break;
		}

		switch (cinput) //* �̵��� switch ��
		{
		case 'w':
		case 'W':
			if (iStar > 3) {
				iNum[iStar] = iNum[iStar - 4]; //*��ġ�� �̵��Ϸ��� ���� �� ����
				iNum[iStar - 4] = INT_MAX; // *�� ���� ������ ������ �����Ƿ� ���� ������ �ʿ� ����
			}
			break;
		case 's':
		case 'S':
			if (iStar < 12) {
				iNum[iStar] = iNum[iStar + 4];
				iNum[iStar + 4] = INT_MAX;
			}
			break; 
		case 'a':
		case 'A':
			if (iStar % 4) {
				iNum[iStar] = iNum[iStar - 1];
				iNum[iStar - 1] = INT_MAX;
			}
			break;
		case 'd':
		case 'D':
			if ((iStar % 4) != 3) {
				iNum[iStar] = iNum[iStar + 1];
				iNum[iStar + 1] = INT_MAX;
			}
			break;
		default:
			break;
		}
	}

	cout << endl << "������ ���� �մϴ�." << endl;


	return 0;
}