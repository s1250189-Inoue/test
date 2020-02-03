public class ex11a {


	public static void main(String[] args) {

		new LUband().decompose(a, n, h);

		new LUband().solve(a, n, h, b);


		for(int i=0;i<n;i++){
		System.out.println("x["+ i +"] =   " + String.format("%.4f",b[i]));
		}
	}

	static int n=6,h=3;
	static double[][] A = {{3,-1,-1,0,0,0},
							{-1,2,0,-2,0,0},
							{-1,0,3,-1,0,0},
							{0,-2,-1,2,0,0},
							{0,0,0,0,1,-2},
							{0,0,0,0,-2,1}};
	static double[] b = {-2,-5,4,1,-7,-4};
	static double[] a = {0,0,3,0,-1,2,-1,0,3,-2,-1,2,0,0,1,0,-2,1};
}


class LUband {

	public void decompose (double[] a, int n, int h) {



	int i,j,k,h1=h-1;

	double w;



	for(j=1; j<n; j++) {

	    for(i=Math.max(j-h1,0); i<j; i++) {

		for(k=Math.max(j-h1,0); k<i; k++) {

		    a[i+h1*(j+1)] -= a[k+h1*(i+1)] * a[k+h1*(j+1)];

		}

	    }

	    for(i=Math.max(j-h1,0); i<j; i++) {

		w = a[i+h1*(j+1)];

		a[i+h1*(j+1)] /= a[i+h1*(i+1)];

		a[j+h1*(j+1)] -= a[i+h1*(j+1)]*w;

	    }

	}
    }



    public void solve (double[] a, int n, int h, double[] b) {



	int i,j,h1=h-1 ;



	for(j=1; j<n; j++) {

	    for(i=Math.max(j-h1,0); i<j; i++) b[j] -= a[i+h1*(j+1)]*b[i];

	}

	for(j=0; j<n; j++) {

	    b[j] /= a[j+h1*(j+1)];

	}

	for(j=n-1; j>=0; j--) {

	    for(i=Math.max(j-h1,0); i<j; i++) {

		b[i] -= a[i+h1*(j+1)] * b[j];

	    }

	}

    }



}