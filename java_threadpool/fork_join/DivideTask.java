import java.util.concurrent.RecursiveTask;

public class DivideTask extends RecursiveTask<int[]> {

    int[] arrayToDivide;

    public DivideTask ( int[] arrayToDivide ) {
        this.arrayToDivide = arrayToDivide;
    }

    @Override
    protected int[] compute () {

        int kon = arrayToDivide.length, sr = kon / 2;
        int[] t1 = new int[sr];
        int[] t2 = new int[kon - sr];

        if ( sr != 0 ) {                                
			//jeżeli to nie jest tablica jednoelementowa
            for ( int i = 0; i < t1.length; i++ )
                t1[i] = arrayToDivide[i];
            for ( int i = 0; i < t2.length; i++ )
                t2[i] = arrayToDivide[i + sr];

            DivideTask task1 = new DivideTask( t1 );
            DivideTask task2 = new DivideTask( t2 );

            task1.fork();                               //fork wywołuje compute taska
            task2.fork();

            //Wait for results from both tasks
            int[] tab1 = task1.join();
            int[] tab2 = task2.join();

            scal_tab( tab1, tab2, arrayToDivide );
        }
        return arrayToDivide;
    }

    private void scal_tab ( int[] tab1, int[] tab2, int[] scal_tab ) {
        int i = 0, j = 0, k = 0;

        while ( ( i < tab1.length ) && ( j < tab2.length ) )
            if ( tab1[i] < tab2[j] )
                scal_tab[k++] = tab1[i++];
            else
                scal_tab[k++] = tab2[j++];

        if ( i == tab1.length )
            for ( int a = j; a < tab2.length; a++ )
                scal_tab[k++] = tab2[a];
        else
            for ( int a = i; a < tab1.length; a++ )
                scal_tab[k++] = tab1[a];
    }

}
