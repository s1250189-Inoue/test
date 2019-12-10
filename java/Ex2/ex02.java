/**
 *  Numerical Analysis. Exercise 02.
 */
public class ex02 {
    public static void main(String[] args) {
	new QuadEquation().evaluate();
	new Cancellation().evaluate();
    }
}

class QuadEquation {
    float ans1,ans2;
    double ans3,ans4;
    double a = 1,b = -8000, c = 1;
    void evaluate() {
        ans1 = (float)((-1.0*b + (float)Math.sqrt(b*b-4*a*c))/2.0*a);
        ans2 = (float)((-1.0*b - (float)Math.sqrt(b*b-4*a*c))/2.0*a);
        ans3 = ((-1.0*b + Math.sqrt(b*b-4*a*c))/2.0*a);
        ans4 = ((-1.0*b - Math.sqrt(b*b-4*a*c))/2.0*a);
        System.out.println("Task 1. Quadratic equation ax^2+bx+c=0");
        System.out.println("a = " + a + " b = " + b + " c = " + c);
        System.out.println("Single precision  x1 = " + ans1 + "  x2 = " + ans2);
        System.out.println("Single precision  x1 = " + ans3 + "  x2 = " + ans4 + "\n\n");
    }
}

class Cancellation {
    double a = 1.0e12, b = 1e9, c = 44.999999999999;
    double ans1, ans2, ans3;
    void evaluate(){
        ans1 = Math.log(a+1.0) -Math.log(a);
        ans2 = Math.sqrt(b*b+1) - b;
        ans3 = Math.pow(Math.cos(Math.toRadians(c)),2) - Math.pow(Math.sin(Math.toRadians(c)),2);

        System.out.println("Task 2. Cancellation");
        System.out.println("ln(x+1)-ln(x),     x = 1.0E12 : " + ans1);
        System.out.println("ans1 = Math.log(x+1.0) -Math.log(x);\n");
        System.out.println("sqrt(x^2+1)-x,     x = 1.0E9 : " + ans2);
        System.out.println("ans2 = Math.sqrt(x*x+1) - x;\n");
        System.out.println("cos^2(x)-sin^2(x), x = 44.999999999999 : " + ans3);
        System.out.println("ans3 = Math.pow(Math.cos(Math.toRadians(x)),2) - Math.pow(Math.sin(Math.toRadians(x)),2);\n");
    }
}