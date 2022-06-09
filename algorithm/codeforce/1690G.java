



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
        //Scanner in=new Scanner(System.in);
        //Scanner in=new Scanner(new File("C:\\Users\\leyal\\IdeaProjects\\CF\\src\\item.txt"));
        PrintWriter pr=new PrintWriter(System.out);

        int T = fs.Int();
        for(int t = 0; t < T; t++) {
            Solution sol = new Solution(pr, fs);
            sol.solution();
        }
        pr.flush();


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
    int INF = Integer.MAX_VALUE;
    int NINF = Integer.MIN_VALUE;
    int MOD = 998244353;
    int mod = 998244353;
    Main.FastScanner fs;

    public Solution(PrintWriter out, Main.FastScanner fs) {
        this.out = out;
        this.fs = fs;
    }

    public void solution() {
        int n = fs.Int();
        int m = fs.Int();
        int a[] = new int[n];
        for(int i = 0; i < n; i++) {
            a[i] = fs.Int();
        }

        TreeMap<Integer, Integer> tree = new TreeMap<>();
        for(int i = 0; i < n; i++) {
            int j = i;
            while(j < n && a[j] >= a[i]) {
                j++;
            }
            tree.put(i,a[i]);
            i = j - 1;
        }

        //System.out.println(tree);


        for(int i = 0; i < m; i++) {
            int k = fs.Int() - 1;
            int d = fs.Int();
            a[k] -= d;
            Integer floor = tree.floorKey(k);
            //System.out.println(i + "  " +floor + "  " +  tree+"  " + a[k]);
            if(tree.get(floor) > a[k]) {
                while(true) {
                    Integer ceil = tree.ceilingKey(k);
                    //System.out.println(ceil);
                    if(ceil == null) break;
                    if(tree.get(ceil) >= a[k]) {
                        tree.remove(ceil);
                    } else {
                        break;
                    }
                }
                tree.put(k, a[k]);
            }
            out.print(tree.size() + " ");
        }
        out.println();
    }
}


