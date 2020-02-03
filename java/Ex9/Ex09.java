/**
 *  Numerical Analysis. Exercise 09
 *  ODE
 */
public class Ex09 {

    public static void main(String[] args) {

	System.out.println();
	System.out.println("dy/dx = xy, a=0, b=1, y(a) = 1");
	System.out.println();

	Ex09 e = new Ex09();
	e.Euler(0.1);
	e.RungeKutta(0.1);
	e.Euler(0.01);
	e.RungeKutta(0.01);

    }

    static double f(double x,double y) { return x*y; }

    static double a=0, b=1, ya = 1;

    void Euler(double h) {
        double x=0.0,f,f1=Ex09.ya,f2=0.0,error;
        double n = (1/h);
        for(double i = 0;i < n;++i){
            x = i * h;
            f2 = f1 + h*x*f1;
            f1=f2;
        }
        x = n*h;
        f = Math.exp(0.5*x*x);
        error = f2 - f;
        System.out.println("Euler:       h = " + h + "  x = "+ String.format("%.3f", x) +"  y = " + String.format("%.8f",f2) + "  Error = " + String.format("%.4e", error));
    }

    void RungeKutta(double h) {
        double f1 = Ex09.ya, f2 = 0.0, f,error;
        double x, k1, k2, k3, k4, k, n=1/h,dx = h;

        for (int i=0; i<n; i++) {
            x = i*dx;
            k1 = dx*x*f1;
            k2 = dx*(x + dx/2.)*(f1 + k1/2.);
            k3 = dx*(x + dx/2.)*(f1 + k2/2.);
            k4 = dx*(x + dx)*(f1 + k3);
            k = (k1 + 2*k2 + 2*k3 + k4)/6.;

            f2 = f1 +k;
            f1 = f2;
        }
        x = n*h;
        f = Math.exp(0.5*x*x);
        error = f2 - f;
        System.out.println("Euler:       h = " + h + "  x = "+ String.format("%.3f", x) +"  y = " + String.format("%.8f",f2) + "  Error = " + String.format("%.4e", error));
    }

}