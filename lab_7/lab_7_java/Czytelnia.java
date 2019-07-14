import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Czytelnia {

    private Lock lock = new ReentrantLock();
    private Condition pisarz_c = lock.newCondition();
    private Condition czytelnik_c = lock.newCondition();
    private int licznik_pisarzy = 0;
    private int licznik_czytelnikow = 0;
    int lp = 0;

    public void pisarz_wchodzi ( int id ) throws InterruptedException {
        lock.lock();
        try {

            //System.out.println( "Pisarz [" + id +  "]: wszedłem" );
            if ( ( licznik_pisarzy + licznik_czytelnikow ) > 0 || lp == -1 ) {
                //System.out.println( "Pisarz [" + id +  "]: czekam" );
                pisarz_c.await();
            }
            lp = 0;
            licznik_pisarzy++;
        }
        finally {
            //lock.unlock();
        }
    }

    public void pisarz_wychodzi () {
        //lock.lock();

        try{
            licznik_pisarzy--;
            lp = -1;
            czytelnik_c.signal();
        }
        finally {
            lock.unlock();
        }
    }

    public void czytelnik_wchodzi ( int id ) throws InterruptedException {
        lock.lock();
        try {
            //System.out.println( "Czytelnik [" + id +  "]: wszedłem" );
            if ( licznik_pisarzy > 0 ) {
                //System.out.println( "Czytelnik [" + id +  "]: czekam" );
                czytelnik_c.await();
            }

            licznik_czytelnikow++;
            czytelnik_c.signal();
        }
        finally {
            lock.unlock();
        }
    }

    public void czytelnik_wychodzi () {
        lock.lock();
        try {
            licznik_czytelnikow--;

            if ( licznik_czytelnikow == 0 )
                pisarz_c.signal();
        }
        finally {
            lock.unlock();
        }
    }

    public int getLicznik_pisarzy () {
        return licznik_pisarzy;
    }

    public int getLicznik_czytelnikow () {
        return licznik_czytelnikow;
    }
}
