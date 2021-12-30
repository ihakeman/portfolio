public class WarResolver
{
  public static int resolve(Player player1, Player player2)
  {//returns int to show who won to help with warlogger in game class
    boolean isAWar = true;
    while (isAWar)
    { //array used to make copies so that value could be accessed without sending the card into the abyss while flipping
      Card[] warCards = new Card[]{player1.flip1(), player2.flip1()};
      int player1WarValue = warCards[0].getValue();
      int player2WarValue = warCards[1].getValue();
      CardsInPlay.add(warCards[0], player1);
      CardsInPlay.add(warCards[1], player2);
      if (player1WarValue > player2WarValue || player2.hasNoMoreCards())
      {//if player1 wins, give them the cards and return their number for WarLogger Purposes
        CardsInPlay.giveToPlayer(player1);
        return player1.getNumber();
      }
      else if (player1WarValue < player2WarValue || player1.hasNoMoreCards())
      {//or if player2 wins, give them the cards and return their number for WarLogger purposes
        CardsInPlay.giveToPlayer(player2);
        return player2.getNumber();
      }//if neither wins it becomes double war and another war occurs
      StatTracker.addDoubleWar();
    }
    return 0; //impossible to access but this is here to make compiler happy
  }
}
