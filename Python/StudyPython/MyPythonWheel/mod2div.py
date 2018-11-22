#!/usr/bin/python3

print('This .py script was made by lantian to solve the question about the Mode in 2 Divide')
print('Inorder to get the correct answer , Please make the Number1 > Number2')

x = input("Please input the Number 1: ")
y = input("Please input the Number 2: ")

# Change the number str into the Iteration

x = list(map(lambda x : int(x) , x))
y = list(map(lambda y : int(y) , y))

# Calculate the length of the number in 2

lengthx = len(x)
lengthy = len(y)

# Save the Answer

answer = []

def get_answer(x , y):
    '''
    x and y are the the number list (x % y in 2)
    and return the Mod 2 Divide answer of the type in list
    '''
    len1 = len(x)
    len2 = len(y)
    ans = []
    if len1 < len2 :
        delta = len1 - len2
        for i in range(delta):
            x.append(0)

    for i in range(len1):
        if x[i] == y[i] : ans.append(0)
        else : ans.append(1)
    return ans

pointer = lengthy - 1   # Set the pointer to the x
new_x = x[0:lengthy]

while pointer < lengthx :
    begin = -1
    for i , j in enumerate(new_x):
        if j == 0 :
            begin += 1
        else : break
    new_x = new_x[begin + 1 : ]
    new_length = len(new_x)
    if new_length < lengthy :
        for i in range(lengthy - new_length):
            pointer += 1
            if pointer == lengthx : break
            new_x.append(x[pointer])
    if pointer == lengthx : break
    new_x = get_answer(new_x , y)

new_x = map(lambda x : str(x) , new_x)
print(''.join(new_x))
