import java.util.Scanner;

public class triforce {
    public static void main(String[] args) {
        double sqrt3 = Math.sqrt(3);
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        for(int c = 0; c < n; c++) {
            int s = in.nextInt();
            int t = in.nextInt();
            int p = in.nextInt();
            if(t > 100) {
                System.out.printf("Triforce #%d: 0.00\n", c+1);
                continue;
            }
            double area = sqrt3*s*s/4*Math.pow(3.0/4.0, t);
            System.out.printf("Triforce #%d: %.2f\n", c+1, area*p);
        }
    }
}
