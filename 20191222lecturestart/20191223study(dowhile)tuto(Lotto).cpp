
#include <iostream>
#include <time.h>


using namespace std;

int main() {
	/*
	do {}while(���ǽ�)
	do while���� ó�� �� ���� ������ �����ϰ�, �� �ڿ��� ���ǽ���
	üũ�ؼ� �����ϴ� �ݺ��� �̴�.
	*/

	/*
	�迭 : �������� ������ �� ���� ���� �� �� �ִ� ��� �̴�,
	����Ÿ�� �迭��[����]
	Ư¡ : ���ӵ� �޸� ������ �����ȴ�.
	*/


	srand((unsigned int)time(0));
	//lotto Program
	int iLOTTO[45] = {};

	for (int i = 0; i < 45; ++i) { //������ 1���� 45���� ���ʴ�� ����
		iLOTTO[i] = i + 1;
	}

	//shuffle :Swap algorithm Ȱ��
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i) { //������ �� �ε����� 100�� swap�Ѵ�
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLOTTO[idx1];
		iLOTTO[idx1] = iLOTTO[idx2];
		iLOTTO[idx2] = iTemp;
	}
	for (int i = 0; i < 6; ++i) {
		cout << iLOTTO[i] << "\t";
	}
	cout << "Bonus number :" << iLOTTO[6] << endl;


	return 0;
}