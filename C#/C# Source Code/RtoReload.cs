/*
# Name: Ian Hakeman
# Student ID#: 2338119
# Chapman email: hakeman@chapman.edu
# Course Number and Section: 236/02
# Assignment: Final Project
# Code copied from Brickbuster
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class RtoReload : MonoBehaviour
{
    // Update is called once per frame
    void Update()
    {
        if(Input.GetKeyDown(KeyCode.R))
        {
            SceneManager.LoadScene(0);
        }
    }
}
