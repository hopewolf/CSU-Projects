import subprocess as sp
import sys
array = ['200','2000','20000','200000']
output = [0,0,0,0,0]
print('2chain00')
for G in array:
    for i in range(0,5):
        output[i] = sp.call(['./MM2chain00',G])
    print('\n')
    
print('2chain01')
for G in array:
    for i in range(0,5):
        output[i] = sp.call(['./MM2chain01',G])
    print('\n')
