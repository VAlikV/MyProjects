import random
import time
field1 = [[], [], [], [], [], [], [], [], [], [], [], []]
field2 = [[], [], [], [], [], [], [], [], [], [], [], []]
col = ["А", "Б", "В", "Г", "Д", "Е", "Ж", "З", "И", "К"]
string = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
ch = [[0, 0, 0, 0], [0, 0, 0, 0]]
tr1 = [[0, 0, 0], [0, 0, 0]]
tr2 = [[0, 0, 0], [0, 0, 0]]
dw1 = [[0, 0], [0, 0]]
dw2 = [[0, 0], [0, 0]]
dw3 = [[0, 0], [0, 0]]
o1 = [0, 0]
o2 = [0, 0]
o3 = [0, 0]
o4 = [0, 0]
ch1 = [[0, 0, 0, 0], [0, 0, 0, 0]]
tr11 = [[0, 0, 0], [0, 0, 0]]
tr22 = [[0, 0, 0], [0, 0, 0]]
dw11 = [[0, 0], [0, 0]]
dw22 = [[0, 0], [0, 0]]
dw33 = [[0, 0], [0, 0]]
o11 = [0, 0]
o22 = [0, 0]
o33 = [0, 0]
o44 = [0, 0]
for i in range(0, 12):
    for j in range(0, 12):
        field1[i].append(0)
        field2[i].append(0)
# ----------------------------------- Вывод

def vod(a,b):
    print('\n      А     Б     В     Г     Д     Е     Ж     З     И     К                     А     Б     В     Г     Д     Е     Ж     З     И     К   ')
    for k in range(1, 11):
        print('   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+               +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+')
        if k - 1 == 9:
            string = str(k) + ' |'
        else:
            string = str(k) + '  |'
        for n in range(1, 11):
            if (a[k][n] == 0) or (a[k][n] == 1):
                string = string + '     |'
            elif a[k][n] == 5:
                string = string + '  ·  |'
            elif a[k][n] == 2:
                string = string + ' |х| |'
            elif (a[k][n] > 9) and (a[k][n] != 50):
                string = string + '  ■  |'
            elif a[k][n] == 50:
                string = string + '  ★  |'
        if k - 1 == 9:
            string = string + '           ' + str(k) + '  |'
        else:
            string = string + '            ' + str(k) + '  |'
        for n in range(1, 11):
            if (b[k][n] == 0) or (b[k][n] == 1):
                string = string + '     |'
            elif b[k][n] == 5:
                string = string + '  ·  |'
            elif b[k][n] == 2:
                string = string + ' |х| |'
            elif b[k][n] > 9:
                string = string + '     |'
        print(string)
    print('   +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+               +-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n')

# ----------------------------------- Поиск пробелов

def prob(pos):
    if len(pos) != 0:
        s = 0
        for i in range(0, len(pos)):
            if pos[i] == ' ':
                s += 1
        return s

# ----------------------------------- Замена о

def zamo(a):
    for k in range(1, 11):
        for n in range(1, 11):
            if a[k][n] == 50:
                a[k][n] = 5

# ----------------------------------- Размещение

def raz(n):
    x = 0
    y = 0
    slov = {4: 'четырехпалубного', 3: 'трехпалубного', 2: 'двухпалубного'}
    while x != (5 - n):
        while 1:
            pos = input('Введите координаты "начальной" палубы {} корабля (Через пробел): '.format(slov.get(n)))
            if (pos.find(' ') == -1) or (prob(pos) > 1) or (len(pos) < 3):
                print('Ошибка ввода данных, поробуйте еще раз.')
                break
            else:
                cl1, st1 = pos.split()
                cl1.upper()
            if (cl1 in col) and (st1 in string) and (field1[string.index(st1)+1][col.index(cl1)+1] == 0):
                while 1:
                    pos = input('Введите координаты "конечной" палубы {} корабля (Через пробел) (0 0 для отмены): '.format(slov.get(n)))
                    if (pos.find(' ') == -1) or (prob(pos) > 1) or (len(pos) < 3):
                        print('Ошибка ввода данных, поробуйте еще раз.')
                        break
                    else:
                        cl2, st2 = pos.split()
                        cl2.upper()
                    if (cl2 in col) and (st2 in string) and ((cl1 == cl2) and (abs(string.index(st2) - string.index(st1)) == (n-1))) and (field1[string.index(st2)+1][col.index(cl2)+1] == 0):
                        if string.index(st2) > string.index(st1):
                            for i in range(string.index(st1) + 1, string.index(st2) + 2):
                                field1[i][col.index(cl2) + 1] = (n*10 + x)
                                if field1[i - 1][col.index(cl2) + 1] < 5:
                                    field1[i - 1][col.index(cl2) + 1] = 1
                                    field1[i - 1][col.index(cl2) + 2] = 1
                                    field1[i - 1][col.index(cl2)] = 1
                                field1[i][col.index(cl2)] = 1
                                field1[i][col.index(cl2) + 2] = 1
                                y = i
                            field1[y + 1][col.index(cl2) + 1] = 1
                            field1[y + 1][col.index(cl2) + 2] = 1
                            field1[y + 1][col.index(cl2)] = 1
                        else:
                            for i in range(string.index(st2) + 1, string.index(st1) + 2):
                                field1[i][col.index(cl2) + 1] = (n*10 + x)
                                if field1[i - 1][col.index(cl2) + 1] < 5:
                                    field1[i - 1][col.index(cl2) + 1] = 1
                                    field1[i - 1][col.index(cl2) + 2] = 1
                                    field1[i - 1][col.index(cl2)] = 1
                                field1[i][col.index(cl2)] = 1
                                field1[i][col.index(cl2) + 2] = 1
                                y = i
                            field1[y + 1][col.index(cl2) + 1] = 1
                            field1[y + 1][col.index(cl2) + 2] = 1
                            field1[y + 1][col.index(cl2)] = 1
                        vod(field1, field2)
                        x = x + 1
                        break
                    elif (cl2 in col) and (st2 in string) and ((st1 == st2) and (abs(col.index(cl2) - col.index(cl1)) == n-1)) and (field1[string.index(st2)+1][col.index(cl2)+1] == 0):
                        if col.index(cl2) > col.index(cl1):
                            for i in range(col.index(cl1) + 1, col.index(cl2) + 2):
                                field1[string.index(st2) + 1][i] = (n*10 + x)
                                if field1[string.index(st2) + 1][i - 1] < 5:
                                    field1[string.index(st2) + 1][i - 1] = 1
                                    field1[string.index(st2) + 2][i - 1] = 1
                                    field1[string.index(st2)][i - 1] = 1
                                field1[string.index(st2)][i] = 1
                                field1[string.index(st2) + 2][i] = 1
                                y = i
                            field1[string.index(st2) + 1][y + 1] = 1
                            field1[string.index(st2) + 2][y + 1] = 1
                            field1[string.index(st2)][y + 1] = 1
                        else:
                            for i in range(col.index(cl2) + 1, col.index(cl1) + 2):
                                field1[string.index(st2) + 1][i] = (n*10 + x)
                                if field1[string.index(st2) + 1][i - 1] < 5:
                                    field1[string.index(st2) + 1][i - 1] = 1
                                    field1[string.index(st2) + 2][i - 1] = 1
                                    field1[string.index(st2)][i - 1] = 1
                                field1[string.index(st2)][i] = 1
                                field1[string.index(st2) + 2][i] = 1
                                y = i
                            field1[string.index(st2) + 1][y + 1] = 1
                            field1[string.index(st2) + 2][y + 1] = 1
                            field1[string.index(st2)][y + 1] = 1
                        vod(field1, field2)
                        x = x + 1
                        break
                    elif (st2 == "0") and (cl2 == "0"):
                        break
                    else:
                        print('Ошибка ввода данных, поробуйте еще раз.')
            else:
                print('Ошибка ввода данных, поробуйте еще раз.')
            break

# ----------------------------------- Заполнение 2

def zap(field2, n):
    x = 0
    y = 0
    st2 = 0
    cl2 = 0
    while x != (5 - n):
        while 1:
            cl1 = random.randrange(1, 11)
            st1 = random.randrange(1, 11)
            nap = random.randrange(1, 5)
            if field2[st1][cl1] == 0:
                if nap == 1:
                    st2 = st1
                    cl2 = cl1 + (n-1)
                elif nap == 2:
                    st2 = st1
                    cl2 = cl1 - (n-1)
                elif nap == 3:
                    cl2 = cl1
                    st2 = st1 - (n-1)
                elif nap == 4:
                    cl2 = cl1
                    st2 = st1 + (n-1)
            if (st2 in range(1, 11)) and (cl2 in range(1, 11)):
                if field2[st2][cl2] == 0:
                    if cl1 == cl2:
                        if st2 > st1:
                            for i in range(st1, st2 + 1):
                                field2[i][cl2] = (n * 10 + x)
                                if field2[i - 1][cl2] < 5:
                                    field2[i - 1][cl2] = 1
                                    field2[i - 1][cl2 + 1] = 1
                                    field2[i - 1][cl2 - 1] = 1
                                field2[i][cl2 - 1] = 1
                                field2[i][cl2 + 1] = 1
                                y = i
                            field2[y + 1][cl2] = 1
                            field2[y + 1][cl2 + 1] = 1
                            field2[y + 1][cl2 - 1] = 1
                        else:
                            for i in range(st2, st1 + 1):
                                field2[i][cl2] = (n * 10 + x)
                                if field2[i - 1][cl2] < 5:
                                    field2[i - 1][cl2] = 1
                                    field2[i - 1][cl2 + 1] = 1
                                    field2[i - 1][cl2 - 1] = 1
                                field2[i][cl2 - 1] = 1
                                field2[i][cl2 + 1] = 1
                                y = i
                            field2[y + 1][cl2] = 1
                            field2[y + 1][cl2 + 1] = 1
                            field2[y + 1][cl2 - 1] = 1
                        x = x + 1
                        break
                    elif st1 == st2:
                        if cl2 > cl1:
                            for i in range(cl1, cl2 + 1):
                                field2[st2][i] = (n * 10 + x)
                                if field2[st2][i - 1] < 5:
                                    field2[st2][i - 1] = 1
                                    field2[st2 + 1][i - 1] = 1
                                    field2[st2 - 1][i - 1] = 1
                                field2[st2 - 1][i] = 1
                                field2[st2 + 1][i] = 1
                                y = i
                            field2[st2][y + 1] = 1
                            field2[st2 + 1][y + 1] = 1
                            field2[st2 - 1][y + 1] = 1
                        else:
                            for i in range(cl2, cl1 + 1):
                                field2[st2][i] = (n * 10 + x)
                                if field2[st2][i - 1] < 5:
                                    field2[st2][i - 1] = 1
                                    field2[st2 + 1][i - 1] = 1
                                    field2[st2 - 1][i - 1] = 1
                                field2[st2 - 1][i] = 1
                                field2[st2 + 1][i] = 1
                                y = i
                            field2[st2][y + 1] = 1
                            field2[st2 + 1][y + 1] = 1
                            field2[st2 - 1][y + 1] = 1
                        x = x + 1
                        break
            break

# ----------------------------------- Заполнение 1

def zap1(field2):
    x = 0
    y = 0
    while x != 4:
        while 1:
            cl1 = random.randrange(1, 11)
            st1 = random.randrange(1, 11)
            if field2[st1][cl1] == 0:
                field2[st1][cl1] = 10 + x
                field2[st1 - 1][cl1 - 1] = 1
                field2[st1 - 1][cl1] = 1
                field2[st1 - 1][cl1 + 1] = 1
                field2[st1][cl1 - 1] = 1
                field2[st1][cl1 + 1] = 1
                field2[st1 + 1][cl1 - 1] = 1
                field2[st1 + 1][cl1] = 1
                field2[st1 + 1][cl1 + 1] = 1
                x = x + 1
                break

# ----------------------------------- Проверка на затопление

def prov(f):
    s = 0
    a = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    for i in range(1,11):
        for j in range(1,11):
            if f[i][j] == 40:
                a[0] = a[0] + 1
            elif f[i][j] == 30:
                a[1] = a[1] + 1
            elif f[i][j] == 31:
                a[2] = a[2] + 1
            elif f[i][j] == 20:
                a[3] = a[3] + 1
            elif f[i][j] == 21:
                a[4] = a[4] + 1
            elif f[i][j] == 22:
                a[5] = a[5] + 1
            elif f[i][j] == 10:
                a[6] = a[6] + 1
            elif f[i][j] == 11:
                a[7] = a[7] + 1
            elif f[i][j] == 12:
                a[8] = a[8] + 1
            elif f[i][j] == 13:
                a[9] = a[9] + 1
    for k in range(0,10):
        if a[k] == 0:
            s = s + 1
    return s

# ----------------------------------- Окружение точками

def okr(field2, ch1, tr11, tr22, dw11, dw22, dw33, o11, o22, o33, o44):
    if (field2[ch1[0][0]][ch1[1][0]] == 2) and (field2[ch1[0][1]][ch1[1][1]] == 2) and (field2[ch1[0][2]][ch1[1][2]] == 2) and (field2[ch1[0][3]][ch1[1][3]] == 2):
        for i in range(0, 4):
            if field2[ch1[0][i]+1][ch1[1][i]] != 2:
                field2[ch1[0][i] + 1][ch1[1][i]] = 5
            if field2[ch1[0][i]-1][ch1[1][i]] != 2:
                field2[ch1[0][i] - 1][ch1[1][i]] = 5
            if field2[ch1[0][i]][ch1[1][i]+1] != 2:
                field2[ch1[0][i]][ch1[1][i]+1] = 5
            if field2[ch1[0][i]][ch1[1][i]-1] != 2:
                field2[ch1[0][i]][ch1[1][i]-1] = 5
            field2[ch1[0][i] + 1][ch1[1][i] + 1] = 5
            field2[ch1[0][i] - 1][ch1[1][i] + 1] = 5
            field2[ch1[0][i] + 1][ch1[1][i] - 1] = 5
            field2[ch1[0][i] - 1][ch1[1][i] - 1] = 5
    if (field2[tr11[0][0]][tr11[1][0]] == 2) and (field2[tr11[0][1]][tr11[1][1]] == 2) and (field2[tr11[0][2]][tr11[1][2]] == 2):
        for i in range(0,3):
            if field2[tr11[0][i]+1][tr11[1][i]] != 2:
                field2[tr11[0][i] + 1][tr11[1][i]] = 5
            if field2[tr11[0][i]-1][tr11[1][i]] != 2:
                field2[tr11[0][i] - 1][tr11[1][i]] = 5
            if field2[tr11[0][i]][tr11[1][i]+1] != 2:
                field2[tr11[0][i]][tr11[1][i]+1] = 5
            if field2[tr11[0][i]][tr11[1][i]-1] != 2:
                field2[tr11[0][i]][tr11[1][i]-1] = 5
            field2[tr11[0][i] + 1][tr11[1][i] + 1] = 5
            field2[tr11[0][i] - 1][tr11[1][i] + 1] = 5
            field2[tr11[0][i] + 1][tr11[1][i] - 1] = 5
            field2[tr11[0][i] - 1][tr11[1][i] - 1] = 5
    if (field2[tr22[0][0]][tr22[1][0]] == 2) and (field2[tr22[0][1]][tr22[1][1]] == 2) and (field2[tr22[0][2]][tr22[1][2]] == 2):
        for i in range(0,3):
            if field2[tr22[0][i]+1][tr22[1][i]] != 2:
                field2[tr22[0][i] + 1][tr22[1][i]] = 5
            if field2[tr22[0][i]-1][tr22[1][i]] != 2:
                field2[tr22[0][i] - 1][tr22[1][i]] = 5
            if field2[tr22[0][i]][tr22[1][i]+1] != 2:
                field2[tr22[0][i]][tr22[1][i]+1] = 5
            if field2[tr22[0][i]][tr22[1][i]-1] != 2:
                field2[tr22[0][i]][tr22[1][i]-1] = 5
            field2[tr22[0][i] + 1][tr22[1][i] + 1] = 5
            field2[tr22[0][i] - 1][tr22[1][i] + 1] = 5
            field2[tr22[0][i] + 1][tr22[1][i] - 1] = 5
            field2[tr22[0][i] - 1][tr22[1][i] - 1] = 5
    if (field2[dw11[0][0]][dw11[1][0]] == 2) and (field2[dw11[0][1]][dw11[1][1]] == 2):
        for i in range(0,2):
            if field2[dw11[0][i]+1][dw11[1][i]] != 2:
                field2[dw11[0][i] + 1][dw11[1][i]] = 5
            if field2[dw11[0][i]-1][dw11[1][i]] != 2:
                field2[dw11[0][i] - 1][dw11[1][i]] = 5
            if field2[dw11[0][i]][dw11[1][i]+1] != 2:
                field2[dw11[0][i]][dw11[1][i]+1] = 5
            if field2[dw11[0][i]][dw11[1][i]-1] != 2:
                field2[dw11[0][i]][dw11[1][i]-1] = 5
            field2[dw11[0][i] + 1][dw11[1][i] + 1] = 5
            field2[dw11[0][i] - 1][dw11[1][i] + 1] = 5
            field2[dw11[0][i] + 1][dw11[1][i] - 1] = 5
            field2[dw11[0][i] - 1][dw11[1][i] - 1] = 5
    if (field2[dw22[0][0]][dw22[1][0]] == 2) and (field2[dw22[0][1]][dw22[1][1]] == 2):
        for i in range(0,2):
            if field2[dw22[0][i]+1][dw22[1][i]] != 2:
                field2[dw22[0][i] + 1][dw22[1][i]] = 5
            if field2[dw22[0][i]-1][dw22[1][i]] != 2:
                field2[dw22[0][i] - 1][dw22[1][i]] = 5
            if field2[dw22[0][i]][dw22[1][i]+1] != 2:
                field2[dw22[0][i]][dw22[1][i]+1] = 5
            if field2[dw22[0][i]][dw22[1][i]-1] != 2:
                field2[dw22[0][i]][dw22[1][i]-1] = 5
            field2[dw22[0][i] + 1][dw22[1][i] + 1] = 5
            field2[dw22[0][i] - 1][dw22[1][i] + 1] = 5
            field2[dw22[0][i] + 1][dw22[1][i] - 1] = 5
            field2[dw22[0][i] - 1][dw22[1][i] - 1] = 5
    if (field2[dw33[0][0]][dw33[1][0]] == 2) and (field2[dw33[0][1]][dw33[1][1]] == 2):
        for i in range(0,2):
            if field2[dw33[0][i]+1][dw33[1][i]] != 2:
                field2[dw33[0][i] + 1][dw33[1][i]] = 5
            if field2[dw33[0][i]-1][dw33[1][i]] != 2:
                field2[dw33[0][i] - 1][dw33[1][i]] = 5
            if field2[dw33[0][i]][dw33[1][i]+1] != 2:
                field2[dw33[0][i]][dw33[1][i]+1] = 5
            if field2[dw33[0][i]][dw33[1][i]-1] != 2:
                field2[dw33[0][i]][dw33[1][i]-1] = 5
            field2[dw33[0][i] + 1][dw33[1][i] + 1] = 5
            field2[dw33[0][i] - 1][dw33[1][i] + 1] = 5
            field2[dw33[0][i] + 1][dw33[1][i] - 1] = 5
            field2[dw33[0][i] - 1][dw33[1][i] - 1] = 5
    if field2[o11[0]][o11[1]] == 2:
            field2[o11[0] + 1][o11[1]] = 5
            field2[o11[0]- 1][o11[1]] = 5
            field2[o11[0]][o11[1]+1] = 5
            field2[o11[0]][o11[1]-1] = 5
            field2[o11[0] + 1][o11[1] + 1] = 5
            field2[o11[0] - 1][o11[1] + 1] = 5
            field2[o11[0] + 1][o11[1] - 1] = 5
            field2[o11[0] - 1][o11[1] - 1] = 5
    if field2[o22[0]][o22[1]] == 2:
            field2[o22[0] + 1][o22[1]] = 5
            field2[o22[0] - 1][o22[1]] = 5
            field2[o22[0]][o22[1]+1] = 5
            field2[o22[0]][o22[1]-1] = 5
            field2[o22[0] + 1][o22[1] + 1] = 5
            field2[o22[0] - 1][o22[1] + 1] = 5
            field2[o22[0] + 1][o22[1] - 1] = 5
            field2[o22[0] - 1][o22[1] - 1] = 5
    if field2[o33[0]][o33[1]] == 2:
            field2[o33[0] + 1][o33[1]] = 5
            field2[o33[0] - 1][o33[1]] = 5
            field2[o33[0]][o33[1]+1] = 5
            field2[o33[0]][o33[1]-1] = 5
            field2[o33[0] + 1][o33[1] + 1] = 5
            field2[o33[0] - 1][o33[1] + 1] = 5
            field2[o33[0] + 1][o33[1] - 1] = 5
            field2[o33[0] - 1][o33[1] - 1] = 5
    if field2[o44[0]][o44[1]] == 2:
            field2[o44[0] + 1][o44[1]] = 5
            field2[o44[0] - 1][o44[1]] = 5
            field2[o44[0]][o44[1]+1] = 5
            field2[o44[0]][o44[1]-1] = 5
            field2[o44[0] + 1][o44[1] + 1] = 5
            field2[o44[0] - 1][o44[1] + 1] = 5
            field2[o44[0] + 1][o44[1] - 1] = 5
            field2[o44[0] - 1][o44[1] - 1] = 5

# ----------------------------------- Начало

vod(field1, field2)
print()

# ----------------------------------- Поле бота

zap(field2, 4)
zap(field2, 3)
zap(field2, 2)
zap1(field2)
vod(field1, field2)

# ----------------------------------- Заполнение поля


while 1:
    sposob = input('\nКак заполнить поле? (Вречную(1) или автоматически(2)) ')
    if sposob == '1':
        raz(4)
        raz(3)
        raz(2)
        x = 0
        y = 0
        while x != 4:
            while 1:
                pos = input('\nВведите координаты однопалубного корабля (Через пробел): ')
                if (pos.rfind(' ') == -1) or (prob(pos) > 1) or (len(pos) < 3):
                    print('Ошибка ввода данных, поробуйте еще раз.')
                    break
                else:
                    cl1, st1 = pos.split()
                    cl1.upper()
                if (cl1 in col) and (st1 in string) and (field1[string.index(st1) + 1][col.index(cl1) + 1] == 0):
                    field1[string.index(st1) + 1][col.index(cl1) + 1] = 10 + x
                    field1[string.index(st1)][col.index(cl1)] = 1
                    field1[string.index(st1)][col.index(cl1) + 1] = 1
                    field1[string.index(st1)][col.index(cl1) + 2] = 1
                    field1[string.index(st1) + 1][col.index(cl1)] = 1
                    field1[string.index(st1) + 1][col.index(cl1) + 2] = 1
                    field1[string.index(st1) + 2][col.index(cl1)] = 1
                    field1[string.index(st1) + 2][col.index(cl1) + 1] = 1
                    field1[string.index(st1) + 2][col.index(cl1) + 2] = 1
                    vod(field1, field2)
                    x = x + 1
                    break
                else:
                    print('Ошибка ввода данных, поробуйте еще раз.')
        break
    elif sposob == '2':
        zap(field1, 4)
        zap(field1, 3)
        zap(field1, 2)
        zap1(field1)
        vod(field1, field2)
        break
    else:
        print('Ошибка вводы данных, попробуйте еще раз.')


# ----------------------------------- Поиск кораблей

x = 0
for i in range(1, 11):
    for j in range(1,11):
        if field1[i][j] == 40:
            ch[0][x] = i
            ch[1][x] = j
            x = x + 1

x = 0
y = 0
for i in range(1, 11):
    for j in range(1,11):
        if field1[i][j] == 30:
            tr1[0][x] = i
            tr1[1][x] = j
            x = x + 1
        elif field1[i][j] == 31:
            tr2[0][y] = i
            tr2[1][y] = j
            y = y + 1

x = 0
y = 0
z = 0
for i in range(1, 11):
    for j in range(1,11):
        if field1[i][j] == 20:
            dw1[0][x] = i
            dw1[1][x] = j
            x = x + 1
        elif field1[i][j] == 21:
            dw2[0][y] = i
            dw2[1][y] = j
            y = y + 1
        elif field1[i][j] == 22:
            dw3[0][z] = i
            dw3[1][z] = j
            z = z + 1

for i in range(1, 11):
    for j in range(1,11):
        if field1[i][j] == 10:
            o1[0] = i
            o1[1] = j
        elif field1[i][j] == 11:
            o2[0] = i
            o2[1] = j
        elif field1[i][j] == 12:
            o3[0] = i
            o3[1] = j
        elif field1[i][j] == 13:
            o4[0] = i
            o4[1] = j

# -----------------------

x = 0
for i in range(1, 11):
    for j in range(1,11):
        if field2[i][j] == 40:
            ch1[0][x] = i
            ch1[1][x] = j
            x = x + 1

x = 0
y = 0
for i in range(1, 11):
    for j in range(1,11):
        if field2[i][j] == 30:
            tr11[0][x] = i
            tr11[1][x] = j
            x = x + 1
        elif field2[i][j] == 31:
            tr22[0][y] = i
            tr22[1][y] = j
            y = y + 1

x = 0
y = 0
z = 0
for i in range(1, 11):
    for j in range(1,11):
        if field2[i][j] == 20:
            dw11[0][x] = i
            dw11[1][x] = j
            x = x + 1
        elif field2[i][j] == 21:
            dw22[0][y] = i
            dw22[1][y] = j
            y = y + 1
        elif field2[i][j] == 22:
            dw33[0][z] = i
            dw33[1][z] = j
            z = z + 1

for i in range(1, 11):
    for j in range(1,11):
        if field2[i][j] == 10:
            o11[0] = i
            o11[1] = j
        elif field2[i][j] == 11:
            o22[0] = i
            o22[1] = j
        elif field2[i][j] == 12:
            o33[0] = i
            o33[1] = j
        elif field2[i][j] == 13:
            o44[0] = i
            o44[1] = j

# ----------------------------------- Стрельба

win1 = 0
win2 = 0
kills = 0
kills2 = 0
sq = 1
prcl1 = 0
prst1 = 0
prcl = 0
prst = 0
while (win1 != 10) or (win2 != 10):
    serial1 = 1                     # ---------------------------------- Стрельба человека
    while serial1 == 1:
        while win1 != 10:
            pos = input('Куда стрелять, адмирал? ')
            kills = prov(field2)
            if (pos.find(' ') == -1) or (prob(pos) > 1) or (len(pos) < 3):
                print('Ошибка ввода данных, поробуйте еще раз.')
                serial1 = 2
                break
            else:
                a, b = pos.split()
            if (a in col) and (b in string):
                cl1 = col.index(a)+1
                st1 = string.index(b)+1
            else:
                print('Ошибка ввода данных, поробуйте еще раз.')
                serial1 = 2
                break
            if field2[st1][cl1] > 9:
                field2[st1][cl1] = 2
                serial1 = serial1 + 1
                if prov(field2) != kills:
                    okr(field2, ch1, tr11, tr22, dw11, dw22, dw33, o11, o22, o33, o44)
                    win1 = win1 + 1
                    vod(field1, field2)
                    print('Убили!')
                    break
                else:
                    vod(field1, field2)
                    print('Ранили!')
                    break
            elif (field2[st1][cl1] == 0) or (field2[st1][cl1] == 1):
                field2[st1][cl1] = 5
                serial1 = serial1 - 1
                break
            else:
                print('Ошибка ввода данных, поробуйте еще раз.')
                serial1 = 2
                break
        vod(field1, field2)
        serial1 = serial1 - 1
        if win1 == 10:
            break
    if win1 == 10:
        break
    serial2 = 1
    while serial2 == 1:
        kills2 = prov(field1)
        while win2 != 10:
            zamo(field1)
            if sq == 1: # ----------------------------------------------------------------- Первый сценарий
                st2 = random.randrange(1, 11)
                cl2 = random.randrange(1, 11)
                prst = st2
                prcl = cl2
                prst1 = st2
                prcl1 = cl2
                if field1[st2][cl2] > 9:
                    field1[st2][cl2] = 2
                    serial2 = 1
                    if prov(field1) != kills2:
                        okr(field1, ch, tr1, tr2, dw1, dw2, dw3, o1, o2, o3, o4)
                        win2 = win2 + 1
                        vod(field1, field2)
                        print('Убил, каналья!')
                        time.sleep(3)
                        sq = 1
                        break
                    else:
                        vod(field1, field2)
                        print('Ранил!')
                        time.sleep(3)
                        prst = prst1
                        prcl = prcl1
                        sq = 2
                        break
                elif (field1[st2][cl2] == 0) or (field1[st2][cl2] == 1):
                    field1[st2][cl2] = 50
                    vod(field1, field2)
                    sq = 1
                    serial2 = 0
                    break
                else:
                    serial2 = 1
                    sq = 1
                    break
            elif sq == 2: # ----------------------------------------------------------------- Второй сценарий
                if (prcl1 == 10) or (prcl == 11):
                    sq = 3
                    prst = prst1
                    prcl = prcl1
                    serial2 = 1
                    break
                else:
                    if field1[prst][prcl+1] > 9:
                        field1[prst][prcl+1] = 2
                        serial2 = 1
                        if prov(field1) != kills2:
                            okr(field1, ch, tr1, tr2, dw1, dw2, dw3, o1, o2, o3, o4)
                            win2 = win2 + 1
                            vod(field1, field2)
                            print('Убил, каналья!')
                            time.sleep(3)
                            sq = 1
                            break
                        else:
                            vod(field1, field2)
                            print('Ранил!')
                            time.sleep(3)
                            prcl = prcl + 1
                            sq = 2
                            break
                    elif (field1[prst][prcl+1] == 0) or (field1[prst][prcl+1] == 1):
                        field1[prst][prcl+1] = 50
                        vod(field1, field2)
                        prst = prst1
                        prcl = prcl1
                        sq = 3
                        serial2 = 0
                        break
                    else:
                        serial2 = 1
                        prst = prst1
                        prcl = prcl1
                        sq = 3
                        break
            elif sq == 3: # ----------------------------------------------------------------- Третий сценарий
                if (prcl1 == 1) or (prcl == 0):
                    sq = 4
                    prst = prst1
                    prcl = prcl1
                    serial2 = 1
                    break
                else:
                    if field1[prst][prcl-1] > 9:
                        field1[prst][prcl-1] = 2
                        serial2 = 1
                        if prov(field1) != kills2:
                            okr(field1, ch, tr1, tr2, dw1, dw2, dw3, o1, o2, o3, o4)
                            win2 = win2 + 1
                            vod(field1, field2)
                            print('Убил, каналья!')
                            time.sleep(3)
                            sq = 1
                            break
                        else:
                            vod(field1, field2)
                            print('Ранил!')
                            time.sleep(3)
                            prcl = prcl - 1
                            sq = 3
                            break
                    elif (field1[prst][prcl-1] == 0) or (field1[prst][prcl-1] == 1):
                        field1[prst][prcl-1] = 50
                        vod(field1, field2)
                        prst = prst1
                        prcl = prcl1
                        sq = 4
                        serial2 = 0
                        break
                    else:
                        serial2 = 1
                        prst = prst1
                        prcl = prcl1
                        sq = 4
                        break
            elif sq == 4:  # ----------------------------------------------------------------- Четвертый сценарий
                if (prst1 == 10) or (prst == 11):
                    sq = 5
                    prst = prst1
                    prcl = prcl1
                    serial2 = 1
                    break
                else:
                    if field1[prst+1][prcl] > 9:
                        field1[prst+1][prcl] = 2
                        serial2 = 1
                        if prov(field1) != kills2:
                            okr(field1, ch, tr1, tr2, dw1, dw2, dw3, o1, o2, o3, o4)
                            win2 = win2 + 1
                            vod(field1, field2)
                            print('Убил, каналья!')
                            time.sleep(3)
                            sq = 1
                            break
                        else:
                            vod(field1, field2)
                            print('Ранил!')
                            time.sleep(3)
                            prst = prst + 1
                            sq = 4
                            break
                    elif (field1[prst+1][prcl] == 0) or (field1[prst+1][prcl] == 1):
                        field1[prst+1][prcl] = 50
                        vod(field1, field2)
                        prst = prst1
                        prcl = prcl1
                        sq = 5
                        serial2 = 0
                        break
                    else:
                        serial2 = 1
                        prst = prst1
                        prcl = prcl1
                        sq = 5
                        break
            elif sq == 5:  # ----------------------------------------------------------------- Пятый сценарий
                if (prst1 == 1) or (prst == 0):
                    sq = 1
                    serial2 = serial2 + 1
                    break
                else:
                    if field1[prst-1][prcl] > 9:
                        field1[prst-1][prcl] = 2
                        serial2 = 1
                        if prov(field1) != kills2:
                            okr(field1, ch, tr1, tr2, dw1, dw2, dw3, o1, o2, o3, o4)
                            win2 = win2 + 1
                            vod(field1, field2)
                            print('Убил, каналья!')
                            time.sleep(3)
                            sq = 1
                            break
                        else:
                            vod(field1, field2)
                            print('Ранил!')
                            time.sleep(3)
                            prst = prst - 1
                            sq = 5
                            break
                    elif (field1[prst-1][prcl] == 0) or (field1[prst-1][prcl] == 1):
                        field1[prst-1][prcl] = 50
                        vod(field1, field2)
                        prst = prst1
                        prcl = prcl1
                        sq = 1
                        serial2 = 0
                        break
                    else:
                        serial2 = 1
                        prst = prst1
                        prcl = prcl1
                        sq = 1
                        break
        if win2 == 10:
            break


if win1 == 10:
    print('Мы победили, мой адмирал! Ураааа!')
elif win2 == 10:
    print('Прощайте, адмирал, мне было честью служить с Вами!')