import random
from operator import index

from game import give_up_count, win_count

#난이도
level_name={1:"쉬움",2:"보통",3:"어려움"}
level_choice={1:9,2:12,3:15} #난이도 리스트

# 0.메인화면구성
switch=True
while True:
    com_num = random.sample(range(1, 10), 3)
    print(com_num)  ##
    # # 승리 패배 포기 횟수
    # win_count = []  # 승리횟수
    # # print(win_count)
    # # print(len(win_count))  # 승리횟수의 길이
    # lose_count = []  # 패배횟수
    # # print(lose_count)
    # # print(len(lose_count))  # 패배횟수의 길이
    # give_up_count = []  # 포기횟수
    # # print(give_up_count)
    # # print(len(give_up_count))  # 포기횟수의 길이
    # total_count = len(win_count) + len(lose_count) + len(give_up_count)
    # # 총 플레이한 횟수=승리횟수의 길이+패배횟수의 길이+포기횟수의 길이
    # # 승률 계산
    # win_rate=(len(win_count))/total_count*100
    # # (승리한 횟수-1/총플레이한 횟수)*100 "%" 로 표기
    # # print(win_rate)

    main_monitor = input("""
    1.플레이
    2.전적확인
    3.게임종료
    """)

    if int(main_monitor) == 1:
        level_input=input(f"""
        난이도선택
        1.{level_name.get(1)}/{level_choice.get(1)}
        2.{level_name.get(2)}/{level_choice.get(2)}
        3.{level_name.get(3)}/{level_choice.get(3)}
         """)
        level_input=int(level_input)
        if level_input in level_name:
            print(f"""
            난이도{level_name.get(level_input)}선택
            """)
            if level_input == int(level_choice.get(1)):
                max_inning=int(level_choice.get(1))
                strike,ball=0,0
                now_inning=0
                while switch:
                    user_num=input("3자리 숫자선택")
                    now_inning+=1
                    if user_num == com_num:
                        strike+=1
                        retire=input(f"{strike}S/{ball}B/엔터누르면진행/0입력시 포기")
                        if retire==0:
                            give_up_count=give_up_count+1
                        continue
                    elif user_num in com_num:
                        ball+=1
                        retire = input(f"{strike}S/{ball}B/엔터누르면진행/0입력시 포기")
                        if retire == 0:
                            give_up_count = give_up_count + 1
                        continue
                    elif strike==3:
                        win_count=win_count+1
                        print(f"{strike}S/{ball}B/엔터누르면 난이도선택)
                    elif max_inning == now_inning
                        print(f"이닝초과 게임종료")
                        break
            elif level_input == int(level_choice.get(2)):
                max_inning = int(level_choice.get(2))

            elif level_input ==int(level_choice.get(3)):
                max_inning = int(level_choice.get(3))

            else:
                print("잘못된선택 재선택")
                continue
        else:
            print("잘못된선택 재선택")
            continue



