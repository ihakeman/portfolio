public class Card
{
  private int cardValue;
  private String cardSuit;

  public Card()
  {
    cardValue = 0;
    cardSuit = "No Suit";
  }
  public Card(int cardValue, String cardSuit)
  {
    this.cardValue = cardValue;
    this.cardSuit = cardSuit;
  }
  public int getValue()
  {
    return cardValue;
  }
  public String getSuit()
  {
    return cardSuit;
  }
  public String toString()
  {
    String name = String.valueOf(cardValue);
    if (cardValue == 11)
      name = "Jack";
    else if (cardValue == 12)
      name = "Queen";
    else if (cardValue == 13)
      name = "King";
    else if (cardValue == 14)
      name = "Ace";
    return name + "-of-" + cardSuit;
  }
}
