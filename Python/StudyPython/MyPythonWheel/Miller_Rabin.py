def quick_mod(a,b,c):
    result = 1
    while b!=0:
        if b&1:result = (result*a)%c
        b >>= 1
        a = (a*a)%c
    return result

def Miller_Rabin(n):
    t=0
    p=n-1
    while (p&1)==0:
        t+=1
        p>>=1
    list_atom=[2,3,7,61,23251]
    for var in list_atom:
        x=quick_mod(var,p,n)
        for i in range(t):
            y=quick_mod(x,2,n)
            if y==1 and x!=1 and x!=n-1:
                return False
            x=y
        if x!=1:
            return False
        else:return True
a = int(raw_input())
print(Miller_Rabin(a))
