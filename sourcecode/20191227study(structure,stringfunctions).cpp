

#include <iostream>

using namespace std;


#define NAME_SIZE 32

/*
����ü : �����ִ� �������� ��Ƽ� �ϳ��� ���ο� Ÿ���� ������ִ� ����̴�.
��������� ���� Ÿ���̴�.

struct ����ü�� {};

�迭�� ����ü�� ������
1. ������ �����̴�.
2. ���ӵ� �޸� ���� �Ҵ�ȴ�. 
(����ü ������� ���ӵ� �޸� ������ ������ �ȴ�.)

*/

struct _tagStudent {
	char strName[NAME_SIZE];
	int iNum;
	int iKorScore;
	int iMathScore;
	int iTotalScore;
	float fAvg;
};

int main() {
	_tagStudent tStudent = {}; //��� ��� 0���� �ʱ�ȭ ����
	//����ü �迭�� ������ �����ϴ�
	// _tagStudent tStudentArr[100] = {};
	//����ü ����� ����� ���� . �� �̿��Ѵ�.
	tStudent.iKorScore = 100;

	//���ڿ��� �迭�� �־��� ������ �ܼ� �������δ� �Ұ����ϴ�.
	//strcpy_s�� ������ �־�� �Ѵ�.
	//�� �Լ��� �����ʿ� �ִ� ���ڿ��� �������� �������ش�.
	strcpy_s(tStudent.strName, "�ڼ���");
	
	//���ڿ��� ���� �׻� 0(NULL)�� �������Ѵ�.
	//�ƴ϶�� ����� �� ���ڿ��� ���� �ν��� �� ���⶧���� ������ ������ ��µȴ�.
	
	//strcat_s() ���ڿ��� �ٿ��ִ� �Լ�
	//�����ʿ� �ִ� ���ڿ��� ���� ���ڿ��ڿ� �ٿ��ش�,
	strcat_s(tStudent.strName, " SoonSung");
	
	//strlen() ���ڿ��� ũ�⸦ �����ִ� �Լ�
	cout << "�̸� ����  : " << strlen(tStudent.strName) << endl;
	cout << "�̸� : " << tStudent.strName << endl;

	//strcmp �Լ��� �� ���ڿ��� ���Ͽ� ���� ��� 0�� ��ȯ �ϰ� �ٸ����
	//0�� �ƴ� ���� ��ȯ�Ѵ�.
	strcpy_s(tStudent.strName, "Soonsung");

	cout << "���� �̸��� �Է��ϼ��� : ";
	char strCmp[NAME_SIZE] = {};
	cin >> strCmp;
	if (strcmp(tStudent.strName, strCmp)) {
		cout << "���� �ʽ��ϴ�" << endl;
	}
	else
		cout << "�����ϴ�" << endl;
	
	
	
	
	
	return 0;
}