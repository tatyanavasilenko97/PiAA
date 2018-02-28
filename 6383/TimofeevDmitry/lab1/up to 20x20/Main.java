
import java.util.Scanner;

public class Main{
    public static void main(String[] args) {
        int n=new Scanner(System.in).nextInt();
        //long time=System.currentTimeMillis();
        Context.squares(n);
        //System.out.println("time= "+(System.currentTimeMillis()-time));
    }
}

class CombFinder{
    /*public static void main(String[] args) {
        for(int n=2;n<40;n++){
            System.out.println("n="+n);
            Context.squares(n);
            System.out.println();
        }
    }*/

    static void printArr(int[][] arr){
        StringBuilder s= new StringBuilder();
        s.append(arr.length).append("\n");
        for(int[] ent:arr) s.append(ent[1]).append(" ").append(ent[2]).append(" ").append(ent[0]).append("\n");
        System.out.println(s);
    }
}

class Context{
    private final int[] field;
    private final int[][] koords;
    private final int size;
    private final int maxDepth;
    private Context(int size,int maxDepth){
        this.size=size;
        this.maxDepth=maxDepth;
        koords=new int[maxDepth][3];
        field=new int[size];
    }
    static void squares(int n){
        for(int i=4;true;i++) {
            Context context=new Context(n,i);
            if(context.solve(0,0,0)){
                CombFinder.printArr(context.koords);
                return;
            }
        }
    }
    private boolean solve(final int x, final int y, final int deep){
        if(deep==maxDepth)return false;
        for (int nom=1;nom<size;nom++){
            if(x+nom>size)return false;
            if(y+nom>size)return false;
            for(int ix=x;ix<x+nom;ix++)if(field[ix]>y)return false;
            // --------------------
            koords[deep][0]=nom;
            koords[deep][1]=x;
            koords[deep][2]=y;
            for(int it=x;it<x+nom;it++)field[it]+=nom;
            //---------------------
            int nx=x+nom;
            int ny=y;
            while (true){
                if(nx==size){
                    nx=0;
                    ny++;
                    if(ny==size)return true;
                }
                if(field[nx]<=ny)break;
                nx++;
            }

            if(solve(nx,ny,deep+1))return true;

            //---------------------
            for(int it=x;it<x+nom;it++)field[it]-=nom;
        }
        return false;
    }
}