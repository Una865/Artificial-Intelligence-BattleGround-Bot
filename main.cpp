import pygame as pg
import sys
import time
import math
import random

import requests

SERVER_IP = 'best2.aibg.best'
MY_ID = '1'
GAME_ID = '3663'

pg.init()

width = 600

size = width, width

screen = pg.display.set_mode(size)
print(requests.get(f'http://{SERVER_IP}:9080/train?gameId={GAME_ID}&playerId={MY_ID}&position={MY_ID}'))

colors = [(40,40,40), (0,255,255), (128,128,0), (0,0,255), (128,128,0), (255,255,0), (255,0,0), (40,120,20), (0,255,0)]

map = {

}

for q in range(-14,15):
        for s in range(-14,15):
            for r in range(-14,15):
                map[(q,r,s)] = 0


def cube_distance(a, b):
    return (abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2])) / 2

moves = {
    (0,-1,1)
}

dirs = [
    (0,1,-1, 'nw'),
    (0,-1,1, 'se'),
    (1,0,-1, 'ne'),
    (-1,0,1, 'sw'),
    (-1,1,0, 'w'),
    (1,-1,0, 'e'),
]

money_goals = ['200' , '300' , '200' , '300', '150']
money_cnt = 0

req = requests.get(f'http://{SERVER_IP}:9080/game/play?gameId={GAME_ID}&playerId={MY_ID}')
print(req.json())

while 1:
    data = req.json()
    tiles = data['map']['tiles']

    flag = (data['currFlag']['q'],data['currFlag']['s'],data['currFlag']['r'])

    player = (data[f'player{MY_ID}'])
    playerPos = (player['q'], player['s'], player['r'])

    print(player['health'] + player['cannons'])
    if(player['health'] > 700 and player['cannons']==250):
        for i in range(1,5):
            if(i==int(MY_ID)):
                continue
            else:
                if(data[f'player{i}']):
                    enemy = data[f'player{i}']
                    if(enemy['health'] <= 0):
                        continue
                    enemyh = int(enemy['health'])
                    playerc = int(player['cannons'])
                    enemyc = int(enemy['cannons'])
                    playerh = int(player['health'])
                    if (enemyh/playerc < playerh/enemyc) or (enemyh//playerc == playerh//enemyc and int(player['money'])<int(enemy['money'])):
                        flag = (enemy['q'],enemy['s'],enemy['r'])
                        print('enemy locked ', flag)


    for q in range(-14,15):
        for s in range(-14,15):
            for r in range(-14,15):
                map[(q,r,s)] = 0

    shops = []

    for l in tiles:
        for e in l:
            if(e):
                if(e['tileType'] == 'NORMAL'):
                    if(not e['entity']):
                        map[(e['q'],e['s'],e['r'])] = 1
                    elif(e['entity']['type'] == 'WHIRLPOOL' or e['entity']['type']==None):
                        map[e['q'],e['s'],e['r']] = 2
                    else:
                        map[e['q'],e['s'],e['r']] = 6
                elif(e['tileType'] == 'ISLAND'):
                    if(e['entity']['type'] == 'ISLANDFLAG'):
                        map[e['q'],e['s'],e['r']] = 5
                    elif(e['entity']['type'] == 'ISLANDSHOP'):
                        map[e['q'],e['s'],e['r']] = 8
                        shops.append((e['q'],e['s'],e['r']))
                else:
                    map[(e['q'],e['s'],e['r'])] = 4
    
    next_move = 'w'
    mindis = 999999

    minshopdis = 99999
    minshopindex = -1

    for i,shop in enumerate(shops):
        print('distance shop: ',cube_distance(playerPos, shops[minshopindex]))
        if(cube_distance(playerPos, shops[minshopindex])<minshopdis):
            minshopdis = cube_distance(playerPos, shops[minshopindex])
            minshopindex = i
    
    print(shops, money_cnt)
    print(player['money'], player['potNums'])

    if(int(player['health']) < int(player['maxHealth']) and int(player['potNums']) > 0):
        next_move = (0,0,0,'up')
    elif(minshopindex > -1 and int(player['money']) >= int(money_goals[money_cnt])):
        if(minshopdis==1):
            if(money_cnt < 2):
                next_move = (0,0,0,'buy-HULL')
            elif(money_cnt < 4):
                next_move = (0,0,0,'buy-CANNONS')
            else:
                if(int(player['potNums']) < 2):
                    next_move = (0,0,0,'buy-POTION')
        else:
            if(int(player['money']) < int(money_goals[money_cnt]) or int(player['potNums'])==2):
                pass
            else:
                if(random.random() < 0.2):
                    random.shuffle(dirs)
                for dir in dirs:
                    q = playerPos[0]+dir[0]
                    s = playerPos[1]+dir[1]
                    r = playerPos[2]+dir[2]
                    if(abs(q)>14 or abs(s)>14 or abs(r)>14):
                        continue
                    if(map[(q,s,r)] and (map[(q,s,r)]==5 or map[(q,s,r)]==2)):
                        continue
                    dis = cube_distance((q,s,r), (shops[minshopindex][0],shops[minshopindex][1], shops[minshopindex][2]))
                    if(dis < mindis):
                        next_move = dir
                        mindis = dis
    print(next_move)
    if(next_move=='w'):
        mindis=999999
        if(random.random() < 0.2):
            random.shuffle(dirs)
        for dir in dirs:
            q = playerPos[0]+dir[0]
            s = playerPos[1]+dir[1]
            r = playerPos[2]+dir[2]
            if(abs(q)>14 or abs(s)>14 or abs(r)>14):
                continue
            if(map[(q,s,r)] and (map[(q,s,r)]==5 or map[(q,s,r)]==2 or map[(q,s,r)]==8)):
                continue
            dis = cube_distance((q,s,r), flag)
            if(dis < mindis):
                next_move = dir
                mindis = dis

    maxdis=-999
    for i in range(1,7):
        if(i==int(MY_ID)):
            continue
        else:
            if(i < 5 and data[f'player{i}']):
                enemy = data[f'player{i}']
                if(enemy['health'] <= 0):
                    continue
                map[enemy['q'], enemy['s'], enemy['r']] = 6
                if(cube_distance(playerPos, (enemy['q'], enemy['s'], enemy['r']))<=2):
                    print(cube_distance(playerPos, (enemy['q'], enemy['s'], enemy['r'])))
                    enemyid=enemy['id']
                    next_move = (0,0,0,f'atk-{enemyid}')
                if(cube_distance(playerPos, (enemy['q'], enemy['s'], enemy['r']))>3):
                    continue
                if (int(player['health'])/int(enemy['cannons']) > int(enemy['health'])/int(player['cannons'])) or (( int(player['health'])//int(enemy['cannons']) == int(enemy['health'])//int(player['cannons']) ) and int(enemy['money']) > int(player['money'])):
                    continue
                for dir in dirs:

                    q = playerPos[0]+dir[0]
                    s = playerPos[1]+dir[1]
                    r = playerPos[2]+dir[2]
                    if(abs(q)>14 or abs(s)>14 or abs(r)>14):
                        continue
                    if(map[(q,s,r)] and (map[(q,s,r)]==5 or map[(q,s,r)]==2)):
                        continue
                    dis = cube_distance((q,s,r), (enemy['q'], enemy['s'], enemy['r']))
                    if(dis > maxdis):
                        next_move = dir
                        maxdis = dis
            elif(i > 4 and data[f'npc{i-4}']):
                enemy = data[f'npc{i-4}']
                if(enemy['health'] <= 0):
                    continue
                map[enemy['q'], enemy['s'], enemy['r']] = 7
                if(cube_distance(playerPos, (enemy['q'], enemy['s'], enemy['r']))<=2):
                    print(cube_distance(playerPos, (enemy['q'], enemy['s'], enemy['r'])))
                    enemyid=enemy['id']
                    print(enemyid)
                    next_move = (0,0,0,f'atk-{enemyid}')
                    print(next_move)
                    break
                for dir in dirs:
                    if(player['health'] < 0.4*player['maxHealth']):
                        continue
                    q = playerPos[0]+dir[0]
                    s = playerPos[1]+dir[1]
                    r = playerPos[2]+dir[2]
                    if(abs(q)>14 or abs(s)>14 or abs(r)>14):
                        continue
                    if(map[(q,s,r)] and (map[(q,s,r)]==5 or map[(q,s,r)]==2)):
                        continue
                    dis = cube_distance((q,s,r), (enemy['q'], enemy['s'], enemy['r']))
                    if(dis > maxdis):
                        next_move = dir
                        maxdis = dis
                
    if(next_move[3] == 'buy-HULL' or next_move[3]=='buy-CANNONS'):
        money_cnt += 1
    req = requests.get(f'http://{SERVER_IP}:9080/doAction?gameId={GAME_ID}&playerId={MY_ID}&action={next_move[3]}')
    print(next_move[3])

    for event in pg.event.get():
        if event.type == pg.QUIT: 
            sys.exit()

    map[flag] = 3

    for q in range(-14,15):
        for s in range(-14,15):
            for r in range(-14,15):
                if q+r+s!=0:
                    continue
                pg.draw.circle(screen, colors[map[(q,s,r)]], (300+5*1.73205080757*q-5*1.73205080757*s,300-(q*5*1.73205080757+s*5*1.73205080757-10*r)), 5)

    pg.display.flip()

    
