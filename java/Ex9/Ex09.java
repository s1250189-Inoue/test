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
    }

    void RungeKutta(double h) {
    }

}