#!/usr/bin/python3


def lru(pages, buf, counters):
    """Executes the LRU scheduling algorithm"""
    pgfaults = 0
    for page in pages:
        fltflag = False
        if page in buf:
            counters[buf.index(page)]=0
        else:
            fltflag = True
            pgfaults+=1
            foundflag=False
            ind = None
            for indx, val in enumerate(buf):
                if val==-1:
                    ind = indx
                    buf[ind] = page
                    foundflag=True
                    break
            if not foundflag:
                ind = counters.index(max(counters))
                buf[ind] = page
            counters[ind] = 0
        for idx, counter in enumerate(counters):
            counters[idx]+=1
        print(counters)
        print("[", end='\t')
        for i in buf:
            if i==-1:
                print("--", end='\t')
            else:
                print(i, end='\t')
        print("]", end='\t')
        if fltflag:
            print("F")
        else:
            print()
    print("The total number of page faults is: ", pgfaults, "\n")
            
            

def main():
    """Used as the main fuction"""
    pages = []
    buf = []
    counters = []
    totpgs = int(input("Enter the total number of pages:"))
    frmsz = int(input("Enter the frame size:"))
    print("Enter the pages:")
    for i in range(0, totpgs):
        pages.append(int(input()))
    for i in range(0, frmsz):
        buf.append(-1)
        counters.append(0)
    lru(pages, buf, counters)

if __name__ == '__main__':
    main()

