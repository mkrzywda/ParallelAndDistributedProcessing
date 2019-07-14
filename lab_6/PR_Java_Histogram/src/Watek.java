
public class Watek extends Thread{
    Obraz obraz;
    int i;
    public Watek(int id,Obraz obraz)
    {
        this.i=id;
        this.obraz=obraz;
    }
    public void nextTask(int i)
    {
        this.i =i;
    }
    @Override
    public void run() {
        obraz.calculate_histogram(i);
        obraz.print_histogram(i);
    }


}
