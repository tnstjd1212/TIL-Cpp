// �������� 2�� ���� 9�ܱ��� ���
//���� ��� ����






#include <iostream>

using namespace std;


int main(){
    /*
    2�� 3�� 4��
    5�� 6�� 7��
    8�� 9�� 10��
    */
    
    for (int i = 2; i <= 8; i += 3) {  // ���� ���� ��ġ �κ�
        for (int j = 1; j <= 9; ++j) { // �� ���� ����ϴ� �κ�
            for (int w = 0; w < 3; w++) { // ���� ���� ��ġ �κ�
                cout << i + w << " * " << j << " = " << i + w * j << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
/*
*
**
***
****
*****
*/
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= i; ++j) {
            cout << "*";
        }
        cout << endl;
    }


    /*
    *****
    ****
    ***
    **
    *
    */
    for (int i = 5; i >= 1; --i) {
        for (int j = i; j > 0; --j) {
            cout << "*";
        }
        cout << endl;
    }


/*
   *
  ***
 *****
*******
*/
    //���� : 3,2,1,0   �� : 1, 3, 5, 7
    for (int i = 0; i <= 3; ++i) {
        //���� ��¿�
        for (int j = 3; j > i; --j) {
            cout << " ";
        }
        //�� ��¿�
        for (int j = (1 + (2 * i)); j > 0; --j) {
            cout << "*";
        }
        cout << endl;
    }

    /*
       *
      ***
     *****
    *******
     *****
      ***
       * 
    */
    //���� : 3, 2, 1, 0, 1, 2, 3
    // �� : 1, 3, 5, 7, 5, 3, 1
    int iLine = 7; // �� �� ��Ʈ�� ���� (Ȧ����)

    for (int i = 0; i < iLine; ++i) {
        int iCount = 0;
        if (i <= iLine / 2) {
            iCount = i;
        }
        else {
            iCount = iLine - i - 1;
        }
        //���� ��¿�
        for (int j = iCount; j < iLine / 2; ++j) {
                cout << " ";
        }
        //�� ��¿�
        for (int j = 0; j < (1 + (2 * iCount)); ++j) {
            cout << "*";
        }
        cout << endl;
    }

	return 0;
}