import random

# 0.메인화면구성
while True:
    input("""
    1.플레이
    2.전적확인
    3.게임종료
    """)
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
win_rate=(len(win_count))/total_count*100
win_rate=win_rate
# (승리한 횟수-1/총플레이한 횟수)*100 "%" 로 표기
# print(win_rate)

# 난이도
level_name = {1: "쉬움", 2: "보통", 3: "어려움"}
level_choice = {1: 9, 2: 12, 3: 15}  # 난이도 리스트

main_monitor=input("""
1.플레이
2.전적확인
3.게임종료
""")

if int(main_monitor)==1:
#게임실행
elif int(main_monitor) == 2:
    if total_count <= 3:
        print("게임을 진행한적없음")
    else:
        input(f"""
        승 : {len(win_count)-1}
        패 : {len(lose_count)-1}
        포 : {len(give_up_count)-1}
        률 : {round(win_rate)}% 
        """)#3자리수 까지 표현
        continue
elif int(main_monitor) == 3:
    exit("게임종료")
else:
    print("잘못입력 메인화면으로")
    break
