public class ex11b {


	public static void main(String[] args) {

		new LUprofile().decompose(a, pcol, n);

        new LUprofile().solve(a, pcol, n, b);


		for(int i=0;i<n;i++){
		System.out.println("x["+ i +"] =   " + String.format("%.4f",b[i]));
		}
	}

	static int n=6;
	static double[][] A = {{3,-1,-1,0,0,0},
							{-1,2,0,-2,0,0},
							{-1,0,3,-1,0,0},
							{0,-2,-1,2,0,0},
							{0,0,0,0,1,-2},
							{0,0,0,0,-2,1}};
	static double[] b = {-2,-5,4,1,-7,-4};
    static double[] a = {3,-1,2,-1,0,3,-2,-1,2,1,-2,1};
    static int[] pcol = {0,1,3,6,9,10,12};
}
 class LUprofile {

    public void decompose (double[] A, int pcol[], int n) {



    int i,j,k,ii,jj,ifirst,jfirst,m;
    double w;

    for(j=1; j<n; j++) {

        jfirst = j - (pcol[j+1]-pcol[j]) + 1;

        jj = pcol[j+1] - j - 1;

        for(i=jfirst; i<j; i++) {

            ifirst = i - (pcol[i+1]-pcol[i]) + 1;

            ii = pcol[i+1] - i - 1;

            w = 0;

            for(m=Math.max(jfirst,ifirst); m<i; m++) w += A[m+ii]*A[m+jj];

                A[i+jj] -= w;

      }

      for(i=jfirst; i<j; i++) {

          w = A[i+jj];

          A[i+jj] = w/A[pcol[i+1]-1];

          A[pcol[j+1]-1] -= w*A[i+jj];

      }

    }

    }



    public void solve (double[] A, int pcol[], int n, double[] x) {

    int i,j,jj,ifirst,jfirst,m;

    for(j=1; j<n; j++) {

        jfirst = j - (pcol[j+1]-pcol[j]) + 1;

        jj = pcol[j+1] - j - 1;

        for(i=jfirst; i<j; i++) 

            x[j] -= A[i+jj]*x[i];

    }

    for(i=n-1; i>=0; i--) {

        x[i] /= A[pcol[i+1]-1];

        for(j=i+1; j<n; j++) {

            jfirst = j - (pcol[j+1]-pcol[j]) + 1;

            if(i>=jfirst) {

                jj = pcol[j+1] - j - 1;

                x[i] -= A[i+jj]*x[j];

            }

        }

    }

    }



    }