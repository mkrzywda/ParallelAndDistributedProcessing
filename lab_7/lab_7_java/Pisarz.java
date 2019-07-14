public class Pisarz extends Thread {
    Czytelnia czytelnia;
    int id;

    public Pisarz ( Czytelnia czytelnia, int id ) {
        this.czytelnia = czytelnia;
        this.id = id;
    }

    @Override
    public void run(){
        while (true){
            System.out.println( "Pisarz [" + id +  "]: przed zamkiem" );
            try {
                czytelnia.pisarz_wchodzi( id );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            System.out.println( "\nCzytelników = " + czytelnia.getLicznik_czytelnikow() + "\tPisarzy = " + czytelnia.getLicznik_pisarzy() );
            System.out.println( "Pisarz [" + id +  "]: piszę" );
            try {
                Thread.sleep( 500 );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            System.out.println( "Pisarz [" + id +  "]: po zamku" );
            czytelnia.pisarz_wychodzi();
            try {
                Thread.sleep( 1000 );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }
    }
}
