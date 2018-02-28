
import java.util.Arrays;
import java.util.Scanner;

// 0 - free
// >0- not free
class Main1 {
    int min_d ;
    int [][] bestp;
    Main1(int n){
    }
    private static void init(int [] s,int x,int size){
        for (int i=x;i<x+Math.abs(size);i++)
            s[i]+=size;
    }

    private static boolean couldInit(int [] s,int x,int y,int size){
        if (x+size>s.length || y+size>s.length) return false;
 
        for (int i=x;i<x+size;i++)
            if(s[i] > y) return false;
        return true;
    }

    private  static int [] firstFree(int [] s,int x,int y){
        if (x>=s.length) {
            x = 0;y++;
            if (y == s.length) return null;
        }

        while (true){
          
            if (s[x] <= y) return new int[] {x,y};

            x++;
            if (x == s.length) {
                x = 0;
                y++;
                if (y == s.length) return null;
            }
        }
    }
    private void copy(int [][] s,int d){
        for (int i=0;i<d;i++)
            for (int j=0;j<3;j++)
                bestp[i][j] = s[i][j];
    }

    private void solve(int[] s, final int x, final int y,int d,int [][]p,int k){
     

        for(int sz=k-1;sz>=1;sz--){
           
        if (d>=min_d) { return;}
     
           if (!couldInit(s, x, y, sz)) continue;
            if (d == 1) {k = sz+1;}
            init(s,x,sz);
            p[d-1][0] = x;
            p[d-1][1] = y;
            p[d-1][2] = sz-1;
            int[] xy = firstFree(s, x+sz, y);
            if (xy == null) {
              
                if (d < min_d) {
                    min_d = d;
                    copy(p,d);
                    
                }

                init(s,x,-sz);
                return;
            }
            solve(s, xy[0], xy[1], d + 1,p,k);
            init(s,x,-sz);
        }

    }

    static void solve(int n){

        Main1 m=new Main1(n);
        int [][] p = new int [2*n][3];
        m.bestp = new int [2*n][3];
        m.min_d=2*n;
        if (n==29) return;
        m.solve(new int[n],0,0,1,p,n);
        
        StringBuilder s= new StringBuilder("" + m.min_d+"\n");
        for (int i=0;i<m.min_d;i++) {
            for (int j = 0; j < 3; j++)
                s.append(m.bestp[i][j]+1).append(" ");
            s.append("\n");
        }
        System.out.println(s);
        
    }
}

class Main{
    public static void main(String[] args) {
        int n =new Scanner(System.in).nextInt();   
        Main1.solve(n);    

    }
}