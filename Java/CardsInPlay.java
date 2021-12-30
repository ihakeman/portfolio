import java.util.*;
public class CardsInPlay
{
  private static Cards player1Cards = new Cards();
  private static Cards player2Cards = new Cards();

  public static void reset()
  {
    player1Cards = new Cards();
    player2Cards = new Cards();
  }
  public static void add(Cards cards, Player player)
  {
    if (player.getNumber() == 1)
      player1Cards.add(cards);
    else
      player2Cards.add(cards);
  }
  public static void add(Card card, Player player)
  {
    if (player.getNumber() == 1)
      player1Cards.add(card);
    else
      player2Cards.add(card);
  }
  public static void giveToPlayer(Player player)
  { //adds all cards into one Cards and then shuffles before giving to their new owner
    Cards tempCards = new Cards();
    tempCards.add(player1Cards);
    tempCards.add(player2Cards);
    tempCards.randomize();
    for (int i=0; i<tempCards.size(); ++i) //give each card to the player it belongs
    {
      player.receiveCard(tempCards.get(i));
    }
    reset(); //clear the cards in play
  }
  public static int computeValueOfCards(Cards cards)
  {
    int[] cardValues = new int[cards.size()];
    for(int i=0; i<cards.size();++i)
    {
      cardValues[i] = cards.get(i).getValue();
    }
    Arrays.sort(cardValues);
    if (cards.size()==1)
      return cardValues[0];
    return cardValues[1];
  }
  public static int computeValueOfAPlayersCards(Player player)
  {
    if (player.getNumber() == 1)
    {
      return computeValueOfCards(player1Cards);
    }
    else
    {
      return computeValueOfCards(player2Cards);
    }
  }
  public static Cards playerCards(Player player) //returns the group of cards that a player has in play
  {
    if (player.getNumber()==1)
      return player1Cards;
    return player2Cards;
  }
  public static String makeString()
  {
    String stringToReturn = "Player 1's cards in play:\n" + player1Cards.toString()
      + "\nPlayer 2's cards in play:\n" + player2Cards.toString();
    return stringToReturn;
  }
}
