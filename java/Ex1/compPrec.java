/**
 *  Numerical Analysis. Exercise 01.
 */

public class compPrec {

    /** Radix used by floating-point numbers    */
    static private int fRadix = 2;

    /** Largest positive value which, when subtracted to 1.0, yields 0.0   */
    static private double negativeMachinePrecision = 0;

    /** Largest possible number   */
    static private double largestNumber = 0;

    /** Smallest number different from zero     */
    //    static private double smallestNumber = 0;


    public static double getNegativeMachinePrecision() {
        int n = 1;
        double pow = Math.pow(2, -1*n);
        double P = 1 - pow -1;
        while(P != 0){
            n += 1;
            pow = Math.pow(2, -1*n);
            P = 1 - pow - 1;
        }
        negativeMachinePrecision = Math.pow(2, -1*(n));

	return negativeMachinePrecision;
    }


    public static double getLargestNumber() {
        double f =1- 2 * negativeMachinePrecision;
        double g = f;
        f = 2 * f;
        boolean A = Double.isFinite(f);
        while(A){
            g = f;
            f = 2 * f;
            A = Double.isFinite(f);
        }
        largestNumber = g;
	return largestNumber;
    }


    public static void printParameters() {

	System.out.println( "Floating-point machine parameters");
	System.out.println( "---------------------------------");
	System.out.println( " ");
	System.out.println( "Negative machine precision = "
			    + getNegativeMachinePrecision());
	System.out.println( "Largest number = "+ getLargestNumber());
	//	System.out.println( "Smallest number = "+ getSmallestNumber());
	return;
    }


    public static void main(String[] args) {

	compPrec cp = new compPrec();

	cp.printParameters();

    }

}