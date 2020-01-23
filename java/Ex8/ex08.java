
public class ex08 {

    public static void main(String[] args) {
        System.out.println("Numerical differentiation");
        System.out.println("");

	new NumericalDifferntiation().solve();
	new NumericalIntegration().solve();

    }

    static double f(double x) { return Math.sin(x); }
    static double fprime(double x) { return (float)Math.cos(x); }

    static double f2(double x) { return 1/(double)(x*x+1);}
}

class NumericalDifferntiation {

    void solve() {
    float Deriv, Error;
    double x,h = 0.025 * Math.PI;


    System.out.println("Forward difference");
    for(int i = 0;i <= 5; i++){
        x = 0.1 * i * Math.PI;
        Deriv = (float)((ex04.f(x+h) - ex04.f(x))/h);
        Error = Deriv - (float)ex04.fprime(x);
        System.out.println("x = " + String.format("%.1f", i*0.1) + " PI  Deriv =   " + String.format("%.6f", Deriv) + "   Error =  " + String.format("%.6f", Error));
    }

    System.out.println("");
    System.out.println("Central difference");
    for(int i = 0;i <= 5; i++){
        x = 0.1 * i * Math.PI;
        Deriv = (float)((ex04.f(x+h) - ex04.f(x-h))/(2.0*h));
        Error = Deriv - (float)ex04.fprime(x);
        System.out.println("x = " + String.format("%.1f", i*0.1) + " PI  Deriv =   " + String.format("%.6f", Deriv) + "   Error =  " + String.format("%.6f", Error));
    }
    }

}

class NumericalIntegration {

    void solve() {
        double I, R, Error,Integral = Math.PI/4.0;
        double n = 24.0,h = 1/n;
        System.out.println("");
        System.out.println("Numerical integration");
        System.out.println("I = Integral(1/(x^2+1)), limits: [0,1]");

        System.out.println("Trapezoidal rule, nsub = 24");
        I = 0.0;
        for(int i=0;i < n; i++){
            I += (ex08.f2(i/n)+ex08.f2((i+1)/n));
        }
        I = I*h/2;
        Error = I - Integral;
        R = Error/I*100;
        System.out.println("I =   " + String.format("%.12f", I) + "   Error =  "+ String.format("%.4e", Error) +"   R =  " + String.format("%.2e", R) + " %");
        System.out.println("");
        System.out.println("Simpson 1/3 rule, nsub = 24");
        I = 0.0;
        for(int i=0;i < n-1; i+=2){
            I += (ex08.f2(i/n)+4*ex08.f2((i+1)/n)+ex08.f2((i+2)/n));
        }
        I = I*h/3;
        Error = I - Integral;
        R = Error/I*100;
        System.out.println("I =   " + String.format("%.12f", I) + "   Error =  "+ String.format("%.4e", Error) +"   R =  " + String.format("%.2e", R) + " %");

    }

}
