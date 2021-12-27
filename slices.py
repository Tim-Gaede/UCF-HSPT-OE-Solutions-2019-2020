#solution to Slices by David Harmeyer

#Current issues:
#samples don't match the problem description. Problem statement says it is okay
#to be one away, samples say oppisite
#Weak data: only one case tests off-by-one errors, and it is a border case.
#someone could easily get part of it wrong, but start their counters at level 1,
#and get it correct when it should be incorrect.
T=int(input());

for tt in range(0, T):
  n,k=map(int, input().split());
  eHatesT=False;
  tHatesE=False;
  e,t=0, 0;
  for i in range(0, n):
    solver=input().split()[0];
    if (solver=="Kelly"):
      #what kind of self-respecting programming language doesn't have the ++ operator?!
      e+=1;
    else:
      t+=1;
    if e>t+k:
      tHatesE=True;
    if t>e+k:
      eHatesT=True;
  if eHatesT and tHatesE:
    print("Their friendship is doomed");
  elif eHatesT:
    print("Kelly hates Jim");
  elif tHatesE:
    print("Jim hates Kelly");
  else:
    print("Everything is good");
    



