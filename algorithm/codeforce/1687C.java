// Don't place your source in a package


import javax.swing.*;
import java.lang.reflect.Array;
import java.text.DecimalFormat;
import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;
import java.util.stream.Stream;



// Please name your class Main
public class Main {
    static FastScanner fs=new FastScanner();
    static class FastScanner {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st=new StringTokenizer("");
        public String next() {
            while (!st.hasMoreElements())
                try {
                    st=new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            return st.nextToken();
        }
        int Int() {
            return Integer.parseInt(next());
        }

        long Long() {
            return Long.parseLong(next());
        }

        String Str(){
            return next();
        }
    }


    public static void main (String[] args) throws java.lang.Exception {
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        //reading /writing file
        //Scanner sc=new Scanner(new File("src/text.txt"));
        //PrintWriter pr=new PrintWriter("output.txt");
        //File file = new File("src/text.txt");

        int T=Int();
        for(int t=0;t<T;t++){
            Solution sol1=new Solution(out,fs);
            sol1.solution();
        }
        out.flush();

    }


    public static int[] Arr(int n){
        int A[]=new int[n];
        for(int i=0;i<n;i++)A[i]=Int();
        return A;
    }
    public static int Int(){
        return fs.Int();
    }
    public static long Long(){
        return fs.Long();
    }
    public static String Str(){
        return fs.Str();
    }

}








class Solution {
    PrintWriter out;
    int INF = 10000000;
    int MOD = 998244353;
    int mod = 1000000007;
    Main.FastScanner fs;
    public Solution(PrintWriter out,Main.FastScanner fs) {
        this.out = out;
        this.fs=fs;
    }


    public void solution() {
        int n = fs.Int();
        int m = fs.Int();
        int a[] = new int[n + 1];
        long s[] = new long[n + 1];
        for(int i = 1; i <= n; i++) {
            a[i] = fs.Int();
        }

        for(int i = 1; i <= n; i++) {
            int x = fs.Int();
            a[i] -= x;
            s[i] = a[i] + s[i - 1];
        }

        TreeSet<Integer> tree = new TreeSet<>();
        Queue<Integer> q = new LinkedList<>();
        for(int i = 0; i <= n; i++) {
            if(s[i] == 0) q.add(i);
            else tree.add(i);
        }

        List<Integer> graph[] = new ArrayList[n + 1];
        Arrays.setAll(graph, e->new ArrayList<>());
        for(int i = 0; i < m; i++) {
            int l = fs.Int();
            int r = fs.Int();
            int mn = Math.min(l, r), mx = Math.max(l, r);
            graph[mn - 1].add(mx);
            graph[mx].add(mn - 1);
        }

        while(q.size() > 0) {
            int root = q.poll();
            for(int nxt : graph[root]) {
                if(s[nxt] != 0) continue;
                int l = Math.min(root, nxt) - 1, r = Math.max(root, nxt);
                while(tree.size() > 0) {
                    Integer h = tree.higher(l);
                    if(h == null || h > r) break;
                    q.add(h);
                    tree.remove(h);
                    s[h] = 0;
                }
            }
        }

        if(tree.size() == 0) {
            out.println("YES");
        } else {
            out.println("NO");
        }

    }


}
