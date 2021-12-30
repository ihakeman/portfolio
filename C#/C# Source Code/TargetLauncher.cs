/*
# Range from https://docs.unity3d.com/ScriptReference/Random.Range.html
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TargetLauncher : MonoBehaviour
{
	public int LaunchSpeed = 700;
	private bool isLeftLaunchPosition = true; //if true, it launches from left, if not it launches from right
	public GameObject TargetPrefab;
	public GameObject InstantiatedTarget;
	public GameObject BottomRightLaunchPosition;
	public GameObject BottomLeftLaunchPosition;
	public Game game;
	private int launchAngle;
	private GameObject[] TargetsInPlay;
	void Update()
	{
		if (game.isPlaying)
        {
            MakeTargetIfNoneExist();
        }
        else
		{
			DestroyTargetIfItExists();
        }
    }

    private void DestroyTargetIfItExists()
	{//if game isn't playing and there are still targets, get rid of them
		TargetsInPlay = GameObject.FindGameObjectsWithTag("Target");
        if (TargetsInPlay.Length > 0)
        {
            Destroy(TargetsInPlay[0]);
        }
    }

    private void MakeTargetIfNoneExist()
	{//find if there are targets, and if not, make one
		TargetsInPlay = GameObject.FindGameObjectsWithTag("Target");
        if (TargetsInPlay.Length == 0)
        {
            GenerateTarget();
        }
    }

    private void GenerateTarget()
	{
		GenerateLaunchAngle();
		GameObject newTarget = Instantiate(TargetPrefab, GetLaunchPosition(), Quaternion.identity);//make the target object
		newTarget.transform.SetParent(gameObject.transform);//make the target a child of the target launcher
		GetComponentInChildren<Target>().Launch(launchAngle, LaunchSpeed);	//launch the target	
	}
	private Vector3 GetLaunchPosition()
	{
		if (isLeftLaunchPosition)
		{//launch from the left position
			isLeftLaunchPosition = false;//swap the position for next time
			return new Vector3(BottomLeftLaunchPosition.transform.position.x, BottomLeftLaunchPosition.transform.position.y, 
				BottomLeftLaunchPosition.transform.position.z + Random.Range(0, 7));//adjust the z position to a random distance 0 to 6
		}
		else //same but with the right side values for the launch position
        {
			isLeftLaunchPosition = true;
			return new Vector3(BottomRightLaunchPosition.transform.position.x, BottomRightLaunchPosition.transform.position.y, 
				BottomRightLaunchPosition.transform.position.z + Random.Range(0, 7));
        }
}
	private void GenerateLaunchAngle()
	{
		if (isLeftLaunchPosition)
			launchAngle = Random.Range(45, 85);//launch angle is up and to the right
		else
			launchAngle = Random.Range(95, 135);//launch angle is up and to the left
	}
}

