/*
Solution to Room by David Harmeyer himself!

The inspiration for the problem was that I asked for a prime-numbered
room to study in in the library and was given room number 16. True story.

Anyway, one method of solving this problem is to binary search the base
we are looking for. If we interprit the room we are given in too large a base,
then we will get a room number that is bigger than what we are looking for.
If we interpret it in a base that is too small, we will get a base too small.

In fact, you can take advantage of the fact that the number you are given doesn't have
that many digits at all to use a solution that doesn't use this binary search,
but that is a bit more complicated and unnecissary.

The one part to be careful with when binary searching here is that you
don't want to overflow longs when calculating something with a large base.
I handle this by first checking to see if I will be way above any feasable answer
with doubles, and then using more precise 64 bit long longs (equivalent to longs in java)
to get exactly the right answer once I am sure I won't overflow.

*/

#include <iostream>

using namespace std;
typedef long long ll;

bool baseTooBig(ll given, ll target, ll base) {
  double max=2e18;
  int digits[7];
  int takeDigitsOf=given;
  for (int i=0; i<7; i++) {
    digits[i]=takeDigitsOf%10;
    takeDigitsOf/=10;
  }
  ll basePows[7];
  basePows[0]=1;
  for (int i=1; i<7; i++) {
    if (basePows[i-1]==-1||basePows[i-1]*(double)base>max)
      basePows[i]=-1;
    else
      basePows[i]=basePows[i-1]*base;
  }
  ll total=0;
  for (int i=0; i<7; i++) {
    if (total==-1||total+(double)digits[i]*(double)basePows[i]>max
        ||(digits[i]!=0&&basePows[i]==-1))
      total=-1;
    else
      total+=digits[i]*basePows[i];
  }
  if (total==-1)
    return true;
  return total>target;
}

int main() {
    int T;
    cin>>T;
    for (int tt=1; tt<=T; tt++) {
      ll given, target;
      cin>>given>>target;
      ll low=10, hi=1000000000000000000;
      while (low!=hi) {
        ll mid=(low+hi+1)/2;
        if (baseTooBig(given, target, mid))
          hi=mid-1;
        else
          low=mid;
      }
      cout<<"Hotel Visit #"<<tt<<": Base "<<low<<"\n";
    }
}
