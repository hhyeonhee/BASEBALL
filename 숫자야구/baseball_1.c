#include <stdio.h>   // 표준 입출력
#include <stdlib.h>  // rand, srand, system
#include <time.h>    // time
#include <string.h>  // strlen
#include <ctype.h>   // isdigit

#define INIT   0
#define GREEN  "\033[32m"
#define YELLOW "\033[33m"
#define RESET  "\033[0m"

int main()
{
    // 1) 0~9 숫자 중복 검사용 배열 초기화
    int used[10] = { INIT } ;

    // 2) 뽑은 숫자를 저장할 배열과 카운터 초기화
    int target[3] = { INIT } ;
    int count     = INIT ;

    // 3) 난수 시드 설정
    srand((unsigned int)time(NULL)) ;

    // 4) 중복 없이 3개 숫자 뽑기
    while (count < 3)
    {
        int r = rand() % 10 ;
        if (used[r] == 0)
        {
            used[r]        = 1 ;
            target[count]  = r ;
            count++ ;
        }
    }

    // 5) 테스트용: 정답 숫자 확인
    printf("test: 정답 숫자 = %d%d%d\n"
           , target[0], target[1], target[2]) ;

    // 6) 게임 정보 초기화
    int inning                = INIT ;
    int history_guess[100][3] = { { INIT } } ;
    int history_strike[100]   = { INIT } ;
    int history_ball[100]     = { INIT } ;
    char input[16]            = { INIT } ;

    // 7) 게임 루프
    while (1)
    {
        printf("세 자리 숫자를 입력하세요 (예: 012, 123): ") ;
        if (!fgets(input, sizeof(input), stdin))
        {
            continue ;
        }

        // 8) 입력 끝 개행 제거
        size_t len = strlen(input) ;
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0' ;
            len-- ;
        }
        if (len != 3)
        {
            continue ;
        }

        // 9) 입력 문자→숫자 변환 및 유효성 검사
        int  guess[3] = { INIT } ;
        int  valid    = 1 ;
        for (int i = INIT; i < 3; i++)
        {
            if (!isdigit((unsigned char)input[i]))
            {
                valid = 0 ;
                break ;
            }
            guess[i] = input[i] - '0' ;
        }
        if (!valid)
        {
            continue ;
        }
        if (guess[0] == guess[1] || guess[0] == guess[2] || guess[1] == guess[2])
        {
            continue ;
        }

        // 10) 스트라이크/볼 계산
        int strikes = INIT ;
        int balls   = INIT ;
        for (int i = INIT; i < 3; i++)
        {
            if (guess[i] == target[i])
            {
                strikes++ ;
            }
            else
            {
                for (int j = INIT; j < 3; j++)
                {
                    if (guess[i] == target[j])
                    {
                        balls++ ;
                        break ;
                    }
                }
            }
        }

        // 11) 기록 저장
        history_guess[inning][0] = guess[0] ;
        history_guess[inning][1] = guess[1] ;
        history_guess[inning][2] = guess[2] ;
        history_strike[inning]   = strikes ;
        history_ball[inning]     = balls ;
        inning++ ;

        // 12) 화면 갱신 및 출력
        system("clear") ;
        printf("=== 숫자야구 게임 ===\n") ;
        printf("현재 이닝: %d\n", inning) ;
        printf("+-----+---+---+\n") ;
        printf("| NUM | S | B |\n") ;
        printf("+-----+---+---+\n") ;
        for (int i = INIT; i < inning; i++)
        {
            printf("| %d%d%d | %s%d%s | %s%d%s |\n"
                   , history_guess[i][0]
                   , history_guess[i][1]
                   , history_guess[i][2]
                   , YELLOW, history_strike[i], RESET
                   , GREEN, history_ball[i], RESET
            ) ;
        }
        printf("+-----+---+---+\n") ;

        // 13) 승리 조건
        if (strikes == 3)
        {
            printf("%d회 만에 맞히셨습니다!\n", inning) ;
            break ;
        }
    }

    return 0 ;
}


