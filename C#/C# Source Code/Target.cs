/*
# Name: Ian Hakeman
# Student ID#: 2338119
# Chapman email: hakeman@chapman.edu
# Course Number and Section: 236/02
# Assignment: Final Project
# Code copied from Brickbuster: using the add force method on the rigidbody.
# Converting degrees to the needed radians https://docs.unity3d.com/ScriptReference/Mathf.Rad2Deg.html
# Sin and cos https://docs.unity3d.com/ScriptReference/Mathf.Sin.html
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Target : MonoBehaviour
{
    public GameObject TargetPrefab;
    private Rigidbody physics;
    public void Launch(int LaunchAngle, int LaunchSpeed)
    {
        physics = GetComponent<Rigidbody>();//get the access to the rigidbody.
        //launch with constant speed using sin and cos and multiplying by launch. No z direction velocity.
        physics.AddForce(Mathf.Cos(Mathf.Deg2Rad*LaunchAngle) * LaunchSpeed, Mathf.Sin(Mathf.Deg2Rad*LaunchAngle) * LaunchSpeed, 0);
    }
    public void OnCollisionEnter(Collision collision)
    {//when it hits something it gets destroyed.
        Destroy(gameObject);
    }
}
