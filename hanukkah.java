import java.util.Scanner;

public class hanukkah
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int g = scan.nextInt();
		for (int testCase = 1; testCase <= g; testCase++)
		{
			long n = scan.nextLong();
			long a = scan.nextLong();
			long b = scan.nextLong();
			if (a > b) //Swap a and b so that a <= b
			{
				long temp = a;
				a = b;
				b = temp;
			}
			System.out.printf("Graph #%d: ", testCase);
			if (n % 2 == 0) //n is even
			{
				if (a % 2 == b % 2) //Difference between them is even
				{
					long startA = (b-a)/2; //Start at smaller id and go clockwise
					long startB = (a+n-b)/2; //Start at larger id and go clockwise
					System.out.println(Math.min(startA, startB));
				}
				else //Difference between them is odd
					System.out.println("Impossible");
			}
			else //n is odd
			{
				if (a % 2 == b % 2) //Difference between them is even
					System.out.println((b-a)/2);
				else //Difference between them is odd
				{
					long startA = (b+n-a)/2;
					long startB = (a+n-b)/2;
					System.out.println(Math.min(startA, startB));
				}
			}
		}
	}
}
