import java.util.concurrent.*;

class MatrixMultiplikation {

    public static void main(String args[]) throws InterruptedException {
        MatrixMultiplikation test = new MatrixMultiplikation(10);
        test.run();
    }

    private ExecutorService threadPool;
    private int n;

    public MatrixMultiplikation(int n){
        threadPool =Executors.newFixedThreadPool(n*n);
        this.n = n;
    }

    public void run() throws InterruptedException {
        Matrix matrixIn = Matrix.randomMatrix(n);
        Matrix matrixOut = Matrix.randomMatrix(n);
        for(int l = 0; l<n;l++)for(int r = 0; r<n;r++){
            threadPool.submit(new MultiplyMatrixTask(matrixIn, matrixOut,l,r));
        }
        threadPool.shutdown();
        boolean success = threadPool.awaitTermination(10, TimeUnit.SECONDS);
        if(success)
            System.out.println(matrixOut);
        else
            System.out.println("Error!");
    }

}

class MultiplyMatrixTask implements Runnable {


    private final Matrix input;
    private final Matrix output;
    private final int line;
    private final int row;

    public MultiplyMatrixTask(Matrix input, Matrix output, int line, int row){
        this.input = input;
        this.output = output;
        this.line = line;
        this.row = row;
    }

    @Override
    public void run() {
        int newValue = 0;
        for(int i = 0;i<input.getHeight();i++){
            newValue += input.get(line, i) * input.get(i, row);
        }
        output.set(newValue,line,row);
    }
}

class Matrix{

    int[][] data;

    public Matrix(int[][] data){
        this.data = data;
    }

    public int get(int line, int row){
        return data[line][row];
    }


    public synchronized void set(int v, int line, int row){
        data[line][row] = v;
    }

    public int getHeight(){
        return data.length;
    }

    public int getWidth(){
        return data[0].length;
    }

    public static Matrix randomMatrix(int n) {
        Matrix ret = new Matrix(new int[n][n]);
        for(int l = 0; l<n;l++)for(int r = 0; r<n;r++){
            ret.set(l+r,l,r);
        }
        return ret;
    }

    public String toString(){
        String ret = "";
        for(int l = 0; l<this.getHeight();l++){
            for(int r = 0; r<this.getWidth();r++){
                ret+=this.get(l,r) + " ";
            }
            ret += "\n";
        }
        return ret;
    }

}
