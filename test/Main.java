



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
        //Scanner in=new Scanner(new File("input.txt"));
        //PrintWriter pr=new PrintWriter("output.txt")
        int T=1;
        for(int t=0;t<T;t++){
            Solution sol1=new Solution(out,fs);
            int n = fs.Int();
            int a[] = new int[n * 2];
            for(int i = 0; i < a.length; i++) a[i] = fs.Int();
            sol1.solution(a);
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


//You are given an array with size 2 * n
// Determine if you can split it into exactly n pairs, the sum of each pair is odd
//Print "YES" if you can, otherwise, print "NO"

//Example1 :
// n = 2
//array : 2 3 4 5
//"YES"

//Example2 :
// n = 3
//array : 2 3 4 5 5 5
//"NO"

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

    public void solution(int a[]) {


    }

}



