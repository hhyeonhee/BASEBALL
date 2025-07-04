import random

def user_input():
    while True:
        user_number = input("3자리 숫자를 입력하세요 : ")
        user_number = ''.join(dict.fromkeys(user_number))

        if len(user_number) == 3:
            return user_number
        else:
            print("숫자 3개만 입력")
            continue

def game_check(user_number):
    strike, ball ,idx= 0, 0, 0
    print(secret_num)
    for num in secret_num:
        if int(user_num[idx]) == num:
            strike += 1
        elif int(user_num[idx]) in secret_num:
            ball += 1
            idx += 1
    return strike, ball

def game_result():
    game_count = 0
    while game_count < 10:
        num = user_input()
        strike, ball = game_check(num)
        print(game_count+1,'회', '/' ,strike, "스트라이크", "/", ball, "볼")
        game_count += 1

        if strike == 3:
            print("축하합니다.")
            print(game_count, "번만에 성공했습니다.")
            break

while True:
    secret_num = random.sample(range(1, 10), 3)
    print("1.플레이")

    game_result()

    result = input("다시시작(y/n)")
    if result == 'n' or result == 'N':
        print("게임종료")
        break
    elif result == 'y' or result == 'Y':
        continue
    else:
        print("잘못 입력")
