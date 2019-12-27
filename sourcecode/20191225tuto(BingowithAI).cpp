//���� ���� ����� : 6�� ���� ���� �Ǹ� �¸�

#include <iostream>

#include <time.h>

using namespace std;



//��������
int iBingo[25] = {};
int iAIBingo[25] = {};//������
int iTemp, idx1, idx2; // ���ÿ� ����
int iComplete = 0, iAIComplete = 0; // �ϼ��� ���� ������ ������ ���� �Ѵ�.
int iAIMode = 0; //AI���̵� ���ÿ� ����
int iInput; // Player input�� AI input �� �����ϴ� ����
bool bAcc = true; //�ߺ� Ȯ�� �� ����
int iNonSelect[25] = {}; // AI�� ������ ���� �����ϴ� �迭
int iNonSelectCount = 0; // AI�� ������ ���� ������ ī���� �ϴ� ����
int iLine = 0;
int iStarCount = 0;
int iSaveCount = 0; // AI hard ��忡�� ���� ������ Ȯ���� ���� ������ ã�� ���� ���� 


enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};
enum LINE_NUMBER {
	LN_R1,
	LN_R2,
	LN_R3,
	LN_R4,
	LN_R5,
	LN_C1,
	LN_C2,
	LN_C3,
	LN_C4,
	LN_C5,
	LN_LT,
	LN_RT
};

int main() {

	srand((unsigned int)time(0));


	//1~25 ���� ���ڸ� �־��ش�.
	for (int i = 0; i < 25; ++i) {
		iBingo[i] = i + 1;
		iAIBingo[i] = i + 1;
	}

	//number shuffle
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

	

	//AI ���̵� ����
	while (true) {
		system("cls");
		cout << " 1. Easy" << endl;
		cout << " 2. Hard" << endl;
		cout << "AI ��带 �����ϼ��� : ";
		cin >> iAIMode;

		if (iAIMode == AM_EASY || iAIMode == AM_HARD)
			break;
	}

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

		switch (iAIMode) {
		case AM_EASY:
			cout << "AI easy mode" << endl;
			break;
		case AM_HARD:
			cout << "AI hard mode" << endl;
			break;
		}
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
		cout << "AI ���� �ϼ� ���� : " << iAIComplete << endl << endl;
		if (iComplete >= 6) {  // ���ÿ� �������� ��� Player �¸�
			cout << "Player �¸�" << endl;
			break;
		}
		else if (iAIComplete >= 6) {
			cout << "AI �¸�" << endl;
			break;
		}

		cout << "���ڸ� �Է��ϼ���.(0�� ������ ����˴ϴ�) : ";
			cin >> iInput;

		if (iInput == 0)
			break;
		else if (iInput < 1 || iInput > 25) {
			cout << "���� ���� ���ڰ� �ƴմϴ�.���ڸ� �ٽ� �Է��ϼ���." << endl;
			system("pause");
			continue;
		}
		
		//�ߺ��Ǿ��ٰ� ���� �� ���ڸ� ã���� �ߺ� ���� �ʾҴٷ� ����
		bAcc = true;
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

		//AI�� ������ �Ѵ�. AI��忡 ���� �޶�����.
		// AI Easy ��� : �ߺ����� ���� �� �߿� �ϳ��� �����ϰ� ����

		// AI Hard ��� : ���ε� �߿��� ���� �� Ȯ���� ���� ���� ������ ���� �� �ϳ��� ����
		iNonSelectCount = 0;
		iSaveCount = 0;
		iLine = 0;
		iNonSelect[25] = {};
		switch (iAIMode) {
		case AM_EASY:
			for (int i = 0; i < 25; ++i) {
				if (iAIBingo[i] != INT_MAX) {
					iNonSelect[iNonSelectCount] = iAIBingo[i];
					++iNonSelectCount;
				}
			}
			if (iNonSelectCount != 0) {
				iInput = iNonSelect[rand() % iNonSelectCount];
			}
			else
				cout << "������ �� �ִ� ���� �����ϴ�.";
			
			break;
		case AM_HARD:
			for (int i = 0; i < 5; ++i) {

				//Row �� ���� �˻�
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (iAIBingo[5 * i + j] == INT_MAX) {
						++iStarCount;
					}
				}
				if (iStarCount >= iSaveCount && iStarCount < 5) {
					iSaveCount = iStarCount;
					iLine = i; // Row 0~4
				}
				//column �� ���� �˻�
				iStarCount = 0;
				for (int j = 0; j < 5; ++j) {
					if (iAIBingo[i + j * 5] == INT_MAX) {
						++iStarCount;
					}
				}
				if (iStarCount >= iSaveCount && iStarCount < 5) {
					iSaveCount = iStarCount;
					iLine = i + 5; //column 5~9
				}
			}

			iStarCount = 0;
			for (int i = 0; i < 5; ++i) {
				if (iAIBingo[i * 6] == INT_MAX) {
					++iStarCount;
				}
			}
			if (iStarCount >= iSaveCount && iStarCount < 5) {
				iSaveCount = iStarCount;
				iLine = LN_LT;
			}

			iStarCount = 0;
			for (int i = 0; i < 5; ++i) {
				if (iAIBingo[4 + i * 4] == INT_MAX) {
					++iStarCount;
				}
			}
			if (iStarCount >= iSaveCount && iStarCount < 5) {
				iSaveCount = iStarCount;
				iLine = LN_RT;
			}

			switch (iLine) {
			case LN_R1:
			case LN_R2:
			case LN_R3:
			case LN_R4:
			case LN_R5:// ���� �� �� ���
				for (int i = 0; i < 5; ++i) {
					if (iAIBingo[iLine * 5 + i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[iLine * 5 + i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "������ �� �ִ� ���� �����ϴ�.";

				break;
			case LN_C1:
			case LN_C2:
			case LN_C3:
			case LN_C4:
			case LN_C5://���� �� �� ���
				for (int i = 0; i < 5; ++i) {
					if (iAIBingo[(iLine - 5) + 5 * i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[(iLine - 5) + 5 * i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "������ �� �ִ� ���� �����ϴ�.";

				break;
			case LN_LT:
				for (int i = 0; i < 5; ++i)
				{
					if (iAIBingo[6 * i] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[6 * i];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "������ �� �ִ� ���� �����ϴ�.";

				break;
			case LN_RT:
				for (int i = 0; i < 5; ++i)
				{
					if (iAIBingo[4 * i + 4] != INT_MAX) {
						iNonSelect[iNonSelectCount] = iAIBingo[4 * i + 4];
						++iNonSelectCount;
					}
				}
				if (iNonSelectCount != 0) {
					iInput = iNonSelect[rand() % iNonSelectCount];
				}
				else
					cout << "������ �� �ִ� ���� �����ϴ�.";

				break;// line switch
			}
			break; //AImode switch
		}

		cout << "AI�� ������ ���� " << iInput << "�Դϴ�." << endl;
		system("pause");


		//AI�� ������ ���� *�� ��ȯ
		for (int i = 0; i < 25; ++i) {
			if (iInput == iBingo[i]) {
				iBingo[i] = INT_MAX;
				break;
			}
		}


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