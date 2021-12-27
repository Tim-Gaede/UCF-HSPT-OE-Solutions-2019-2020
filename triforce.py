from sys import stdin

numQueries=int(stdin.readline())
for i in range(1,numQueries+1):
    #Read input for testcase
    s,r,p=stdin.readline().split()
    s=float(s)
    r=int(r)
    p=int(p)

    #Compute the area of an equilateral triangle
    #Area of a triangle is base*height, and 
    #height = base*sqrt(3)/2
    area=s*s/4*(3**.5)
    #Each recursive step for the pattern has 3/4 of the original area.
    #This is evident if you look at the sample, going from 0 to 1 triforce.
    #So, we just multiply by 3/4 each time we recurse. The area will
    #continue to decrease
    area*=pow(3.0/4,r)   
    #Once we have our final area, multiply by price
    area*=p
    
    #Print the rounded area
    print("Triforce #%d: %.2f"%(i,area))
    numQueries-=1
