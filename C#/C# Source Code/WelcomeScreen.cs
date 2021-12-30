using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WelcomeScreen : MonoBehaviour
{
    public CanvasGroup WelcomeScreenCanvasGroup;
    public CanvasGroup RulesScreenCanvasGroup;
    public CanvasGroup ControlsScreenCanvasGroup;
    public CanvasGroup ScoreScreenCanvasGroup;
    public Game game;

    // Start is called before the first frame update
    void Start()
    {
        game.isPlaying = false;
        Show(WelcomeScreenCanvasGroup);
        Hide(RulesScreenCanvasGroup);
        Hide(ControlsScreenCanvasGroup);
        Hide(ScoreScreenCanvasGroup);
    }
    public void OnPlayButtonClick()
    {
        Hide(WelcomeScreenCanvasGroup);
        Hide(RulesScreenCanvasGroup);
        Hide(ControlsScreenCanvasGroup);
        Hide(ScoreScreenCanvasGroup);
        game.isPlaying = true;
    }
    public void OnRulesScreenButtonClick()
    {
        Hide(WelcomeScreenCanvasGroup);
        Hide(ControlsScreenCanvasGroup);
        Show(RulesScreenCanvasGroup);
        Hide(ScoreScreenCanvasGroup);
    }
    public void OnControlsScreenButtonClick()
    {
        Hide(WelcomeScreenCanvasGroup);
        Hide(RulesScreenCanvasGroup);
        Show(ControlsScreenCanvasGroup);
        Hide(ScoreScreenCanvasGroup);
    }
    public void OnBackButtonClick()
    {
        Show(WelcomeScreenCanvasGroup);
        Hide(RulesScreenCanvasGroup);
        Hide(ControlsScreenCanvasGroup);
        Hide(ScoreScreenCanvasGroup);
    }
    public void ShowScoreScreen()
    {
        Hide(WelcomeScreenCanvasGroup);
        Hide(RulesScreenCanvasGroup);
        Hide(ControlsScreenCanvasGroup);
        Show(ScoreScreenCanvasGroup);
    }
    public void OnLoss()
    {
        game.isPlaying = false;
        Show(ScoreScreenCanvasGroup);
    }
    public void OnXButtonClick()
    {//unused since button was turned off after switching the build settings to windowed instead of full screen, but left here in case I want to revert at some point
        Debug.Log("Quit");
        Application.Quit();
    }
    private void Show(CanvasGroup canvasGroup)
    {
        canvasGroup.alpha = 1;
        canvasGroup.interactable = true;
        canvasGroup.blocksRaycasts = true;
    }
    private void Hide(CanvasGroup canvasGroup)
    {
        canvasGroup.alpha = 0;
        canvasGroup.interactable = false;
        canvasGroup.blocksRaycasts = false;
    }

}
