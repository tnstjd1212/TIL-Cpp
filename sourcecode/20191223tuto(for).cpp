// 구구단을 2단 부터 9단까지 출력
//별을 찍어 보자






#include <iostream>

using namespace std;


int main(){
    /*
    2단 3단 4단
    5단 6단 7단
    8단 9단 10단
    */
    
    for (int i = 2; i <= 8; i += 3) {  // 단의 세로 위치 부분
        for (int j = 1; j <= 9; ++j) { // 각 단을 출력하는 부분
            for (int w = 0; w < 3; w++) { // 단의 가로 위치 부분
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
    //공백 : 3,2,1,0   별 : 1, 3, 5, 7
    for (int i = 0; i <= 3; ++i) {
        //공백 출력용
        for (int j = 3; j > i; --j) {
            cout << " ";
        }
        //별 출력용
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
    //공백 : 3, 2, 1, 0, 1, 2, 3
    // 별 : 1, 3, 5, 7, 5, 3, 1
    int iLine = 7; // 줄 수 컨트롤 가능 (홀수만)

    for (int i = 0; i < iLine; ++i) {
        int iCount = 0;
        if (i <= iLine / 2) {
            iCount = i;
        }
        else {
            iCount = iLine - i - 1;
        }
        //공백 출력용
        for (int j = iCount; j < iLine / 2; ++j) {
                cout << " ";
        }
        //별 출력용
        for (int j = 0; j < (1 + (2 * iCount)); ++j) {
            cout << "*";
        }
        cout << endl;
    }

	return 0;
}