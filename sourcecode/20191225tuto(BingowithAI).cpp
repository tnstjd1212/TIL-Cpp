//���� ���� ����� : 6�� ���� ���� �Ǹ� �¸�

#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};

int main() {

	srand((unsigned int)time(0));

	int iBingo[25] = {};
	int iAIBingo[25] = {};

	//1~25 ���� ���ڸ� �־��ش�.
	for (int i = 0; i < 25; ++i) {
		iBingo[i] = i + 1;
		iAIBingo[i] = i + 1;
	}

	//number shuffle
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; ++i) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iBingo[idx1];
		iBingo[idx1] = iBingo[idx2];
		iBingo[idx2] = iTemp;

		//AI ���ڵ� ���´�.
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAIBingo[idx1];
		iAIBingo[idx1] = iAIBingo[idx2];
		iAIBingo[idx2] = iTemp;
	}

	int iComplete = 0, iAIComplete = 0; // �ϼ��� ������ ������ ���� �Ѵ�.


	//AI ���̵� ����
	while (true) {
		system("cls");
		cout << " 1. Easy" << endl;
		cout << " 2. Hard" << endl;
		cout << "AI ��带 �����ϼ��� : ";
		int iAIMode;
		cin >> iAIMode;

		if (iAIMode == AM_EASY || iAIMode == AM_HARD)
			break;
	}
	// AI Easy ��� : �ߺ����� ���� �� �߿� �ϳ��� �����ϰ� ����
	// AI Hard ��� : ���ε� �߿��� ���� �� Ȯ���� ���� ���� ������ ���� �� �ϳ��� ����
	while (true) {
		system("cls");
		//���ڸ� 5X5�� ����Ѵ�.
		cout << "=================Player================" << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (iBingo[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else {
					cout << iBingo[5 * i + j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "Player ���� �ϼ� ���� : " << iComplete << endl << endl;

		cout << "=================AI====================" << endl;
		for (int i = 0; i < 5; ++i) {
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[i * 5 + j] == INT_MAX) {
					cout << "*\t";
				}
				else
					cout << iAIBingo[i * 5 + j] << "\t";
			}
			cout << endl;
		}
		cout << "AI ���� �ϼ� ���� : " << iAIComplete << endl;
		if (iComplete >= 6) {
			cout << "Player �¸�" << endl;
			break;
		}
		else if (iAIComplete >= 6) {
			cout << "AI �¸�" << endl;
			break;
		}

		cout << "���ڸ� �Է��ϼ���.(0�� ������ ����˴ϴ�) : ";
		int iInput;
			cin >> iInput;

		if (iInput == 0)
			break;
		else if (iInput < 1 || iInput > 25) {
			cout << "���� ���� ���ڰ� �ƴմϴ�.���ڸ� �ٽ� �Է��ϼ���." << endl;
			system("pause");
			continue;
		}
		bool bAcc = true; //�ߺ� Ȯ�� �� ����
		//�ߺ��Ǿ��ٰ� ���� �� ���ڸ� ã���� �ߺ� ���� �ʾҴٷ� ����
		
		for (int i = 0; i < 25; ++i) {
			if (iInput == iBingo[i]) {
				bAcc = false;
				iBingo[i] = INT_MAX;
				//�� �̻� ���ڸ� ã�� �� �ʿ䰡 �����Ƿ� for���� ����������.
				break;
			}
		}
		if (bAcc) { //true �� ��� �ߺ��� ���ڸ� �Է��� ���̹Ƿ� �ٽ� �Է��ϰ� �Ѵ�.
			cout << "�ߺ��� �����Դϴ�.���ڸ� �ٽ� �Է��ϼ���." << endl;
			system("pause");
			continue;
		}

		//AI ���ڸ� ���� ��ȯ
		for (int i = 0; i < 25; ++i) {
			if (iInput == iAIBingo[i]) {
				iAIBingo[i] = INT_MAX;
				break;
			}
		}


		//���� �ϼ� �Ǿ����� üũ
		iComplete = 0;
		iAIComplete = 0;
		for (int i = 0; i < 5; ++i) {
			//Player ���� ���� üũ
			//���� 5�� üũ
			int icheck = 0;
			for (int j = 0; j < 5; ++j) {
				if (iBingo[i * 5 + j] == INT_MAX)
					++icheck;
				else //�ϳ��� �ƴ� ��� ���� �ƴϹǷ� �� ���� �ʿ� �����Ƿ� Ż�� 
					break;
			}
			if (icheck == 5) { //5���� ��� üũ ������ 1Bingo
				++iComplete;
			}

			// ���� 5�� üũ
			icheck = 0; //���θ� üũ�ϱ� ���� �ٽ� �ʱ�ȭ
			for (int j = 0; j < 5; ++j) {
				if (iBingo[j * 5 + i] == INT_MAX)
					++icheck;
				else
					break;
			}
			if (icheck == 5) {
				++iComplete;
			}

			//AI  ���� ���� üũ
			//���� 5�� üũ
			int iAIcheck = 0;
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[i * 5 + j] == INT_MAX)
					++iAIcheck;
				else //�ϳ��� �ƴ� ��� ���� �ƴϹǷ� �� ���� �ʿ� �����Ƿ� Ż�� 
					break;
			}
			if (iAIcheck == 5) { //5���� ��� üũ ������ 1Bingo
				++iAIComplete;
			}

			// ���� 5�� üũ
			iAIcheck = 0; //���θ� üũ�ϱ� ���� �ٽ� �ʱ�ȭ
			for (int j = 0; j < 5; ++j) {
				if (iAIBingo[j * 5 + i] == INT_MAX)
					++iAIcheck;
				else
					break;
			}
			if (iAIcheck == 5) {
				++iAIComplete;
			}
		}

		//Player �밢�� üũ
		//������ �밢�� üũ
		int icheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iBingo[6 * i] == INT_MAX)
				++icheck;
			else
				break;
		}
		if (icheck == 5) {
			++iComplete;
		}

		//���� �밢�� üũ
		icheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iBingo[4 + i * 4] == INT_MAX) {
				++icheck;
			}
			else {
				break;
			}
		}

		if (icheck == 5) {
			++iComplete;
		}


		//AI �밢�� üũ
		//������ �밢�� üũ
		int iAIcheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iAIBingo[6 * i] == INT_MAX)
				++iAIcheck;
			else
				break;
		}
		if (iAIcheck == 5) {
			++iAIComplete;
		}

		//���� �밢�� üũ
		iAIcheck = 0;
		for (int i = 0; i < 5; ++i) {
			if (iAIBingo[4 + i * 4] == INT_MAX) {
				++iAIcheck;
			}
			else {
				break;
			}
		}

		if (iAIcheck == 5) {
			++iAIComplete;
		}

	}

	return 0;
}