import java.util.*;
public class Cards
{
  protected LinkedList<Card> cardGroup = new LinkedList<Card>();
  protected Random random = new Random();

  public String toString()
  {
    String returnedString = "";
    for (int i=0; i< cardGroup.size(); ++i)
    {
      returnedString += cardGroup.get(i).toString() + "\n";
    }
    return returnedString;
  }
  public void add(Card card)
  {
    cardGroup.add(card);
  }
  public void add(Cards setOfCards)
  {
    for (int i=0; i<setOfCards.size(); ++i)
    {
      cardGroup.add(setOfCards.get(i));
    }
  }
  public Card get(int index)
  {
    return cardGroup.get(index);
  }
  public int size()
  {
    return cardGroup.size();
  }
  public int getValue(int index)
  {
    return cardGroup.get(index).getValue();
  }
  public Cards removeTopCards(int numberToRemove)
  {
    Cards removedCards = new Cards();
    for (int i=0; i<numberToRemove; ++i)
    {
      removedCards.add(cardGroup.remove());
    }
    return removedCards;
  }
  public void sort()
  {
    cardGroup.sort(new Comparator<Card>()
    {
      @Override
      public int compare(Card card1, Card card2)
      {
        if (card1.getValue() < card2.getValue())
          return -1;
        if (card1.getValue() > card2.getValue())
          return 1;
        return 0;
      }
    });
  }
  protected Card drawRandomCard()
  {
    return cardGroup.remove(random.nextInt(cardGroup.size()));
  }
  public void randomize() //shuffles a group of cards (cards object)
  {
    LinkedList<Card> randomOrdered = new LinkedList<Card>();
    while (!cardGroup.isEmpty())
    { //takes a random card from current Cards to put into new one
      randomOrdered.add(cardGroup.remove(random.nextInt(cardGroup.size())));
    }
    cardGroup = randomOrdered; //make member variable equal the new random cards
  }
  public Card[] toArray()
  {
    Card[] cardArray = new Card[cardGroup.size()];
    for (int i=0; i<cardGroup.size(); ++i)
    {
      cardArray[i] = cardGroup.get(i);
    }
    return cardArray;
  }
}
