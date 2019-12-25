

#include <iostream>
#include <time.h>

int main()
{

    /*
    분기문 : if문과 switch문
    if문 : 조건을 체크해주는 기능
    if(조건문) {코드블럭}
    if문은 조건식이 true일 경우 코드블럭 안의 코드가 동작한다
    false일 경우 동작 되지 않는다.
    if문의 조건문은 혼자서 많이 생각해 봐야 
    조건을 더 잘 만들수 있을 것이다.
    */
    if (true) {
        std::cout << "if문의 조건이 true 입니다." << std::endl;
    }
    /*
    else : if문과 반드시 같이 사용 되어야 한다.
    if문 조건이 false일 경우 else가 있다면
    else 구문 안의 코드가 동작한다.
    */
    if (false)
        std::cout << "if문의 조건이 true 입니다" << std::endl;
    else
        std::cout << "if문의 조건이 false 입니다" << std::endl;


    // 난수 발생
    srand((unsigned int)time(0));
    std::cout << rand() << std::endl;
    std::cout << rand() << std::endl;
    std::cout << rand() << std::endl;
    //소숫점 아래까지 뽑고 싶을 때
    std::cout << (rand() % 10000 / 100.f) << std::endl;

    int iUpgrade = 0;
    std::cout << "Upgrade 기본 수치를 입력 하세요 (0~ 15) : ";
    std::cin >> iUpgrade;

    if (iUpgrade > 15 || iUpgrade < 0) {
        std::cout << "0에서 15사이의 숫자를 입력하세요" << std::endl;
        std::cin >> iUpgrade;
    }

    //강화 확률을 구한다.
    float fPercent = rand() % 10000 / 100.f;

    //강화 확률 : 업그레이드가 0~3 : 100% 성공, 4~6 : 40%, 7~9 : 10%
    //10~13 : 1%, 14~15 : 0.01%
    std::cout << "Upgrade : " << iUpgrade << std::endl;
    std::cout << "Percent : " << fPercent << std::endl;

    if (iUpgrade <= 3)
        std::cout << "강화 성공" << std::endl;
    else if ((4 <= iUpgrade) && (iUpgrade <= 6)) {
        if (fPercent <= 40.f) {
            std::cout << "강화 성공" << std::endl;
        }
        else
            std::cout << "강화 실패" << std::endl;
    }
    else if ((7 <= iUpgrade) && (iUpgrade <= 9)) {
        if (fPercent <= 10.f)
            std::cout << "강화 성공" << std::endl;
        else
            std::cout << "강화 실패" << std::endl;
    }
    else if ((10 <= iUpgrade) && (iUpgrade <= 13)) {
        if (fPercent <= 1.f)
            std::cout << "강화 성공" << std::endl;
        else
            std::cout << "강화 실패" << std::endl;
    }
    else if ((14 <= iUpgrade) && (iUpgrade <= 15)) {
        if (fPercent <= 0.01f)
            std::cout << "강화 성공" << std::endl;
        else
            std::cout << "강화 실패" << std::endl;
    }



    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
