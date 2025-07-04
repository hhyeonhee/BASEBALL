#include <iostream>    // C: <stdio.h> (printf/scanf), C++: <iostream> (cout/cin)
#include <vector>      // C: 고정 길이 배열, C++: std::vector 사용
#include <algorithm>   // C: 직접 알고리즘 구현, C++: std::shuffle 제공
#include <random>      // C: rand()/srand(), C++: mt19937 등 다양한 엔진 제공
#include <ctime>       // C/C++ 모두에 time() 함수 선언 필요
#include <string>      // C: char 배열, C++: std::string 사용
#include <cctype>      // C/C++: isdigit() 등 문자 검사 함수
#include <cstdlib>     // C/C++: system(), std::exit
#include <mariadb/mysql.h>
#include <iomanip>
#include <sstream>

using namespace std;   // C++: std 네임스페이스 사용, C에는 해당 개념 없음

const int INIT    = 0;       // C++: const 상수 선언, C에서는 #define 또는 enum 사용
const string GREEN  = "\033[32m";  // ANSI 컬러 코드: 초록
const string YELLOW = "\033[33m";  // ANSI 컬러 코드: 노랑
const string RESET  = "\033[0m";   // ANSI 컬러 코드: 리셋

void insertToDatabase(unsigned int inning);

// 현재 시간 문자열 (YYYY-MM-DD HH:MM:SS)로 반환
string getCurrentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%F %T", &tstruct); // %F = YYYY-MM-DD, %T = HH:MM:SS
    return string(buf);
}

int main()
{
    // 1) 정답 후보(0~9) 초기화
    vector<int> num(10);
    for (int i = INIT; i < 10; i++)
    {
        num[i] = i;  // C: 배열 초기화, C++: vector 사용
    }

    // 2) Mersenne Twister 엔진(seed = 현재 시간)
    mt19937 random_num(static_cast<unsigned int>(time(nullptr)));
    // C: srand(time(NULL));  C++: mt19937 seed 초기화

    // 3) 후보 섞기
    shuffle(num.begin(), num.end(), random_num);
    // C: Fisher–Yates 직접 구현, C++: std::shuffle

    // 4) 정답 세 자리 선택
    int target[3] = { num[0], num[1], num[2] };
    // cout << "TEST: 정답 숫자 = " << target[0] << target[1] << target[2] << endl;
    // C: printf("TEST: %d%d%d\n", ...);

    // 5) 게임 상태 저장용 변수 및 배열
    int inning = INIT;                            // 시도 회수
    int history_guess[100][3];                    // 과거 입력 기록
    int history_strike[100];                      // 과거 스트라이크 개수
    int history_ball[100];                        // 과거 볼 개수
    string input;                                 // C: char input[16];

    // 6) 게임 루프
    while (true)
    {
        cout << "세 자리 숫자를 입력: ";
        if (!getline(cin, input))
        {
            continue;  // C: fgets 재호출
        }
        if (input.size() != 3)
        {
            continue;  // C: strlen(input) != 3
        }

        // 7) 입력 유효성 검사 및 문자→정수 변환
        int guess[3];
        bool valid = true;  // C: int valid = 1;
        for (int i = INIT; i < 3; i++)
        {
            if (!isdigit(input[i]))
            {
                valid = false;
                break;
            }
            guess[i] = input[i] - '0';  // '0'→48, '1'→49 차감 후 정수
        }
        if (!valid)
        {
            continue;
        }
        if (guess[0] == guess[1] || guess[0] == guess[2] || guess[1] == guess[2])
        {
            continue;  // 중복 입력 방지
        }

        // 8) 스트라이크/볼 계산
        int strikes = INIT;
        int balls   = INIT;
        for (int i = INIT; i < 3; i++)
        {
            if (guess[i] == target[i])
            {
                strikes++;
            }
            else
            {
                for (int j = INIT; j < 3; j++)
                {
                    if (guess[i] == target[j])
                    {
                        balls++;
                        break;
                    }
                }
            }
        }

        // 9) 기록 저장
        history_guess[inning][0] = guess[0];
        history_guess[inning][1] = guess[1];
        history_guess[inning][2] = guess[2];
        history_strike[inning]   = strikes;
        history_ball[inning]     = balls;
        inning++;

        // 10) 화면 갱신 및 이력 출력
        system("clear");  // C/C++ 동일
        cout << "=== 숫자야구 게임 ===" << endl;
        cout << "현재 이닝: " << inning << endl;
        cout << "+-----+---+---+" << endl;
        cout << "| NUM | S | B |" << endl;
        cout << "+-----+---+---+" << endl;
        for (int i = INIT; i < inning; i++)
        {
            cout << "| "
                 << history_guess[i][0]
                 << history_guess[i][1]
                 << history_guess[i][2]
                 << " | " << YELLOW << history_strike[i] << RESET
                 << " | " << GREEN << history_ball[i] << RESET
                 << " |" << endl;
        }
        cout << "+-----+---+---+" << endl;

        // 11) 종료 조건 확인
        if (strikes == 3)
        {
            insertToDatabase(inning);
            cout << inning << "회 만에 맞히셨습니다!" << endl;
            break;
        }
    }
    return 0; 
}

void insertToDatabase(unsigned int inning) {
    MYSQL* conn;
    const char* host = "localhost";
    const char* user = "IOT122";       // 수정 필요
    const char* pass = "122";          // 수정 필요
    const char* db   = "qts";          // 수정 필요

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, db, 0, NULL, 0)) {
        cerr << "MariaDB 연결 실패: " << mysql_error(conn) << endl;
        return;
    }

    string now = getCurrentTime();

    stringstream ss;
    ss << "INSERT INTO DEPT (DATETIME, INNING) VALUES ('"
       << now << "', " << inning << ")";

    string query = ss.str();

    if (mysql_query(conn, query.c_str())) {
        cerr << "INSERT 실패: " << mysql_error(conn) << endl;
    } else {
        cout << GREEN << "DB에 이닝 기록 저장 완료!" << RESET << endl;
    }

    mysql_close(conn);
}


