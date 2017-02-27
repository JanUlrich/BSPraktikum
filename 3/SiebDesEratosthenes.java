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
    private boolean isProcessing = false;
    private final int prim;
    private Primzahltester nextPrim;
    private ArrayList<Integer> toProcess = new ArrayList<Integer>();

    public Primzahltester(int prim){
        this.prim = prim;
        this.nextPrim = null;
        System.out.println(prim); //Primzahl ausgeben
    }

    public synchronized void test(int next){
        final int toTest;
        if(! isProcessing){
            isProcessing = true;
            if(toProcess.size()>0){
                toProcess.add(next);
                toProcess.sort(new Comparator<Integer>() {
                    @Override
                    public int compare(Integer o1, Integer o2) {
                        return o2.compareTo(o1);
                    }
                });
                toTest = toProcess.remove(toProcess.size()-1);
            }else{
                toTest = next;
            }

            if(toTest%prim == 0) {
                //Mache nichts. Zahl ist keine Primzahl
            }else
            {
                if(this.nextPrim == null){
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

            isProcessing = false;
            //Falls es noch Werte in der Warteschlange gibt:
            if(toProcess.size()>0)test(toProcess.remove(toProcess.size()-1));
        }else{
            toProcess.add(next);
        }

    }


}