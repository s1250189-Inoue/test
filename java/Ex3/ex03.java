public class ex03 {

    static double errorTolerance = 1e-7;

    public static void main(String[] args) {

	System.out.println();
	System.out.println("f(x) = x^3 -3*x^2 + 2*x - 0.2 = 0");

	new Bisection().solve();
	new Newton().solve();

    }

    static double f(double x) { return x*x*x -3*x*x + 2*x - 0.2; }
    static double fprime(double x) { return 3*x*x -6*x + 2; }
}

class Bisection {

    void solve() {
        double a = ex03.f(1.5);
        System.out.println();
        System.out.println("Bisection method");
        double xneg = 1.5, xpos = 3.0, x = (xneg + xpos)/2.0;
        double err = 1e-7;
        int i = 1;

        while(Math.abs(xpos - xneg) > err){
            System.out.println("Iteration   "+ i +"    x =   "+ String.format("%.7f", x));
            if(ex03.f(x) > 0){ xpos = x; }
            else{ xneg = x; }
            x = (xpos + xneg)/2.0;
            i++;
        }
    }

}

class Newton {

    void solve() {

        System.out.println();
        System.out.println("Newton's method");
        double x0 = 3.0, x1 = x0 - (ex03.f(x0)/ex03.fprime(x0));
        double err = 1e-7;
        int i = 1;
        while(Math.abs(x0-x1)>err){
            System.out.println("Iteration   " + i +"    x =   " + String.format("%.7f", x1));
            if(ex03.f(x0) != 0 && ex03.fprime(x0) !=0){
                x0 = x1;
                x1 = x0 - (ex03.f(x0)/ex03.fprime(x0));
            }
            i++;
        }
        System.out.println("Iteration   " + i +"    x =   " + String.format("%.7f", x1));

    }

}
