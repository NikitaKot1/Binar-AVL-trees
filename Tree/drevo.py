import random



f = open("drevo.txt", "w")
for i in range(30):
    print(random.randint(0, 1000), file=f)
f.close()
