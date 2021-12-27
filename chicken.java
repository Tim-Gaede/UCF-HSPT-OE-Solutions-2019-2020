import java.util.Scanner;

public class chicken {
	
	public static void main(String[] args) {
		Scanner scan= new Scanner(System.in);
		int t=scan.nextInt();
		for(int i=0;i<t;i++){
			int n=scan.nextInt();
			int d=scan.nextInt();
			double p=scan.nextDouble();
			double[] dp=new double[n+1];
			for(int j=1;j<=n;j++){
				dp[j]=dp[j-1]*(1-p);
				if(j-d>=0){
					dp[j]+=(dp[j-d]+2)*p;
				}else{
					dp[j]+=2*p;
				}
			}
			System.out.println(dp[n]);
		}
	}
	
}