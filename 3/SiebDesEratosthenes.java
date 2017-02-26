
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
    private boolean blocked;
    private final int prim;
    private Primzahltester nextPrim;
    private int toTest;

    public Primzahltester(int prim){
        this.prim = prim;
        this.nextPrim = null;
        blocked = false;
        System.out.println(prim); //Primzahl ausgeben
    }

    public synchronized void test(final int toTest){
        if(toTest%prim == 0) {
            //Mache nichts. Zahl ist keine Primzahl
        }else if(toTest > prim )//Nur wenn es noch einen Sinn hat weiter zu prüfen:
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
            //nextPrim.setNextTest(toTest).run();
        }
    }


}