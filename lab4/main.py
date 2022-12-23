"""LAB 4 tester 
1. save this file (main.py) to ECF, in the same folder as your lab3 parser.exe
2. run this file by typing:
     python3 main.py
"""




from random import randint
tricky_cases = """
shape sqr rectangle 10 10 30 40

draw
shape sqr rectangle 10 10 30 40
draw
shape s1 rectangle 10 10 30 0
draw
shape s2 rectangle 10 10 30 0
draw
shape sqr ellipse 10 10 30 0
draw
shape s3 ellipse 10 10 30 0
 shape trig triangle 60 80 30 50
  shape circ ellipse 30 40 10 10
draw
group no_corners
 draw
move circ no_corners
draw
delete no_corners
delete move
draw
delete pool
shape pool rect 1 1 1 1
shape shape rectangle 1 1 1 1
shape rectangle bla  1 1 1 1
shape my_circle ellipse 50 65 20 20
shape my_square rectangle 100 150 60 60
shape a_circle ellipse 120 200 40 40
shape my_triangle triangle 40 75 90 90
draw
group my_first_group
shape my_rectangle rectangle 100 275 90 180
shape my_rectangle triangle 70 50 10 5
shape second_triangle triangle 70 50 10 5
draw
move my_triangle my_first_group
move my_circle my_first_group
draw
delete my_first_group
draw
delete pool
delete abc
delete abc
delete abc
shape bbb rectangle 1 1 1 1
shape bbb rectangle 1 1 1 1
shape bb2 rectangle 1 1 1 1
draw

shape bb3 rectangle 1 1 1 1
draw

shape bb4 rectangle 1 1 1 1
group new
group n2
group n3
group n4
draw
move bb2 n3
move bb3 n2
move bb2 n4
move bb2 n4
move bb2 n4
move bb2 n4
move bb2 n4
draw

""".strip()

result = []
result += list(tricky_cases.split('\n'))

for i in range(200):#add new shapes
  cmd = f"shape s{i} rectangle 10 {i} 30 40"
  result.append(cmd)

result.append("draw")
for i in range(200):#add new group
  cmd = f"group g{i}"
  result.append(cmd)
result.append("draw")
for i in range(200):#move
  cmd = f"move s{i} g{i}"
  result.append(cmd)
result.append("draw")
for i in range(20,199,7):#add new shapes
  cmd = f"shape s{i} rectangle 10 {i} 30 40"
  result.append(cmd)
result.append("draw")
for i in range(0,199,7):#move
  for j in range(0,199,11):
    cmd = f"move s{(i*j)%200} g{i+j} "
    result.append(cmd)
result.append("draw")

for i in range(3,222,17):#add new group
  for j in range(1,222,13):
    cmd = f"move s{i} g{j} "
    result.append(cmd)
result.append("draw")

for i in range(200):#add new shapes
  cmd = f"shape ss{i} rectangle 10 {i} 30 40"
  result.append(cmd)
result.append("draw")

for i in range(200):#add new shapes
  cmd = f"move ss{i} g{i%4}"
  result.append(cmd)
result.append("draw")
result.append("delete g2")
result.append("draw")

for i in range(3,222,16):#delete shape
    cmd = f"delete s{i}"
    result.append(cmd)
result.append("draw")
for i in range(0,222,2):#add new group
    cmd = f"delete g{i}"
    result.append(cmd)
result.append("draw")

result*=2

scoutner=0
def shape(i,j):
  global scoutner
  scoutner+=1
  return  f"shape s{i} rectangle 10 {j} 30 {scoutner}"
def group(i,j):
  return  f"group g{i} "
def move(i,j):
  if i%2:
    return  f"move s{i} g{i}"
  return  f"move g{i} s{i}"
def delete(i,j):
  if i%2:
    return  f"delete g{i}"
  return  f"delete s{i}"

for funclist in [ [group,move,shape], [group,move,shape,delete]]:
  for i in range(9991):
    for f in funclist:
      result.append(f(randint(0,9999),randint(0,9999)))
  result.append("draw")
  for i in range(999):
    for f in funclist:
      result.append(f(999+randint(0,9999),999+randint(0,9999)))
  for i in range(999):
    for f in funclist:
      result.append(f(randint(0,9999),999+randint(0,9999)))
  for i in range(999):
    for f in funclist:
      result.append(f(999+randint(0,9999),randint(0,9999)))
  for i in range(999):
    for f in funclist:
      result.append(f(randint(0,99),randint(0,99)))
  result.append("draw")
print(f"finished generating {len(result)} test cases. Testing will take about 3 to 10 minutes")
result.append('EOF-MARKER')

header = "~ece244i/public/Parser.exe <<EOF-MARKER\n"
with open("refs.sh", 'w') as f:
  f.write(header + "\n".join(result))
  
header = "./Parser.exe <<EOF-MARKER\n"
with open("yours.sh", 'w') as f:
  f.write(header + "\n".join(result))

header = "valgrind --leak-check=full ./Parser.exe <<EOF-MARKER\n"
with open("yoursvalgrind.sh", 'w') as f:
  f.write(header + "\n".join(result))

import subprocess

subprocess.run(['make'])
a = subprocess.check_output('sh refs.sh'.split())
b = subprocess.check_output('sh yours.sh'.split())
a = a.decode().split(">")
b = b.decode().split(">")
a.remove("")
b.remove("")
'''
with open("aa") as f:
  a=f.read().split("\n")
with open("your-solution") as f:
  b=f.read().split("\n")
'''
counter = 0
a = [_.strip() for _ in a]
b = [_.strip() for _ in b]

for i in range(min(len(a), len(b), len(result))):
  if a[i].strip() != b[i].strip():
    counter += 1
    print()
    print("Error in line", i)
    print("input:", result[i])
    print("ref output:  ", a[i].strip())
    print("your output: ", b[i].strip())
print("outputs thats are missing (if any):", list(set(b) - set(a)))
print(len(a), len(b), len(result))
print("Are the two outputs same:", a == b)
print("Total differences: found", counter, "differences out of", len(result),"trials")
print("running valigrind.... (takes about 30min to 90min?")
subprocess.call('sh yoursvalgrind.sh &>valgrindresult.txt',shell=True)
with open("valgrindresult.txt", 'r') as f:
  f = f.read()
  i = f.index("HEAP SUMMARY:")
  print(f[i:]) 
