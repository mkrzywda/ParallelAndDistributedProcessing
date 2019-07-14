import java.util.Arrays;
import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.Scanner;

public class Main {

    public static void main ( String[] args ) {
		System.out.println("Enter a size of array to sort \n");
		Scanner reader = new Scanner(System.in);
        int n = reader.nextInt();
        int[] tabToSort = new int[n];
        for ( int i = 0; i < n; i++ )
            tabToSort[i] = new Random().nextInt( 10 );

        System.out.println( Arrays.toString( tabToSort ) );
		System.out.println("\nAfter sorting");
        DivideTask dv = new DivideTask( tabToSort );
        ForkJoinPool fjp = new ForkJoinPool();
        fjp.invoke( dv );

        System.out.println( Arrays.toString( tabToSort ) );
    }
}
