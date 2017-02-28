import java.util.ArrayList;
import java.util.Comparator;

public class SiebDesEratosthenes {
    public static void main(String args[]){
        new SiebDesEratosthenes(10000);
    }

    public SiebDesEratosthenes(int maxN){
        Primzahltester start = new Primzahltester(2);
        for(int i = 3;i<maxN;i++){
            start.test(i);
        }
    }
}

class Primzahltester {
    private final int prim;
    private Primzahltester nextPrim;

    public Primzahltester(int prim){
        this.prim = prim;
        this.nextPrim = null;
    }

    public synchronized void test(int next){
        final int toTest = next;

            if(toTest%prim == 0) {
                //Mache nichts. Zahl ist keine Primzahl
            }else
            {
                if(this.nextPrim == null){
                    System.out.println(prim); //Primzahl ausgeben
                    this.nextPrim = (new Primzahltester(toTest));
                }
                //Weiterprüfen:
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        nextPrim.test(toTest);
                    }
                }).start();
            }
        }
}