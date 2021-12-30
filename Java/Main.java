public class Main
{
  private static Game game;
  private static void simulate(int numberOfGames)
  {
    while (StatTracker.getGameNumber() < numberOfGames)
    {
      game = new Game(); //start a new game each time so everything is reset
      game.play();
    }
    StatTracker.report();
  }
  public static void main(String[] args)
  {//this makes the String input to an integer then an int
    simulate(Integer.valueOf(args[0]).intValue());
    WarLogger.getInstance().release();
  }

}
