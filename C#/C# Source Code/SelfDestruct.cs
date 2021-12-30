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

public class SelfDestruct : MonoBehaviour
{//The object will destroy itself after delay amount of time.
    public float Delay = 1f;
    private void Start()
    {
        Destroy(gameObject, Delay);
    }
}
