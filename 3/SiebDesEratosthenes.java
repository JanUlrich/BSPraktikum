
public class SiebDesEratosthenes {
    public static void main(String args[]){
        new SiebDesEratosthenes(10000);
    }

    public SiebDesEratosthenes(int maxN){
        Primzahltester start = new Primzahltester(2);
        for(int i = 3;i<maxN;i++){
            start.setNextTest(i);
            start.run();
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
    private synchronized void enterBlock(){
        while (blocked);
        blocked = true;
    }

    private synchronized void exitBlock(){
        blocked = false;
    }

    public synchronized Primzahltester setNextTest(int toTest){
        //enterBlock();
        this.toTest = toTest;
        //exitBlock();
        return this;
    }

    private synchronized Primzahltester setNextPrim(Primzahltester nextPrim){
        this.nextPrim = nextPrim;
        return this;
    }

    @Override
    public synchronized void run() {
        //enterBlock();
        if(toTest%prim == 0) {
        //Mache nichts. Zahl ist keine Primzahl
        }else if(toTest > prim )//Nur wenn es noch einen Sinn hat weiter zu prüfen:
        {
            if(this.nextPrim == null){
                setNextPrim(new Primzahltester(toTest));
            }
            //Weiterprüfen:
            new Thread(nextPrim.setNextTest(toTest)).start();
            //nextPrim.setNextTest(toTest).run();
        }
        //exitBlock();
    }
}