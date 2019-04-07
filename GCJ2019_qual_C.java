import java.io.InputStream;
import java.io.PrintWriter;
import java.io.OutputStream;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.Map;
import java.util.HashMap;
import java.util.Iterator;
import java.math.BigInteger;

public class Solution {
	public static final int N = 105;

	static class Task {
		int t, m;
		BigInteger n, a[] = new BigInteger[N], primes[] = new BigInteger[N];
		ArrayList <BigInteger> pr = new ArrayList <BigInteger>();
		Map <BigInteger, Character> compress = new HashMap <BigInteger, Character>();

		public void solve (int testNumber, InputReader in, PrintWriter out) {
			t = in.nextInt();
			for (int T = 1; T <= t; T++) {
				pr.clear(); compress.clear();
				out.print("Case #" + T + ": ");
				n = in.nextBigInteger(); m = in.nextInt();
				for (int i = 1; i <= m; i++) a[i] = in.nextBigInteger();
				int diff = 1;

				for (int i = 1; i < m; i++) {
					if (a[i].compareTo(a[i + 1]) != 0) {
						BigInteger gcd_value = a[i].gcd(a[i + 1]);
						diff = i + 1;
						primes[diff] = gcd_value;
						break;
					}
				}

				for (int i = diff - 1; i >= 1; i--) primes[i] = a[i].divide(primes[i + 1]);
				for (int i = diff + 1; i <= m + 1; i++) primes[i] = a[i - 1].divide(primes[i - 1]);
				for (int i = 1; i <= m + 1; i++) pr.add(primes[i]);
				Collections.sort(pr);
				char cur = 'B';
				compress.put(pr.get(0), 'A');
				for (int i = 1; i < pr.size(); i++) if (pr.get(i).compareTo(pr.get(i - 1)) != 0) compress.put(pr.get(i), cur++);
				for (int i = 1; i <= m + 1; i++) out.print(compress.get(primes[i]));
				out.println();
			}
		}
	}

	static class InputReader {
		public BufferedReader reader;
		public StringTokenizer tokenizer;
		public InputReader (InputStream stream) {
			reader = new BufferedReader(new InputStreamReader(stream), 32768);
			tokenizer = null;
		}

		public String next(){
			while (tokenizer == null || !tokenizer.hasMoreTokens()) {
				try {
					tokenizer = new StringTokenizer(reader.readLine());
				} catch (IOException e) {
					throw new RuntimeException(e);
				}
			}

			return tokenizer.nextToken();
		}

		public int nextInt(){
			return Integer.parseInt(next());
		}

		public BigInteger nextBigInteger(){
			return new BigInteger(next());
		}
	}

	public static void main (String []args) {
		InputStream inputStream = System.in;
		OutputStream outputStream = System.out;
		InputReader in = new InputReader(inputStream);
		PrintWriter out = new PrintWriter(outputStream);
		Task solver = new Task();
		solver.solve(1, in, out);
		out.close();
	}
}
