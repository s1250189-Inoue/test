import java.util.TreeMap;

public class ex10 {

    public static void main(String[] args) {
        System.out.println("d^2u/dx^2 + d^2u/dy^2 + 2 = 0, edge length=1");
        System.out.println("");

	new Liebman().solve(10,0.1,210);
    new SOR().solve(10,0.1,51);
    new Liebman().solve(20,0.05,787);
    new SOR().solve(20,0.05,195);

    }

    static double f(double x) { return x; }
    static double y = 0.5;
    static double eps = 1.0e-10;
}

class Liebman {

    void solve(int n,double h,int iter) {
        System.out.println("");
        System.out.println("Liebman method");
        System.out.println("n = "+ n +"   h = "+ String.format("%.3f", h) +"\niter = "+ iter);
        double dpmax,dp,u_new,x;
        double[][] arr = new double [n+1][n+1];


        for(int i=0;i <= n;i++){
            for(int j=0;j <= n;j++){ arr[i][j] = 0;}
        }

        for(int k=0;k<iter;k++){ //iterations
            dpmax = ex10.eps;
            for(int i=1;i< n;i++){
                for(int j=1;j< n;j++){
                    u_new = 0.25*(arr[i+1][j]+arr[i-1][j]+arr[i][j+1]+arr[i][j-1]+2*h*h);
	                dp=arr[i][j];
	                if(Math.abs(dp) < dpmax) dpmax=Math.abs(dp);
                    arr[i][j] = u_new;
                }
            }
        }
        for(int i = 0;i <= n;i++){
            x=h*i;
            System.out.println("x = "+ String.format("%.2f", x) +"   u =  " + String.format("%.5f",arr[i][n/2]));
        }

    }

}

class SOR {

    void solve(int n,double h,int iter) {
        System.out.println("");
        System.out.println("SOR method, overrelaxation factor = 1.6");
        System.out.println("n = "+ n +"   h = "+ String.format("%.3f", h) +"\niter = "+ iter);
        double dpmax,dp,u_new,x;
        double[][] arr = new double [n+1][n+1];


        for(int i=0;i <= n;i++){
            for(int j=0;j <= n;j++){ arr[i][j] = 0;}
        }

        for(int k=0;k<iter;k++){ //iterations
            dpmax = ex10.eps;
            for(int i=1;i< n;i++){
                for(int j=1;j< n;j++){
                    u_new = arr[i][j]+1.6*0.25*(arr[i+1][j]+arr[i-1][j]+arr[i][j+1]+arr[i][j-1]-4*arr[i][j]+2*h*h);
	                dp=arr[i][j];
	                if(Math.abs(dp) < dpmax) dpmax=Math.abs(dp);
                    arr[i][j] = u_new;
                }
            }
        }
        for(int i = 0;i <= n;i++){
            x=h*i;
            System.out.println("x = "+ String.format("%.2f", x) +"   u =  " + String.format("%.5f",arr[i][n/2]));
        }
    }

}
