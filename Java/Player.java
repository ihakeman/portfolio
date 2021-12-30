public class Player
{
  private int number;
  private Cards cards;

  public Player()
  {
    number = 1; //default number to 1
    cards = new Cards();
  }
  public Player(int number)
  {
    this();
    if (number != 1) //if not 1 force their number to be 2 so it is easier for other classes/methods
      number = 2;
    this.number = number;
  }
  public int getNumber()
  {
    return number;
  }
  public int getNumberOfCards()
  {
    return cards.size();
  }
  public Cards flip3()
  {
    return cards.removeTopCards(3);
  }
  public Card flip1()
  {
    Card returnCard = new Card();
    returnCard = cards.get(0); //access the card to flip
    cards.removeTopCards(1); //remove the card to flip from the players hand
    return returnCard;
  }
  public void receiveCard(Card card)
  {
    cards.add(card);
  }
  public boolean hasNoMoreCards()
  {
    if (cards.size()==0)
      return true;
    return false;
  }
  public boolean hasWon()
  {
    if (cards.size()==52)
      return true;
    return false;
  }
  public void emptyHand()
  {
    cards = new Cards(); //clears the players hand for resetting the game
  }
  public String toString()
  {
    return "Player number: " + number + "\n" + cards;
  }
}
