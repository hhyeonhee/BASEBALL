import random

# 0.메인화면구성

while True:
    # 승리 패배 포기 횟수
    win_count = [None]  # 승리횟수
    # print(win_count)
    # print(len(win_count))  # 승리횟수의 길이
    lose_count = [None]  # 패배횟수
    # print(lose_count)
    # print(len(lose_count))  # 패배횟수의 길이
    give_up_count = [None]  # 포기횟수
    # print(give_up_count)
    # print(len(give_up_count))  # 포기횟수의 길이
    total_count = len(win_count) + len(lose_count) + len(give_up_count)
    # 총 플레이한 횟수=승리횟수의 길이+패배횟수의 길이+포기횟수의 길이
    # 승률 계산
    win_rate = (len(win_count)) / total_count * 100
    win_rate = win_rate
    # (승리한 횟수-1/총플레이한 횟수)*100 "%" 로 표기
    # print(win_rate)


    def play_game():
        com_num=random.sample(range(1,10),3)
        print(com_num)
        print(type(com_num))
        now_inning=1
        strike, ball, out = 0, 0, 0

        while True:
            print(f"""
            
            """)
            user_num_input_1 =input("숫자1 선택")
            user_num_input_1=int(user_num_input_1)
            user_num_input_2 =input("숫자2 선택")
            user_num_input_2=int(user_num_input_2)
            user_num_input_3 =input("숫자3 선택")
            user_num_input_3=int(user_num_input_3)


            if strike==3:
                break
            elif user_num_input_1 == com_num[0]:
                strike+=1
            elif user_num_input_2 == com_num[1]:
                strike+=1
            elif user_num_input_3 == com_num[2]:
                strike+=1
            elif user_num_input_1 in com_num:
                ball+=1
            elif user_num_input_2 in com_num:
                ball+=1
            elif user_num_input_3 in com_num:
                ball+=1
            else:
                print("아웃")
                out+=1
    print("""
    ███████████  ||  █████████  ||███████████||███████████||███████████  ||  █████████  ||██         ||██                   
    ██         ██||██         ██||██         ||██         ||██         ██||██         ██||██         ||██         
    ██         ██||██         ██||██         ||██         ||██         ██||██         ██||██         ||██         
    ███████████  ||█████████████||███████████||███████████||███████████  ||█████████████||██         ||██                
    ██         ██||██         ██||         ██||██         ||██         ██||██         ██||██         ||██           
    ██         ██||██         ██||         ██||██         ||██         ██||██         ██||██         ||██         
    ███████████  ||██         ██||███████████||███████████||███████████  ||██         ██||███████████||███████████
    """)
    main_input=input("""
    메인화면

    1.플레이
    2.전적확인
    3.게임종료
    """)
    main_input=int(main_input)

    if main_input == 1 :
        # 1-0.난이도선택
        level_input=input("""
        난이도선택화면
        1.쉬움 | 15이닝
        2.보통 | 12이닝
        3.어려 | 09이닝 
        """)
        level_input=int(level_input)

        if level_input == 1: #1-1.쉬움 15 이닝
            end_inning = 15
            play_game()
        elif level_input == 2: #1-2.보통 12 이닝
            end_inning = 12
            play_game()

        elif level_input == 3: #1-3.어려움 9이닝
            end_inning = 9
            play_game()

        else:
            print("잘못된선택")
            continue
    elif main_input == 2 :
        # 2.전적확인
        input(f"""
        승리 {len(win_count)-1}번
        패배 {len(lose_count)-1}번
        포기 {len(give_up_count)-1}번
        승률 {round(win_rate,3)} %
        """)
    elif main_input == 3 :
        exit("게임종료")
        # 3.게임종료
    else:
        print("잘못된선택")
        continue