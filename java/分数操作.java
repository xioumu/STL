import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	public final static int maxn = 50 + 10;
	public final static int lim_m = 50;
	public final static BigInteger ZERO = new BigInteger("0");
	public final static BigInteger ONE = new BigInteger("1");
	
	public static void updata(int i, int j, int r, int w, BigInteger[][] mu, BigInteger[][] zi, BigInteger scope) {
		BigInteger nmu = mu[r][w].multiply(scope);
		BigInteger new_mu = mu[i][j].multiply(nmu);
		BigInteger new_zi = mu[i][j].multiply(zi[r][w]);
		new_zi = new_zi.add( nmu.multiply(zi[i][j]) );
		
		//BigInteger h = new_mu.gcd(new_zi);
		mu[i][j] = new_mu;
		zi[i][j] = new_zi.divide(h);
	}
	
	public static void main(String[] args) {
		BigInteger[][] mu = new BigInteger[maxn][maxn], zi = new BigInteger[maxn][maxn];
		BigInteger scope = ZERO;
		int[] x = new int[maxn];
		int n, m, a, b;
		Scanner cin = new Scanner(System.in);
		while (cin.hasNextInt()) {
			n = cin.nextInt();
			m = cin.nextInt();
			a = cin.nextInt();
			b = cin.nextInt();
			for (int i = 0; i < n; i++)
				x[i] = cin.nextInt();
			
			for (int i = 0; i <= n + 1; i++)
				for (int j = 0; j <= lim_m; j++)
					mu[i][j] = ONE;
			for (int i = 0; i <= n + 1; i++)
				for (int j = 0; j <= lim_m; j++)
					zi[i][j] = ZERO;
			zi[0][0] = ONE;
			scope = scope.valueOf(b - a + 1);
			
			for (int i = 0; i < n; i++) {
				for (int j = a; j <= b; j++) {
					int dis = Math.abs(x[i] - j);
					for (int k = 0; k <= lim_m; k++)
						if (k - dis >= 0) {
							updata(i + 1, k, i, k - dis, mu, zi, scope);
						}
				}
			}
			
			BigInteger ans_mu = ONE, ans_zi = ZERO;
			for (int i = 0; i <= m; i++) {
				ans_zi = ans_zi.multiply(mu[n][i]);
				ans_zi = ans_zi.add(zi[n][i].multiply(ans_mu));
				ans_mu = ans_mu.multiply(mu[n][i]);
				BigInteger h = ans_zi.gcd(ans_mu);
				ans_zi = ans_zi.divide(h);
				ans_mu = ans_mu.divide(h);
			}
			
			System.out.println(ans_zi + "/" + ans_mu);
		}
	}
}
