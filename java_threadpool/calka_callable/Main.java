import java.util.concurrent.*;

public class Main {

    private static final int NTHREADS = 1;

    public static void main ( String[] args ) {
        ExecutorService executor = Executors.newFixedThreadPool( NTHREADS );
        Callable<Double> calka = new Calka_callable( 0, Math.PI, 0.001 );
        executor.submit( calka );
        executor.shutdown();
        while (!executor.isTerminated()){}
    }
}
