

#include <iostream>

using namespace std;

struct _tagStudent
{
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() 
{
	/*
	������ : �Ϲ� ������ ���� ����������, ������ ������ �޸��ּҸ� �����Ѵ�.
	��� ���� Ÿ���� ������ Ÿ���� ������ �� �ִ�. 
	�����ʹ� �޸� �ּҸ� ��� ���� �����̱� ������  x86������ ũ�Ⱑ 4byte�� ������,
	x64�� 8byte�� ���´�.

	�����ʹ� ������ �ִ� �ּҿ� �����Ͽ� ���� ������ �� �ִ�.
	���� : ����Ÿ�� *������;
	*/
	int iNum = 100;
	//���� �տ� &�� �ٿ��ָ� �ش� ������ �޸� �ּҰ� �ȴ�.
	int* pNum = &iNum;
	cout << *pNum << endl;
	*pNum = 1234;
	cout << iNum << endl;

	//�迭���� �迭�� �����ּ�
	int iArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9 ,0 };
	int* pArray = iArray;
	//pArray�� iArray �����

	/*
	������ ���� : +- ������ �����Ѵ�. ++, -- �� ��밡���ѵ�
	�ܼ��� �޸� �ּҰ��� 1�����ϴ� ���� �ƴ� ������ Ÿ����
	���� Ÿ���� ũ�⸸ŭ ���� �Ѵ�.
	��, �����Ϳ� ���ڸ� ���ؼ� �迭�� ��ҿ� ������ �� �ִ�.
	*/

	cout << *(pArray + 2) << endl;
	cout << *(pArray + 6) << endl;

	const char *pText = "�׽�Ʈ"; 
	//������ڿ��� �����ϰ� �޸� �ּҸ� �������°�
	//�̸��� �ٲٱ� ���ؼ��� �迭�� �����ؼ� �̸��� �����ؾ� ��

	cout << pText << endl;
	cout << (int*)pText << endl;

	//������ �ּҸ� �ٲٴ� ���� �����ϴ�.
	pText = "asd";

	cout << pText << endl;
	cout << (int*)pText << endl;
	//���� ��� ���ڿ� �� ��� �ּҰ� �ٲ��� �ʴ´�.
	pText = "asd";

	cout << pText << endl;
	cout << (int*)pText << endl;

	//�̰��� �迭�� �����ϰ� ���� ����ִ� ���̱� ������ �ּҰ� �ٸ���.
	char str[4] = "asd";

	cout << str << endl;
	cout << (int*)str << endl;

	_tagStudent tStudent = {};

	tStudent.iKor = 100;

	cout << tStudent.iKor << endl;


	_tagStudent* pStudent = &tStudent;

	//*������ ���� .�����ڰ� �켱������ �����Ƿ�
	//�����ͷ� ����ü ����� ������ ��� ()�� �� ����ؾ� �Ѵ�.

	(*pStudent).iKor = 50;

	cout << tStudent.iKor << endl;

	//Ȥ�� �޸��ּ�-> �� ���� ����� ������ �� �ִ�.

	pStudent->iKor = 80;

	cout << tStudent.iKor << endl;

	//void : Ÿ���� ����. void�� ������Ÿ���� Ȱ���� �� �ִ�.
	//void* ������ ������ ��� � Ÿ���� �޸� �ּҵ�
	//��� ���尡���ϴ�. ��, �������� �� �� ����.
	//��, �޸��ּҸ� �����ϴ� ���۷� Ȱ�� �ؾ��Ѵ�.


	//���������� : �������� �������̴�.
	//�������� �޸� �ּҸ� �����Ѵ�.

	int iNum1 = 111;
	int* pNum1 = &iNum1;
	int** ppNum = &pNum1; //**�� �ΰ� ���̸� ���� �����Ͱ� ���������.

	cout << ppNum << "=" << &pNum1 << endl; //int ���� ������ ����
	cout << *ppNum << "=" << pNum1 << endl; //int ������ ����
	cout << **ppNum << "=" << *pNum1 << endl; //int ����



	return 0;
}