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

public class ParticleEffects : MonoBehaviour
{
    public GameObject DestroyParticle;
    public virtual void CreateParticleEffect()
    {
        Instantiate(DestroyParticle, transform.position, Quaternion.identity);
    }
}
