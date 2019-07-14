import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.*;

public class Main {

    private static final int NTHREADS = 4;

    public static void main ( String[] args ) {
        ExecutorService executor = Executors.newFixedThreadPool( NTHREADS );
        List<Future<Double>> list = new ArrayList<>();
        double suma = 0.0;
        double poczatek = 0, koniec = Math.PI, ile_zadan = 12;
        double start, stop;

        for ( int i = 0; i < ile_zadan; i++ ) {
            start = i * ( ( koniec - poczatek ) / ile_zadan );
            stop = start + ( ( koniec - poczatek ) / ile_zadan );

            Callable<Double> calka = new Calka_callable( start, stop, 0.001 );
            Future<Double> future = executor.submit( calka );
            list.add( future );
        }

        for ( Future<Double> el : list ) {
            try {
                suma += el.get();
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            } catch ( ExecutionException e ) {
                e.printStackTrace();
            }
        }

        executor.shutdown();
        while ( ! executor.isTerminated() ) {
        }

        System.out.println( "\n\nSuma = " + suma );
    }
}
