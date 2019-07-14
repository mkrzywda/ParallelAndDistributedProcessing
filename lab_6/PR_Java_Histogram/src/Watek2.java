import java.util.List;

public class Watek2 implements Runnable {
    List<Integer> task;
    Obraz obraz;
    int id;
    Watek2(List<Integer> ts,Obraz obraz,int id)
    {
        this.id=id;
        this.obraz=obraz;
        task=ts;
    }
    @Override
    public void run() {
        System.out.println("Watek ID: "+id+"\n");
        for (int i:task) {
            obraz.calculate_histogram(i);
            obraz.print_histogram(i);
        }

    }
}
