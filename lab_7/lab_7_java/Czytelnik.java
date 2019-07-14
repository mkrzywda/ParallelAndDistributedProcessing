public class Czytelnik extends Thread {
    Czytelnia czytelnia;
    int id;

    public Czytelnik ( Czytelnia czytelnia, int id ) {
        this.czytelnia = czytelnia;
        this.id = id;
    }

    @Override
    public void run(){
        while (true){
            System.out.println( "Czytelnik [" + id +  "]: przed zamkiem" );
            try {
                czytelnia.czytelnik_wchodzi( id );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            System.out.println( "\nCzytelników = " + czytelnia.getLicznik_czytelnikow() + "\tPisarzy = " + czytelnia.getLicznik_pisarzy() );
            System.out.println( "Czytelnik [" + id +  "]: czytam" );
            try {
                Thread.sleep( 500 );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }

            System.out.println( "Czytelnik [" + id +  "]: po zamku" );
            czytelnia.czytelnik_wychodzi();

            try {
                Thread.sleep( 1000 );
            } catch ( InterruptedException e ) {
                e.printStackTrace();
            }
        }
    }
}
