public class Czyt_Pis {
    public static void main ( String[] args ) {

        int lp = 5, lc = 10;

        Czytelnia czytelnia = new Czytelnia();
        Pisarz[] pisarze = new Pisarz[lp];
        Czytelnik[] czytelnicy = new Czytelnik[lc];

        for ( int i = 0; i < lp; i++ )
            (pisarze[i] = new Pisarz( czytelnia, i )).start();

        for ( int i = 0; i < lc; i++ )
            (czytelnicy[i] = new Czytelnik( czytelnia, i )).start();
    }
}
