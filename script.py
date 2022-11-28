import os

for i in range(1, 101):
    a = os.popen(f'diff ./casosdeteste/saida-{i:04d}.txt ./saidas/saida-{i:04d}.txt').readlines()
    if a != []:
        print(f'Diferente: saida-{i:04d}')
