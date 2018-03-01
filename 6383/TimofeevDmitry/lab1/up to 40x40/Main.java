import java.util.Arrays;
import java.util.Scanner;

class Main{
    public static void main(String[] args) {
        int n=new Scanner(System.in).nextInt();
        //long time=System.currentTimeMillis();
        CombFinder.squares(n);
        //System.out.println("time= "+(System.currentTimeMillis()-time));
    }
}

class CombFinder{
    static int kol=0;
   /* public static void main(String[] args) {

        for(int n=2;n<40;n++){
            System.out.println("n="+n);
            squares(n);
            System.out.println();
        }
    }*/

    static void squares(int n){
        finder(n*n,new int[2*n+1],1);
    }

    static boolean finder(int sum, int[] set, int detph){
        if(detph==set.length){
            if(sum==0)return handler(set);
            return false;
        }
        for(int i=set[detph-1];i*i<=sum;i++){
            if (i * i * (set.length-detph)> sum) return false;
            if(i+set[detph-1]>set.length/2)return false;

            if(detph==set.length-3) {
                if (2 * i > set.length / 2) return false;
                if (i*i*2 + (set.length/2-i)*(set.length/2-i) > sum) return false;
                set[detph] = i;
                set[detph + 1] = i;
                set[detph + 2] =set.length/2-i;
                if (finder(sum - i*i*2 - (set.length/2-i)*(set.length/2-i), set, detph + 3)) return true;
                continue;
            }
            if(detph==set.length-6){
                set[detph]=i;
                set[detph+1]=i;
                if(finder(sum-i*i*2,set,detph+2))return true;
                continue;
            }
            set[detph] = i;
            if (finder(sum - i * i, set, detph + 1)) return true;
        }
        return false;
    }

    static boolean handler(int[] m){
        if(m[m.length-2]==0)return false;

        kol++;
        if((kol%1000000)==0) System.out.println("kol="+kol/1000000+"  "+ Arrays.toString(m));

        int numOfSquares=0;
        for (int i:m)if(i!=0)numOfSquares++;
        boolean res=merger(new int[m.length/2],0,0,convert(m),0,new int[numOfSquares][3]);
        if(res){
            //System.out.println("total= "+kol);
            kol=0;
        }
        else {
            if((kol%10000)==0) System.out.println("kol="+kol+" "+Arrays.toString(m));
        }
        return res;
    }

    static void handler(int[][] m){
        printArr(m);
    }

    static void printArr(int[][] arr){
        StringBuilder s= new StringBuilder();
        s.append(arr.length).append("\n");
        for(int[] ent:arr) s.append(ent[1]).append(" ").append(ent[2]).append(" ").append(ent[0]).append("\n");
        System.out.println(s);
    }

    static int[] convert(int[] m){
        int[] res=new int[m[m.length-1]+1];
        for(int n:m)res[n]++;
        res[0]=0;
        //System.out.println(Arrays.toString(res));
        return res;
    }

    static boolean merger(int[] field, final int x, final int y, int[] nominals, int deep, int[][] koords){
        if(deep==0){
            int gr;
            for(int i=nominals.length-1;true;i--)if(nominals[i]!=0){
                gr=i;
                nominals[i]--;
                break;
            }
            int mid;
            for(int i=gr;true;i--)if(nominals[i]!=0){
                mid=i;
                nominals[i]-=2;
                break;
            }

            for(int i=0;i<mid;i++)field[i]=gr+mid;
            for(int i=mid;i<gr;i++)field[i]=gr;
            for(int i=gr;i<mid+gr;i++)field[i]=mid;

            koords[0]=new int[]{gr,0,0};
            koords[1]=new int[]{mid,gr,0};
            koords[2]=new int[]{mid,0,gr};

            return merger(field,gr,mid,nominals,3,koords);
        }
        for (int nom=0;nom<nominals.length;nom++){
            if(nominals[nom]==0)continue;
            if(x+nom>field.length)return false;
            if(y+nom>field.length)return false;
            for(int ix=x;ix<x+nom;ix++)if(field[ix]>y)return false;
            // --------------------
            koords[deep][0]=nom;
            koords[deep][1]=x;
            koords[deep][2]=y;
            nominals[nom]--;
            for(int it=x;it<x+nom;it++)field[it]+=nom;
            //---------------------
            int nx=x+nom;
            int ny=y;
            while (true){
                if(nx==field.length){
                    nx=0;
                    ny++;
                    if(ny==field.length){
                        handler(koords);
                        return true;
                    }
                }
                if(field[nx]<=ny)break;
                nx++;
            }

            if(merger(field,nx,ny,nominals,deep+1,koords))return true;

            //---------------------
            nominals[nom]++;
            for(int it=x;it<x+nom;it++)field[it]-=nom;
        }
        return false;
    }
}