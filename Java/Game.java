public class Game
{
  private static Player player1;
  private static Player player2;
  private static Deck deck;
  private static boolean isWar;

  public Game()
  {
    player1 = new Player(1);
    player2 = new Player(2);
    deck = new Deck();
    isWar = false;
  }
  public static void play()
  {
    deck.createNew();
    deck.dealCards(player1, player2);
    while(!getIfWon(player1, player2))
    {
      if (StatTracker.getBattleNumber()>1000) //if too many battles, restart the whole game
      {
        player1.emptyHand(); //clears the players owned cards
        player2.emptyHand();
        deck = new Deck(); //make a new deck for a new game
        deck.createNew();
        deck.dealCards(player1, player2); //deal the new game
        StatTracker.resetGame(); //clears the stats for the current game so that we can start over
      }
      CardsInPlay.reset();
      StatTracker.addBattle();

      makeHandforBattle(player1); //makes a battle hand for each player
      makeHandforBattle(player2);

      Cards player1Cards = CardsInPlay.playerCards(player1);
      Cards player2Cards = CardsInPlay.playerCards(player2);
      WarLogger.getInstance().logBattle(StatTracker.getBattleNumber(), WarLogger.P1, player1Cards.toArray());
      WarLogger.getInstance().logBattle(StatTracker.getBattleNumber(), WarLogger.P2, player2Cards.toArray());

      int player1HandValue = CardsInPlay.computeValueOfAPlayersCards(player1); //gets hand value for comparison
      int player2HandValue = CardsInPlay.computeValueOfAPlayersCards(player2);
      String winnerForWarLogger;
      if (player1HandValue > player2HandValue) //if player1 wins the battle
      {
        CardsInPlay.giveToPlayer(player1);
        winnerForWarLogger = WarLogger.P1;
        WarLogger.getInstance().logBattleOutcome(StatTracker.getBattleNumber(), winnerForWarLogger);
      }
      else if (player1HandValue < player2HandValue) //else if player2 wins the battle
      {
        CardsInPlay.giveToPlayer(player2);
        winnerForWarLogger = WarLogger.P2;
        WarLogger.getInstance().logBattleOutcome(StatTracker.getBattleNumber(), winnerForWarLogger);
      }
      else
      {
        if (getIfWon(player1, player2)) //check if anyone ran out of cards
          break;
        goToWar(player1, player2); //have a war
      }
      if (player1.hasNoMoreCards() && player2.hasNoMoreCards()) //if both players run out, quit the game
        break;
    }
    StatTracker.endGame();
    if (player2.hasNoMoreCards()) //if player 2 lost
    {
      String winnerForWarLogger = WarLogger.P1;
      WarLogger.getInstance().logGameOutcome(StatTracker.getGameNumber(), winnerForWarLogger);
    }
    else //otherwise assume player 2 won
    {
      String winnerForWarLogger = WarLogger.P2;
      WarLogger.getInstance().logGameOutcome(StatTracker.getGameNumber(), winnerForWarLogger);
    }
  }

  public static void makeHandforBattle(Player player)
  {
    if (player.getNumberOfCards()>=3) //if 3 or more cards flip 3
    {
      CardsInPlay.add(player.flip3(), player);
    }
    else if (player.getNumberOfCards()==2) //if 2 cards flip 2
    {
      CardsInPlay.add(player.flip1(), player);
      CardsInPlay.add(player.flip1(), player);
    }
    else if (player.getNumberOfCards()==1) //if only 1 card only flip 1
    {
      CardsInPlay.add(player.flip1(), player);
    }
  }
  public static void goToWar(Player player1, Player player2)
  {
    String winnerForWarLogger = WarLogger.WAR;
    WarLogger.getInstance().logBattleOutcome(StatTracker.getBattleNumber(), winnerForWarLogger);
    isWar = true;
    StatTracker.addWar();
    int warWinner = WarResolver.resolve(player1, player2); //returns int for player who won
    if (warWinner == player1.getNumber()) //if player 1 won the war
    {
      winnerForWarLogger = WarLogger.P1;
      WarLogger.getInstance().logWarOutcome(StatTracker.getWarNumber(), winnerForWarLogger);
    }
    else
    {
      winnerForWarLogger = WarLogger.P2;
      WarLogger.getInstance().logWarOutcome(StatTracker.getWarNumber(), winnerForWarLogger);
    }
  }
  public static boolean getIfWon(Player player1, Player player2)
  { //checking if somebody has lost/won
    if (player1.hasNoMoreCards() || player2.hasNoMoreCards())
      return true;
    return false;
  }
}
