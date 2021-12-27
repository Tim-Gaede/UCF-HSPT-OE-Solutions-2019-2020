//
// Slices
// UCF Online High School Programming Contest 2019
// Jim Geist jimg@knights.ucf.edu
//
#include <cstdio>
#include <cstring>

int main()
{
    int cases;
    scanf("%d", &cases);

    while (cases--) {
	int n, k;
	scanf("%d %d", &n, &k);

	int jim = 0, kelly = 0;
	bool jimHates = false, kellyHates = false;

	char name[10];
	while (n--) {
	    int level;
	    
	    scanf("%s %d", name, &level);
	    if (strcmp(name, "Jim") == 0) {
		jim = level;
	    } else {
		kelly = level;
	    }

	    if (jim > kelly + k) {
		kellyHates = true;
	    }

	    if (kelly > jim + k) {
		jimHates = true;
	    }
	}

	if (jimHates == false && kellyHates == false) {
	    printf("Everything is good\n");
	} else if (jimHates == false && kellyHates == true) {
	    printf("Kelly hates Jim\n");
	} else if (jimHates == true && kellyHates == false) {
	    printf("Jim hates Kelly\n");
	} else if (jimHates == true && kellyHates == true) {
	    printf("Their friendship is doomed\n");
	}	
    }    
}
