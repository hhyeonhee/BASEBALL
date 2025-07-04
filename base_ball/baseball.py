import random

def player_input():
    while True:
        player_number = input("3자리 숫자를 입력하세요 : ")
        player_number = ''.join(dict.fromkeys(player_number))

        if player_number.isnumeric() and len(player_number) == 3:
            return player_number
        else:
            continue

def game_check(player_number):
    strike, ball, index = 0, 0, 0
    print(secret_number)
    for number in secret_number:
        if int(player_number[index]) == number:
            strike += 1
        elif int(player_number[index]) in secret_number:
            ball += 1
            index += 1
    return strike, ball

def game_print():
    game_count = 0
    while game_count < 10:
        number = player_input()
        strike, ball = game_check(number)
        print(game_count+1,'회', '/' ,strike, "S", '/', ball, "B")
        game_count += 1

        if strike == 3:
            print("승리")
            break


while True:
    secret_number = random.sample(range(1, 10), 3)

    game_print()

    result = input("다시시작(y/n)")
    if result == 'n' or result == 'N':
        print("게임종료")
        break
    elif result == 'y' or result == 'Y':
        continue
    else:
        print("잘못입력")