
w = 60
h = 40

# path = 'gosper_glider_gun.txt'
# right = 0
# down = 0

# path = 'simkin_glider_gun.txt'
# right = 10
# down = 10

# path = 'p46_gun.txt'
# right = 0
# down = 0

# path = 'glider_pusher.txt'
# right = 10
# down = 5

# path = '6bits.txt'
# right = 0
# down = 0

# path = 'bi_gun.txt'
# right = 0
# down = 0

# path = 'new_gun_1.txt'
# right = 0
# down = 0

path = 'blocker.txt'
right = 17
down = 13

f = open(path)
lines = [s.rstrip() for s in f.readlines()]

L = []
for line in lines:
  if line.find('1') == -1:
    L += [[]]
  else:
    temp = []
    for i, c in enumerate(line):
      if c == '1':
        temp.append(i)
    L += [temp]


s = ""
for i, indices in enumerate(L):
  for j in indices:
    s += f"JCW_board[{i+1+down}][{j+1+right}] = 1;\n"

# print(L)
print(s)

f.close()
