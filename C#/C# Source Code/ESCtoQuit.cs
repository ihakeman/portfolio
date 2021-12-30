/*
# Name: Ian Hakeman
# Student ID#: 2338119
# Chapman email: hakeman@chapman.edu
# Course Number and Section: 236/02
# Assignment: Final Project
# Code copied from Brickbuster but with a different keycode.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ESCtoQuit : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Debug.Log("ESC to Quit");
            Application.Quit();
        }
    }
}
