
/*
�߱����� :
1~9 ������ ������ 3���� ���ڸ� ���´�. 
��, ���ڴ� �ߺ��Ǿ�� �ȵȴ�.
player�� �� 3���� ���ڸ� ����� �ϸ� 3���� ���ڸ� �Է��Ѵ�.
���� 1���� ������ ��ġ�� ���ڸ� ��� ����ٸ�, 1strike,
��ġ�� ������ ��������, ���ڰ� �Է��� 3���� ���ڿ� ����ִٸ�,
1ball �����ϸ�,
�Է��� 3���� ���ڿ� ���� ���ڰ� �ƹ� �͵� ���ٸ� out �̴�.
 ���� 3���� ���ڿ� �ڸ��� ��� ��ġ�ϰ� �Է��ϸ� ������ ����ȴ�.
 ��, �Է��� ���� �߿� 0�� �ϳ��� ������� ����ȴ�.
*/



#include<iostream>
#include<time.h>

using namespace std;


int main() {
	//�������� 3���� ���ڸ� ������ �ڵ�
	srand((unsigned int)time(0));
	int iNum[9] = {}; //1~9�� ���ڸ� ���� �迭 ����

	for (int i = 0; i < 9; ++i) { // �迭�� 1~9 ������ ���ڸ� �ִ� �ڵ�
		iNum[i] = i + 1;
	}

	int iSwap, idx1, idx2;
	for (int i = 0; i < 50; ++i) { //shuffle
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		iSwap = iNum[idx1];
		iNum[idx1] = iNum[idx2];
		iNum[idx2] = iSwap;
	}

	int iRnum[3];
	for (int i = 0; i < 3; ++i) { //���� ���� �迭�� �� ���� 3�ڸ��� ���� ���ڷ� �̾ƿ�
		iRnum[i] = iNum[i];
	}

	int iCount = 0;
	int iPlayer[3];
	int iball = 0, istrike = 0;
	//game start
	while (true) {
		//Player�� �Է��� �޾ƿ��� �ڵ�
		cout << endl << "1���� 9������ ���� �ٸ� ���� 3���� �Է��� �ּ���. (0�� �ԷµǸ� ���� ����)" << endl;
		cin >> iPlayer[0] >> iPlayer[1] >> iPlayer[2];


		//Player�� �Է¿� 0�� �ִ��� Ȯ�� �ϴ� �ڵ�
		if ((iPlayer[0] == 0) || (iPlayer[1] == 0) || (iPlayer[2] == 0)) {
			break;
		}
		else if ((iPlayer[0] < 1) || (iPlayer[0] > 9) || (iPlayer[1] < 1) || (iPlayer[1] > 9) || (iPlayer[2] < 1) || (iPlayer[2] > 9)) {
			// 1~9������ ���ڰ� �ƴ� ���
			cout << "���� ���� ���ڰ� �ƴմϴ�." << endl;
			continue;
		}
		else if (iPlayer[0] == iPlayer[1] || iPlayer[1] == iPlayer[2] || iPlayer[2] == iPlayer[0]) {
			cout << "���ڰ� �ߺ� �Ǿ����ϴ�." << endl;
			continue;
		}


		//Player�� �Է°� ���� 3���� ���ڸ� ���ϴ� �ڵ�
		else {
			++iCount;
			iball = istrike = 0;
			for (int p = 0; p < 3; ++p) {
				for (int r = 0; r < 3; ++r) {
					if (iPlayer[p] == iRnum[r]) {
						if (p == r) {
							++istrike;
						}
						else {
							++iball;
						}
					}
				}
			}
		}


		// ������ ����� ����ϴ� �ڵ�
		if ((iball == 0) && (istrike == 0)) {
			cout << "Out!" << endl;
		}
		else if (istrike == 3) {
			cout << "Game Clear!!  �õ� Ƚ�� : " << iCount << endl;
			break;
		}
		else {
			cout << istrike << " strike, " << iball << " ball" << endl;
		}
	}

	return 0;
}