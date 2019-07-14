import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public class Histogram {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        System.out.println("Extends Thread version ");
		System.out.println("Count of threads = 94 ");
        int num_threads = 94;

        Watek[] NewThr = new Watek[num_threads];

        for (int i = 0; i < num_threads; i++) {
            NewThr[i] = new Watek(i,obraz_1);
            NewThr[i].start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr[i].join();
            } catch (InterruptedException e) {}
        }
        System.out.println("\n");
        System.out.println("===============================");
        System.out.println("\n");

        System.out.println(" Runnable version ");
		System.out.println("Set count of threads: ");
        int num_threads2 =  scanner.nextInt();

        Watek2[] NewThr2 = new Watek2[num_threads];
        int j=0;
        List<LinkedList<Integer>>tasks = new LinkedList<>() ;
        for(int i=0;i<num_threads2;i++) {
            tasks.add(new LinkedList<>());
        }
        while(j<94)
        {
            tasks.get(j%num_threads2).add(j);
            j++;

        }
        for(int i=0;i<num_threads2;i++) {
            NewThr2[i]=new Watek2(tasks.get(i),obraz_1,i);
            NewThr2[i].run();
        }



    }
}
