
public class SiebDesEratosthenes {
    public static void main(String args[]){
        new SiebDesEratosthenes(10000);
    }

    public SiebDesEratosthenes(int maxN){
        Primzahltester start = new Primzahltester(2);
        for(int i = 3;i<maxN;i++){
            start.testeZahl(i);
        }
    }
}

class Primzahltester implements Runnable {
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

    public synchronized void testeZahl(int n){
        if(n%prim == 0) {
            //Mache nichts. Zahl ist keine Primzahl
        }else if(n > prim )//Nur wenn es noch einen Sinn hat weiter zu prüfen:
        {
            enterBlock();
            if(this.nextPrim == null){
                setNextPrim(new Primzahltester(n));
            }
            //Weiterprüfen:
            new Thread(nextPrim.setNextTest(n)).start();
            exitBlock();
        }
    }

    private synchronized void enterBlock(){
        while (blocked);
        blocked = true;
    }

    private synchronized void exitBlock(){
        blocked = false;
    }

    private synchronized Primzahltester setNextTest(int toTest){
        this.toTest = toTest;
        return this;
    }

    private Primzahltester setNextPrim(Primzahltester nextPrim){
        this.nextPrim = nextPrim;
        return this;
    }

    @Override
    public void run() {
        testeZahl(toTest);
    }
}