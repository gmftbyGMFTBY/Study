def neighbor1(pb,s,target):
    """Computation of the neighbors of s
    The neighbors of s are provided by swapping two consecutive elements s[j] and s[j+1]
    Input:  pb = list of (p1,p2,d) an instance of the pb
            s: a permutation of [0, 1, ..., n-1]
            target: the value to improve (probably tbar(s))
    Output: the neighbors are computed.
            if the best one is better than s, then (bestneighbor, its tbar) is returned
            else (s,-1) is returned."""
    n=len(s)
    tbarbest=target
    for j in range(1,n): # from 1 to n-1
        (s[j],s[j-1]) = (s[j-1],s[j]) # swap  
        tb = tbar(pb,s)
        if (tb < tbarbest):
            tbarbest = tb
            bestn = s[:]
        (s[j],s[j-1]) = (s[j-1],s[j]) # restore s
    if (tbarbest < target):
        return (bestn, tbarbest)
    else: 
        return (s,-1)

def neighbor2(pb,s,target):
    """Computation of the neighbors of s
    The neighbors of s are provided by swapping two elements s[j1] and s[j2]
    with 0 <= j1 < j2 <= n-1
    Input:  pb = list of (p1,p2,d) an instance of the pb
            s: a permutation of [0, 1, ..., n-1]
            target: the value to improve (probably tbar(s))
    Output: the neighbors are computed.
            if the best one is better than s, then (bestneighbor, its tbar) is returned
            else (s,-1) is returned."""
    n=len(s)
    tbarbest=target
    for j1 in range(n-1): # from 1 to n-2
        for j2 in range(j1+1,n): # from j1+1 to n-1
            (s[j1],s[j2]) = (s[j2],s[j1]) # swap of jobs 
            tb = tbar(pb,s)
            if (tb < tbarbest):
                tbarbest = tb
                bestn = s[:]
            (s[j1],s[j2]) = (s[j2],s[j1]) # restore of s
    if (tbarbest < target):
        return (bestn, tbarbest)
    else: 
        return (s,-1)

def neighbor3(pb,s,target):
    """Computation of the neighbors of s
    The neighbors of s are provided by permuting 3 elements s[j1], s[j2] and s[j3]
    with 0 <= j1 < j2 < j3 <= n-1
    Input:  pb = list of (p1,p2,d) an instance of the pb
            s: a permutation of [0, 1, ..., n-1]
            target: the value to improve (probably tbar(s))
    Output: the neighbors are computed.
            if the best one is better than s, then (bestneighbor, its tbar) is returned
            else (s,-1) is returned."""
    n=len(s)
    tbarbest=target
    for j1 in range(n-2): # 0 <= j1 <= n-3
        for j2 in range(j1+1,n-1): # j1+1 <= j2 <= n-2
            for j3 in range(j2+1,n): # j2+1 <= j3 <= n-1
                (s[j1],s[j2],s[j3]) = (s[j2],s[j3],s[j1]) # perm of jobs 
                tb = tbar(pb,s)
                if (tb < tbarbest):
                    tbarbest = tb
                    bestn = s[:]
                (s[j1],s[j2],s[j3]) = (s[j2],s[j3],s[j1]) # other perm of jobs 
                tb = tbar(pb,s)
                if (tb < tbarbest):
                    tbarbest = tb
                    bestn = s[:]
                (s[j1],s[j2],s[j3]) = (s[j2],s[j3],s[j1]) # restore of jobs 
    if (tbarbest < target):
        return (bestn, tbarbest)
    else: 
        return (s,-1)

def ebsr(pb,s,target):
    """Computation of the neighbors of s
    The neighbors of s are provided by ebsr. With 1 <= k1 < k2 <= n-1
    t(k1) = s(k2)
    for j in k1+1..k2, t(j) = s(j-1)
    for j < k1 or j > k2, t(j) = s(j)
    Input:  pb = list of (p1,p2,d) an instance of the pb
            s: a permutation of [0, 1, ..., n-1]
            target: the value to improve (probably tbar(s))
    Output: the neighbors are computed.
            if the best one is better than s, then (bestneighbor, its tbar) is returned
            else (s,-1) is returned."""
    n=len(s)
    tbarbest=target
    for k2 in range(n-1,0,-1): # n-1 >= k2 >= 1
        for k1 in range(k2-1,-1,-1): # k2-1 >= k1 >= 0
            (s[k1+1],s[k1]) = (s[k1],s[k1+1])
            tb = tbar(pb,s)
            if (tb < tbarbest):
                tbarbest = tb
                bestn = s[:]
        for k1 in range(k2): # 0 <= k1 <= k2-1
            (s[k1+1],s[k1]) = (s[k1],s[k1+1])
    if (tbarbest < target):
        return (bestn, tbarbest)
    else: 
        return (s,-1)

def efsr(pb,s,target):
    """Computation of the neighbors of s
    The neighbors of s are provided by efsr. With 1 <= k1 < k2 <= n-1
    t(k2) = s(k1)
    for j in k1..k2-1, t(j) = s(j+1)
    for j < k1 or j > k2, t(j) = s(j)
    Input:  pb = list of (p1,p2,d) an instance of the pb
            s: a permutation of [0, 1, ..., n-1]
            target: the value to improve (probably tbar(s))
    Output: the neighbors are computed.
            if the best one is better than s, then (bestneighbor, its tbar) is returned
            else (s,-1) is returned."""
    n=len(s)
    tbarbest=target
    for k1 in range(n-1): # 0 <= k1 <= n-2
        for k2 in range(k1+1,n): # k1+1 <= k2 <= n-1
            (s[k2-1],s[k2]) = (s[k2],s[k2-1])
            tb = tbar(pb,s)
            if (tb < tbarbest):
                tbarbest = tb
                bestn = s[:]
        for k2 in range(n-1,k1,-1): # n-1 >= k2 >= k1+1
            (s[k2-1],s[k2]) = (s[k2],s[k2-1])
    if (tbarbest < target):
        return (bestn, tbarbest)
    else: 
        return (s,-1)



