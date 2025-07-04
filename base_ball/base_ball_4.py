import random
from pickle import GLOBAL

#난이도
level_choice={'쉬움':9,'보통':12,'어려움':15} #난이도 리스트

#승리 패배 포기 횟수
win_count=[]            # 승리횟수
print(win_count)
print(len(win_count))       # 승리횟수의 길이
lose_count=[]           # 패배횟수
print(lose_count)
print(len(lose_count))      # 패배횟수의 길이
give_up_count=[]        # 포기횟수
print(give_up_count)
print(len(give_up_count))   # 포기횟수의 길이

total_count=len(win_count)+len(lose_count)+len(give_up_count)-3
# 총 플레이한 횟수=승리횟수의 길이+패배횟수의 길이+포기횟수의 길이

# 승률 계산
# (승리한 횟수/총플레이한 횟수)*100 "%" 로 표기
# win_rate=(len(win_count)-1)/total_count*100
# print(f"{win_rate}%")

print(level_choice)
print(level_choice.items())
print(level_choice.values())
print(level_choice.keys())
print(level_choice['쉬움'])
print(level_choice['보통'])
print(level_choice['어려움'])


com_num=random.sample(range(0,10),3)    # 컴퓨터 랜덤한 3자리수 생성
print(com_num)  # 컴퓨터 생성 수 출력

def game():
    while True:
        user_input=input("3자리수 입력")
        if user_input.isnumeric() and len(user_input) == 3:
            return user_input
        else:
            print("숫자3개만 입력해주세요.")
            continue
    print(user_input)
    while True:
        strike, ball = 0, 0
        for user_input in com_num:
            if int(user_input) == com_num:
                strike += 1
            elif int(user_input) in com_num:
                ball += 1
        return strike, ball