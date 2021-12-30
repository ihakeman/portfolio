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

public class PlaySoundOnCollision : MonoBehaviour
{
    public AudioClip HitSFX;
    private AudioSource source;
    // Start is called before the first frame update
    void Start()
    {
        source = GameObject.FindGameObjectWithTag("Sound").GetComponent<AudioSource>();
    }

    private void OnCollisionEnter(Collision collision)
    {
        source.PlayOneShot(HitSFX);
    }
}