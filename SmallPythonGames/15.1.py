import random
field = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
st = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]

############################################################# ВЫВОД

def vod(a):
    for k in range(0, 4):
        print("‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒")
        string = '| '
        for n in range(0, 4):
            if (a[k][n] < 10) and (a[k][n] != 0):
                string = string + str(a[k][n]) + ' | '
            elif a[k][n] == 0:
                string = string + '  | '
            else:
                string = string + str(a[k][n]) + '| '
        print(string)
    print("‒‒‒‒‒‒‒‒‒‒‒‒‒‒‒")

############################################################# ПРОВЕРКА НА РЕШЕНИЕ

def prov(b):
    if (b[0] == [1, 2, 3, 4]) and (b[1] == [5, 6, 7, 8]) and (b[2] == [9, 10, 11, 12]) and (b[3] == [13, 14, 15, 0]):
        return 1
    else:
        return 0

############################################################# ПРОВЕРКА НА 0

def string(field, st):
    t = 5
    for n in range(0, 4):
        if field[st][n] == 0:
            t = n
    return t


def column(field, cl):
    t = 5
    for k in range(0, 4):
        if field[k][cl] == 0:
            t = k
    return t

############################################################# СОСТАВЛЕНИЕ

s = 16
for i in range(0, 4):
    for j in range(0, 4):
        x = random.randrange(0, s)
        field[i][j] = st.pop(x)
        s -= 1

############################################################# ПРОВЕРКА

s = 0
for i in range(0, 4):
    for j in range(0, 4):
        if field[i][j] != 0:
            for n in range(j, 4):
                if (field[i][j] > field[i][n]) and (field[i][n] != 0):
                    s += 1
            for k in range(i+1, 4):
                for n in range(0, 4):
                    if (field[i][j] > field[k][n]) and (field[k][n] != 0):
                        s += 1
        else:
            s += (i+1)

############################################################# ИСПРАВЛЕНИЕ

if (s % 2) != 0:
    if (field[0][0] != 0) and (field[0][1] != 0):
        x = field[0][0]
        field[0][0] = field[0][1]
        field[0][1] = x
    else:
        x = field[1][0]
        field[1][0] = field[1][1]
        field[1][1] = x

############################################################# ОСНОВА

print('\n_____ПЯТНАШКИ_____\n\n')
vod(field)
check = 0
summ = 0
while check != 1:
    st = 0
    cl = 0

    kl = input('\nВведите клетку, которую хотите подвинуть: ')
    if kl.isdigit() == 1:
        kl1 = int(kl)
    else:
        kl1 = 0


    for i in range(0, 4):
        for j in range(0, 4):
            if field[i][j] == kl1:
                st = i
                cl = j

    if (st >= 0) and (st <= 3) and (cl >= 0) and (cl <= 3) and (field[st][cl] != 0):

        if string(field, st) != 5:  # ЕСЛИ НОЛЬ В СТРОКЕ
            pos = string(field, st)
            if pos > cl:
                for j in range(pos, cl, -1):
                    field[st][j] = field[st][j - 1]
                field[st][cl] = 0
                summ += 1
                vod(field)
                print()
                check = prov(field)
            else:
                for j in range(pos,cl):
                    field[st][j] = field[st][j + 1]
                field[st][cl] = 0
                summ += 1
                vod(field)
                print()
                check = prov(field)

        elif column(field, cl) != 5:  # ЕСЛИ НОЛЬ В СТОЛБЦЕ
            pos = column(field, cl)
            if pos > st:
                for i in range(pos, st, -1):
                    field[i][cl] = field[i - 1][cl]
                field[st][cl] = 0
                summ += 1
                vod(field)
                print()
                check = prov(field)
            else:
                for i in range(pos,st):
                    field[i][cl] = field[i + 1][cl]
                field[st][cl] = 0
                summ += 1
                vod(field)
                print()
                check = prov(field)

        else:  # ЕСЛИ НОЛЬ НИГДЕ
            print('\nНеправльный ввод данных, попробуйте еще раз')

    else:
        print('\nНеправльный ввод данных, попробуйте еще раз')


print('\n_____ПОЗДРАВЛЯЕМ, ГОЛОВОЛОМКА РЕШЕНА!_____\n')
print('Всего ходов: ' + str(summ))