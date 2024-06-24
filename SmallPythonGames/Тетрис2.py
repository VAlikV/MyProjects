import pygame as pg
import sys
import copy
import random
pg.init()

# Цвета

WHITE = (255,255,255)
GRAY = (50, 50, 50)
RED = (225, 0, 50)
GREEN = (0, 225, 0)
BLUE = (0, 0, 225)
BLACK = (0, 0, 0)
ORANGE = (253, 106, 2)
PURP = (148, 0, 211)
YEL = (255, 255, 0)
VIO = (75, 0, 130)

palette = [RED, GREEN, BLUE, ORANGE, PURP, YEL, VIO]

# Дисплей

W = 10
H = 20
box = 40
win = pg.display.set_mode((box * W + 300, box * H))
pg.display.set_caption('Тетрис')
win.fill(BLACK)
pg.display.update()
limY = 1000
cY = 0

# Текст

font = pg.font.SysFont('comicsansms', 32)
Next = font.render('Next:', True, RED, None)

# Сетка

grid = [pg.Rect(x * box, y * box, box, box) for x in range(0, W) for y in range(0, H)]

# Поле

field = [[0 for j in range(0, W)] for i in range(0, H)]

# Отрисовка поля

def Pole(field1):
    for i in range(0, H):
        for j in range(0, W):
            if field1[i][j] != 0:
                pol = (j*box + 2, i*box + 2, box - 4, box - 4)
                pg.draw.rect(win, palette[field1[i][j]-1], pol)

# Проверка

def check(field1, figure1):
    for i in range(0, 4):
        if (figure1[i][1] >= W) or (figure1[i][1] < 0):
            return True
        elif (figure1[i][0] >= H) or (figure1[i][0] < 0) or (field1[figure1[i][0]][figure1[i][1]] != 0):
            return True

# Удаление собранного ряда

def Done(field1):
    for i in range(0, H):
        if field1[i].count(0) == 0:
            field1[i] = field1[i-1]
            for j in range(i-1, 0, -1):
                field1[j] = field1[j-1]
            field1[0] = [0 for i in range(0, W)]
            return True

# Проигрыш

def GameOver(field1):
    if field1[0].count(0) != 10:
        return False
    return True

# Фигуры

figsP = [[[0, 4], [0, 3], [0, 5], [0, 6]],
        [[1, 5], [0, 5], [1, 4], [2, 5]],
        [[1, 5], [0, 4], [1, 4], [2, 5]],
        [[1, 5], [0, 4], [0, 5], [2, 5]],
        [[1, 4], [0, 5], [1, 5], [2, 4]],
        [[0, 4], [0, 5], [1, 4], [1, 5]],
        [[1, 4], [0, 4], [0, 5], [2, 4]]]

# Основа

s = 0
z1 = random.randrange(0, 7)

while GameOver(field):

    loop = True
    z = z1
    z1 = random.randrange(0, 7)
    figureNext = copy.deepcopy(figsP[z1])
    figure = copy.deepcopy(figsP[z])
    field_old = copy.deepcopy(field)

    while loop:
        win.fill(BLACK)
        [pg.draw.rect(win, GRAY, i, 1) for i in grid]

        # Отрисовка фигурки

        for i in range(0, 4):
            y, x = figure[i]
            pol = (x * box + 2, y * box + 2, box - 4, box - 4)
            pg.draw.rect(win, palette[z], pol)

        # Отрисовка следующей фигурки

        for i in range(0, 4):
            if (z1 != 0) and (z1 != 5):
                y, x = figureNext[i]
                pol1 = (x * box + 352, y * box + 152, box - 4, box - 4)
                pg.draw.rect(win, palette[z1], pol1)
                pg.draw.rect(win, GRAY, (450, 120, 200, 180), 2)
            elif (z1 == 0):
                y, x = figureNext[i]
                pol1 = (x * box + 352, y * box + 192, box - 4, box - 4)
                pg.draw.rect(win, palette[z1], pol1)
                pg.draw.rect(win, GRAY, (450, 120, 200, 180), 2)
            else:
                y, x = figureNext[i]
                pol1 = (x * box + 352, y * box + 172, box - 4, box - 4)
                pg.draw.rect(win, palette[z1], pol1)
                pg.draw.rect(win, GRAY, (450, 120, 200, 180), 2)

        # Регистрация нажатий

        rotate = False
        dx = 0
        for i in pg.event.get():
            if i.type == pg.QUIT:
                sys.exit()
            if i.type == pg.KEYDOWN:
                if i.key == pg.K_RIGHT:
                    dx = 1
                elif i.key == pg.K_LEFT:
                    dx = -1
                if i.key == pg.K_DOWN:
                    limY = 75
                if i.key == pg.K_UP:
                    if z != 5:
                        rotate = True

        # Перемещение по Х

        figure_old = copy.deepcopy(figure)
        for i in range(0, 4):
            figure[i][1] += dx
            if check(field, figure):
                figure = figure_old
                break

        # Поворот

        figure_old = copy.deepcopy(figure)
        if rotate:
            for i in range(0, 4):
                x = figure[i][0] - figure[0][0]
                y = figure[i][1] - figure[0][1]
                figure[i][1] = figure[0][1] - x
                figure[i][0] = figure[0][0] + y
                if check(field, figure):
                    figure = figure_old
                    break

        # Перемещение по У

        figure_old = copy.deepcopy(figure)
        cY += 75
        if cY >= limY:
            for i in range(0, 4):
                figure[i][0] += 1
                if check(field, figure):
                    figure = figure_old
                    limY = 1000
                    for c in range(0, 4):
                        field[figure[c][0]][figure[c][1]] = z+1
                    loop = False
                    break
                cY = 0

        if Done(field):
            s += 100
        Pole(field)
        win.blit(Next, (510, 70))
        Score = font.render('Счет: ' + str(s), True, RED, None)
        win.blit(Score, (450, 700))
        pg.display.update()
        pg.time.delay(30)

font1 = pg.font.SysFont('comicsansms', 54)
Text = font1.render('_GAMEOVER!_', True, WHITE, RED)
win.blit(Text, (150, 250))
font1 = pg.font.SysFont('comicsansms', 40)
Text = font1.render('Ваш счет: ' + str(s), True, WHITE, RED)
win.blit(Text, (220, 350))
pg.display.update()

while 1:
    for i in pg.event.get():
        if i.type == pg.QUIT:
            sys.exit()
    pg.time.delay(20)