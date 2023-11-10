def order_at_cafe():
    menu = {
        1 : ['카페_아메리카노 Short', '3600'],
        2 : ['카페_아메리카노 Tall', '4100'],
        3 : ['카페_라떼 Short', '4100'],
        4 : ['카페_라떼 Tall', '4600'],
        5 : ['카푸치노 Short', '4100'],
        6 : ['카푸치노 Tall', '4600'],
        7 : ['카페모카 Short', '4100'],
        8 : ['카페모카 Tall', '4600'],
        9 : ['카라멜_마키아또 Short', '5100'],
        10 : ['카라멜_마키아또 Tall', '5600'],
        11 : ['스타벅스_돌체_라뗴 Short', '5100'],
        12 : ['스타벅스_돌체_라뗴 Tall', '5600']
    }
    total_sales = [0 for i in range(len(menu))]
    selection = [0 for i in range(0, 100)]

    while True:
        total = 0
        user_in = 0
        cnt = 0
        total_sales = 0
        select_flag = 0

        print_menu(menu)

        while True:
            user_in = int(input("주문하실 메뉴 숫자를 입력해주세요 >>"))
            selection[cnt] = user_in
            cnt += 1
            if user_in == 0:
                break

        if selection[0] == 0:
            print("주문을 종료합니다.")
            break

        for i in range(0, cnt):
            if selection[i] < 0 or 12 < selection[i]:
                print(str(selection[i]+1) + "는/은 없는 메뉴입니다...")
                select_flag = 1
                break

        if select_flag == 1:
            select_flag = 0
            continue

        print("주문한 상품 : ")
        for i in range(0, cnt - 1):
            idx = selection[i]
            item = menu.get(idx)
            print(item[0] + " " + item[1])
            total += int(item[1])
        print("합계 : " + str(total) + "원")


def print_menu(menu):
    print('============ CAFE MENU 리스트 ============')
    for key in menu.keys():
        print('[' + str(key) + ']' + menu.get(key)[0] + ', 가격: ' + menu.get(key)[1])


if __name__ == '__main__':
    order_at_cafe()