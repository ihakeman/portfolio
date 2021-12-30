public class StatTracker
{
  private static int maxBattles = 0; //default all but minimum's to be 0
  private static int minBattles = 1000; //set to 1000 since it is the max possible due to restarting after 1000 battles
  private static int maxWars = 0;
  private static int minWars = 1000; //set to 1000 since this is the max possible due to restarting at 1000 battles
  private static int totalGames = 0;
  private static int totalBattles = 0;
  private static int totalWars = 0;
  private static int totalDoubleWars = 0;
  private static int battlesInCurrentGame = 0;
  private static int warsInCurrentGame = 0;
  private static int doubleWarsInCurrentGame = 0;

  public static void endGame()
  {
    totalGames += 1;
    totalBattles += battlesInCurrentGame; //add stats from current battles to totals
    totalWars += warsInCurrentGame;
    totalDoubleWars += doubleWarsInCurrentGame;
    if (battlesInCurrentGame > maxBattles) //change mins/maxs if appropriate
      maxBattles = battlesInCurrentGame;
    if (battlesInCurrentGame < minBattles)
      minBattles = battlesInCurrentGame;
    if (warsInCurrentGame > maxWars)
      maxWars = warsInCurrentGame;
    if (warsInCurrentGame < minWars)
      minWars = warsInCurrentGame;
    battlesInCurrentGame = 0; //reset the ones for each game for the next game
    warsInCurrentGame = 0;
    doubleWarsInCurrentGame = 0;
  }
  public static void resetGame()
  {
    battlesInCurrentGame = 0; //reset the stats for a game if starting the game over
    warsInCurrentGame = 0;
    doubleWarsInCurrentGame = 0;
  }
  public static void addBattle()
  {
    battlesInCurrentGame += 1;
  }
  public static void addWar()
  {
    warsInCurrentGame += 1;
  }
  public static void addDoubleWar()
  {
    doubleWarsInCurrentGame += 1;
  }
  public static int getBattleNumber()
  {
    return battlesInCurrentGame;
  }
  public static int getWarNumber()
  {
    return warsInCurrentGame;
  }
  public static int getGameNumber()
  {
    return totalGames;
  }
  public static double getAvgBattlesPerGame()
  {
    return (1.0 * totalBattles / totalGames);
  }
  public static double getAvgWarsPerGame()
  {
    return (1.0 * totalWars / totalGames);
  }
  public static double getAvgDoubleWarsPerGame()
  {
    return (1.0 * totalDoubleWars / totalGames);
  }
  public static void report()
  {
    System.out.println("Results after " + totalGames + " games: ");
    System.out.println("Average number of battles:     " + getAvgBattlesPerGame());
    System.out.println("Average number of wars:        " + getAvgWarsPerGame());
    System.out.println("Average number of double wars: " + getAvgDoubleWarsPerGame());
    System.out.println("Max number of battles:         " + maxBattles);
    System.out.println("Min number of battles:         " + minBattles);
    System.out.println("Max number of wars:            " + maxWars);
    System.out.println("Min number of wars:            " + minWars);
  }
}
