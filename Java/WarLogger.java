//DO NOT EDIT THIS CODE FOR ANY REASON

import java.io.*;
import java.util.*;


/**
The WarLogger class logs results of battles, wars, and games to a file.
*/
public class WarLogger{

  private static WarLogger m_instance;
  private PrintWriter m_pw;

  /** A string representation for Player 1 for use in log methods*/
  public static final String P1 = "Player 1";
  /** A string representation for Player 2 for use in log methods*/
  public static final String P2 = "Player 2";
  /** A string representation for War for use in log methods*/
  public static final String WAR = "WAR!!!";

  private WarLogger(){
    try{
      m_pw = new PrintWriter(new FileWriter("WarLogger.war"));

    } catch(Exception e){
      System.err.println("WarLogger is unable to create log file!");
      m_pw = null;
    }
  }

  /**This method returns the instance of the WarLogger to be used for logging
  *@return the instance of the WarLogger to call methods on
  */
  public static synchronized WarLogger getInstance(){
    if(m_instance == null){
      m_instance = new WarLogger();
    }
    return m_instance;
  }

  /** Logs the details of a single battle
  *@param battleNum The number of the battle
  *@param player The player (WarLogger.P1 or WarLogger.P2)
  *@param hand an array of cards played by the player for the battle
  */
  public void logBattle(int battleNum, String player, Card[] hand){
    try{
      m_pw.println("Battle Number: " + battleNum);
      m_pw.println("Player Number: " + player);
      m_pw.print("Player Hand: ");
      if(hand == null || hand.length < 1){
        m_pw.println("Null or Empty Hand");

      } else{
        for(Card c: hand){
          m_pw.print(c);
          m_pw.print(" ");
        }
        m_pw.print("\n");
      }
    }catch(Exception e){
      System.err.println("WarLogger error while printing");
    }
  }

  /** Logs the outcome of a single battle
  *@param battleNum The number of the battle
  *@param result The player who won (WarLogger.P1 or WarLogger.P2 or WarLogger.WAR if tie)
  */
  public void logBattleOutcome(int battleNum, String result){
    try{
      m_pw.println("The outcome of battle " + battleNum + " is " + result);
    } catch(Exception e){
      System.err.println("WarLogger error while printing");
    }
  }

  /** Logs the outcome of a single war
  *@param warNum The number of the war
  *@param result The player who won (WarLogger.P1 or WarLogger.P2 or WarLogger.WAR if tie)
  */
  public void logWarOutcome(int warNum, String result){
    try{
      m_pw.println("The outcome of war " + warNum + " is " + result);
    } catch(Exception e){
      System.err.println("WarLogger error while printing");
    }
  }

  /** Logs the outcome of a single game
  *@param warNum The number of the game
  *@param result The player who won (WarLogger.P1 or WarLogger.P2)
  */
  public void logGameOutcome(int gameNum, String playerNum){
    try{
      m_pw.println("The winner of game " + gameNum + " is " + playerNum);
    } catch(Exception e){
      System.err.println("WarLogger error while printing");
    }
  }

  /**Closes the logger and cleans up. Should be the last thing called in main
  *method of the simulation class.
  */
  public void release(){
    try{
      m_pw.close();
    } catch(Throwable t){
      System.err.println("WarLogger unable to close correctly");
    }
  }

}
