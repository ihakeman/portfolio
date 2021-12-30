using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Game : MonoBehaviour
{
    private static Game instance;

    public static Game Instance { get { return instance; } }

    public WelcomeScreen welcomeScreen; //access to the canvases
    public Cannon cannon;
    public int CannonballsRemaining;
    private int targetsHit = 0;
    public bool isPlaying;
    public Text UITargetsHit;
    public Text UICannonballsRemaining;
    public Text UIScore;
    public Text UIHighScore;
    private int highScore;

    private void Awake()
    {
        if (instance != null && instance != this)
        {
            Destroy(this.gameObject);
        }
        else
        {
            instance = this;
        }
    }
    // Start is called before the first frame update
    void Start()
    {
        isPlaying = false;
        CannonballsRemaining = 10;
        targetsHit = 0;
        SetCannonballsRemainingText();
        SetTargetsHitText();
    }
    public void Lose()
    {
        isPlaying = false;
        UpdateFinalScores();
        welcomeScreen.ShowScoreScreen();//show the screen with scores once gameplay is finished.
        cannon.ResetRotation(); //reset the cannons position so it starts at original spot when starting over
        Start(); //reset things
    }
    public void LoseCannonBall()
    {
        CannonballsRemaining--;
        SetCannonballsRemainingText();
    }
    public void AddCannonBall()
    {
        CannonballsRemaining++;
        SetCannonballsRemainingText();
    }
    public void IncrementScore()
    {
        targetsHit++;
        SetTargetsHitText();
    }
    private void SetCannonballsRemainingText()
    {
        UICannonballsRemaining.text = "Cannonballs Remaining: " + CannonballsRemaining;
    }
    private void SetTargetsHitText()
    {
        UITargetsHit.text = "Targets Hit: " + targetsHit;
    }
    private void UpdateFinalScores()
    {
        if(targetsHit>highScore)
        {
            highScore = targetsHit;
        }
        UIScore.text = "Targets Hit: " + targetsHit;
        UIHighScore.text = "High Score: " + highScore;
    }
}
