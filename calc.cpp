/**
Solution to UCF 2019 Div2 Problem 1 - Calculator Game "calc"
    By Dylan Lyon
*/

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <queue>

using namespace std;

int tooBig = 99999999;
int impossibleNumber = tooBig+1;

struct button{
    char type;
    int dat1,dat2;
};

/**
Returns the result of pressing a button given the button
and the integer currently on screen. If it's an impossible
operation (either too big or a fraction or no such digit "a"
for 'T' buttons) this function returns null.
*/
int pressButton(struct button press, int input){
    int result = impossibleNumber;
    switch(press.type){
    case 'A':{
        if(abs(input+press.dat1) <= tooBig)
            result = input+press.dat1;
    }break;
    case 'S':{
        if(abs(input-press.dat1) <= tooBig)
            result = input-press.dat1;
    }break;
     case 'M':{
        if(abs(input*press.dat1) <= tooBig)
            result = input*press.dat1;
    }break;
     case 'D':{
        if(input%press.dat1 == 0 && abs(input/press.dat1) <= tooBig)
            result = input/press.dat1;
    }break;
     case 'T':{
        // Turn input into a positive number, saving the sign
        int sign = 1;
        if(input < 0)
            sign = -1;
        input = abs(input);

        int tmp = input, numdig = 0;
        // Count the number of digits in input
        while(tmp>0){
            tmp/=10;
            numdig++;
        }
        // Replace the digits of input
        tmp = input;
        result = 0;
        for(int i=0;i<numdig;i++){
            int dig = tmp%10;
            if(dig == press.dat1){
                dig = press.dat2;
            }
            result += (int)(pow(10, i)+.001) * (dig);
            tmp /= 10;
        }
        result *= sign;
    }break;
     case 'P':{
        // Turn input into a positive number, saving the sign
        int sign = 1;
        if(input < 0)
            sign = -1;
        input = abs(input);
        // You need to abs input because appending by multiplying by 10
        //  then adding the new digit doesn't work for negatives
        if(abs(input*10+press.dat1) <= tooBig)
            result = (input*10+press.dat1)*sign;
    }break;
    }
    return result;
}

int main(void){
    // Number of levels to test
    int numLevels;
    cin >> numLevels;

    int level;

    for(level=1; level<= numLevels; level++){
        // Read input
        int s,t,b,n;
        scanf("%d %d %d %d",&s,&t,&b,&n);
        //cin >> s >> t >> b >> n;

        // The buttons we're allowed to use
        struct button *buttons = (struct button *)malloc(n*sizeof(button));
        for(int i=0;i<n;i++){
            struct button tmp;
            char *typestring = (char *)malloc(20);
            scanf("%s",typestring);
            tmp.type = typestring[0];
            scanf("%d",&(tmp.dat1));
            if( tmp.type == 'T' ) // this button type has two inputs
                scanf("%d",&(tmp.dat2));
            else
                tmp.dat2 = impossibleNumber;
            buttons[i] = tmp;
        }

        // We're going to start a bfs from value 's' with distance 0
        queue<int *> que;

        int *seed = (int *)malloc(2*sizeof(int));
        seed[0] = s;
        seed[1] = 0;
        que.push(seed);

        bool foundIt = false;

        while(!que.empty()){
            // Pull from the que
            int *tmp = que.front();

            // The number we're at,
            //  and how many moves it took to get there
            int value = tmp[0],
                distance = tmp[1];

            /*
            if(level == 4){
                cout << value << "\n";
            }
            */

            que.pop();
            // Always free!!!
            free(tmp);

            // We found the number or we're too far,
            //  continue only to free memory
            if( distance > b || foundIt)
                continue;
            // We found the number at b presses
            if(value == t && distance == b){
                foundIt = true;
                continue;
            }

            for(int i=0;i<n;i++){
                int nxt = pressButton(buttons[i],value);
                // If the next position is valid, we add it to the que
                if( nxt != impossibleNumber ){
                    int *nxtState = (int *)malloc(2*sizeof(int));
                    nxtState[0] = nxt;
                    nxtState[1] = distance+1;
                    que.push(nxtState);
                }
            }
        }

        // Print based on foundIt
        printf("Level #%d: %s\n",level, (foundIt) ? "It can be done" : "You should give up" );

    }
}
