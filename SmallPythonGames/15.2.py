import random
import pygame
import sys
pygame.init()
field = [[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 0, 0]]
st = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]
win = pygame.display.set_mode((365, 430))
pygame.display.set_caption('Пятнашки')

WHITE = (255, 255, 255)
RED = (225, 0, 50)
GREEN = (0, 102, 0)
GREEN1 = (0, 204, 0)
BLUE = (0, 255, 225)
BLACK = (0, 0, 0)
ORANGE = (255, 153, 0)

font = pygame.font.SysFont('comicsansms', 32)

win.fill(ORANGE)
pygame.display.update()

# --------------------------------------------------------------- ПРОВЕРКА НА РЕШЕНИЕ

def prov(b):
    if (b[0] == [1, 2, 3, 4]) and (b[1] == [5, 6, 7, 8]) and (b[2] == [9, 10, 11, 12]) and (b[3] == [13, 14, 15, 0]):
        return 1
    else:
        return 0

# --------------------------------------------------------------- ПРОВЕРКА НА 0

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

# --------------------------------------------------------------- СОСТАВЛЕНИЕ

s = 16
for i in range(0, 4):
    for j in range(0, 4):
        x = random.randrange(0, s)
        field[i][j] = st.pop(x)
        s -= 1

# --------------------------------------------------------------- ПРОВЕРКА

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

# --------------------------------------------------------------- ИСПРАВЛЕНИЕ

if (s % 2) != 0:
    if (field[0][0] != 0) and (field[0][1] != 0):
        x = field[0][0]
        field[0][0] = field[0][1]
        field[0][1] = x
    else:
        x = field[1][0]
        field[1][0] = field[1][1]
        field[1][1] = x


# --------------------------------------------------------------- ОТРИСОВКА

def otr():
    win.fill(ORANGE)
    for i in range(0,4):
        for j in range(0,4):
            if field[i][j] != 0:
                Text = font.render(str(field[i][j]), True, WHITE, GREEN1)
                x = 15 + j*(80 + 5)
                y = 15 + i*(80 + 5)
                if (field[i][j] >= 10) and (field[i][j] != 11):
                    pygame.draw.rect(win, GREEN, (x, y, 80, 80))
                    pygame.draw.rect(win, GREEN1, (x+5, y+5, 70, 70))
                    win.blit(Text, (x + 23, y + 15))
                elif field[i][j] == 11:
                    pygame.draw.rect(win, GREEN, (x, y, 80, 80))
                    pygame.draw.rect(win, GREEN1, (x + 5, y + 5, 70, 70))
                    win.blit(Text, (x + 25, y + 15))
                elif field[i][j] == 1:
                    pygame.draw.rect(win, GREEN, (x, y, 80, 80))
                    pygame.draw.rect(win, GREEN1, (x + 5, y + 5, 70, 70))
                    win.blit(Text, (x + 33, y + 15))
                else:
                    pygame.draw.rect(win, GREEN, (x, y, 80, 80))
                    pygame.draw.rect(win, GREEN1, (x + 5, y + 5, 70, 70))
                    win.blit(Text, (x + 30, y + 15))
    Text = font.render('Всего ходов: '+str(summ), True, BLACK, ORANGE)
    win.blit(Text, (20, 360))
    pygame.display.update()



# --------------------------------------------------------------- ОСНОВА

check = 0
summ = 0
while check != 1:
    st = 100
    cl = 100
    otr()
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            sys.exit()
        if i.type == pygame.MOUSEBUTTONDOWN:
            if i.button == 1:
                if i.pos[0] in range(15, 96):
                    cl = 0
                elif i.pos[0] in range(100, 181):
                    cl = 1
                elif i.pos[0] in range(185, 266):
                    cl = 2
                elif i.pos[0] in range(270, 351):
                    cl = 3

                if i.pos[1] in range(15, 96):
                    st = 0
                elif i.pos[1] in range(100, 181):
                    st = 1
                elif i.pos[1] in range(185, 266):
                    st = 2
                elif i.pos[1] in range(270, 351):
                    st = 3

    if (st >= 0) and (st <= 3) and (cl >= 0) and (cl <= 3) and (field[st][cl] != 0):

        if string(field, st) != 5:  # ЕСЛИ НОЛЬ В СТРОКЕ
            pos = string(field, st)
            if pos > cl:
                for j in range(pos, cl, -1):
                    field[st][j] = field[st][j - 1]
                field[st][cl] = 0
                summ += 1
                check = prov(field)
            else:
                for j in range(pos,cl):
                    field[st][j] = field[st][j + 1]
                field[st][cl] = 0
                summ += 1
                check = prov(field)

        elif column(field, cl) != 5:  # ЕСЛИ НОЛЬ В СТОЛБЦЕ
            pos = column(field, cl)
            if pos > st:
                for i in range(pos, st, -1):
                    field[i][cl] = field[i - 1][cl]
                field[st][cl] = 0
                summ += 1
                check = prov(field)
            else:
                for i in range(pos,st):
                    field[i][cl] = field[i + 1][cl]
                field[st][cl] = 0
                summ += 1
                check = prov(field)

otr()
font1 = pygame.font.SysFont('comicsansms', 24)
Text = font1.render('ГОЛОВОЛОМКА РЕШЕНА!', True, BLACK, BLUE)
win.blit(Text, (28, 123))
if (summ >= 10) and (summ < 100):
    Text = font1.render('Всего ходов: ' + str(summ), True, BLACK, BLUE)
    win.blit(Text, (92, 207))
elif summ >= 100:
    Text = font1.render('Всего ходов: ' + str(summ), True, BLACK, BLUE)
    win.blit(Text, (88, 207))
else:
    Text = font1.render('Всего ходов: ' + str(summ), True, BLACK, BLUE)
    win.blit(Text, (100, 207))
pygame.display.update()

while 1:
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            sys.exit()
    pygame.time.delay(20)