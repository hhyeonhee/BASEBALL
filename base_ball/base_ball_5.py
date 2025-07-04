import random

from btest import max_inning, user_num, give_up_count, switch, win_count, now_inning
from game import lose_count

#1난이도설정

#1-1 이지
#1-2 노말
#1-3 하드

# -랜덤한  # 3자리 숫자생성
com_num = random.sample(range(1, 10), 3)
# -1회부터시작(난이도별로끝나는시점9, 12, 15)
max_inning=level_name.get(level_input)
# -유저가3자리수입력
user_num=input("3자리숫자선택")

# S,#B 출력 -진행하기 / 포기하기
now_inning=1
strike,ball=0,0
while switch:
    now_inning+=1
    if user_num == com_num and max_inning+1<now_inning:
        strike+=1
        input_give_up=input(f"{strike}S/{ball}/엔터진행/0누르면포기")#-진행하기선택시다음회로이동
        if input_give_up==0:
            give_up_count=give_up_count+1
            switch=False    #-포기하기선택시(포기한횟수기록)-게임종료후메인화면으로이동
    elif user_num in com_num and max_inning+1<now_inning:
        ball+=1
        input_give_up = input(f"{strike}S/{ball}/엔터진행/0누르면포기")
        if input_give_up==0:
            give_up_count=give_up_count+1
            switch=False    #-포기하기선택시(포기한횟수기록)-게임종료후메인화면으로이동
    elif strike==3 and max_inning+1<now_inning:
        win_count=win_count+1
        input_give_up =input(f"{strike}S/0누르면메인으로")
        if input_give_up==0:
            switch=False
    elif max_inning<now_inning:
        lose_count=lose_count+1
        input("이닝초과")
        switch=False

# -반복(9, 12, 15까지)
# -결과출력 & 기록
# -계속할건지 그만할건지물어보고
# -계속할거면난이도설정으로이동
# -그만할거면메인화면으로이동