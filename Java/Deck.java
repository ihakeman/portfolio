public class Deck extends Cards
{
  public void createNew()
  {
    String[] suits = new String[] {"Hearts", "Spades", "Clubs", "Diamonds"};
    for (String suit: suits)
    {
      for (int i=2; i<=14; ++i)
      {
        add(new Card(i, suit));
      }
    }
  }
  public void dealCards(Player player1, Player player2)
  {
    while (cardGroup.size() > 0)
    {
      player1.receiveCard(drawRandomCard());
      player2.receiveCard(drawRandomCard());
    }
  }
}
