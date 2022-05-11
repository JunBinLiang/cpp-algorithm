



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
            int n = fs.Int();
            int a[] = new int[n];
            for(int i = 0; i < n; i++) a[i] = fs.Int();
            Solution sol1=new Solution();
            sol1.solution(a);
        }
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


//Q : You are given an array a, you can do the following operation any number of times : 
//choose an element a[i] and divide it by 2
//You want to make the array strictly increasing, that is a[0] < a[1] < a[2] < ... a[n - 1]
//What is the minimum operations you need to make the array increasing? 
//Or if is impossible, print -1 instead

//Example : [3, 6, 5] = > [3,3,5] => [1, 3, 5] minimum 2 operations needed
// [5, 3, 2, 1] : -1, can not make it increasing
// [1,2,3,4,5] : 5, already increasing

class Solution {
    public void solution(int a[]) {
        

    }

}



