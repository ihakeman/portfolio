/*
# I tried using these for rotation before finding another solution: https://docs.unity3d.com/ScriptReference/Transform-eulerAngles.html https://docs.unity3d.com/ScriptReference/Transform-rotation.html 
#                                                                   https://learn.unity.com/tutorial/translate-and-rotate#5c8a44c2edbc2a001f47ce1e https://learn.unity.com/project/c-survival-guide-rotations
# Input related stuff from: https://docs.unity3d.com/ScriptReference/Input.GetKey.html and https://docs.unity3d.com/ScriptReference/Input.html keycodes found by guess and check in Visual studio
# Changing the parent of an object https://forum.unity.com/threads/instantiate-as-child.535182/
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Cannon : MonoBehaviour
{
    public CannonBall CannonBallPrefab;
    CannonBall cannonBall;
    public Transform FiringPoint;
    public Game game;
    public AudioClip ShootSound;
    private AudioSource source;
    private AudioSource GeneralSource;
    private float movementIncrement = 0.5f;
    public CannonBarrel barrel;
    public Transform FlashPoint;
    public GameObject FlashPrefab;
    private void Start()
    {
        source = gameObject.GetComponent<AudioSource>();
        GeneralSource = GameObject.FindGameObjectWithTag("MovementSound").GetComponent<AudioSource>();//find the audio source just for the movement sound
    }//different audio sources used so that the volume of each sound could be adjusted independantly
    public void ResetRotation()
    {
        float x;
        float y;
        if (transform.rotation.x > 300)//if the angle is >300 it is a negative degrees, so you need to rotate that much in the positive direction
            x = transform.rotation.x;
        else
            x = -transform.rotation.x;//if not >300, it needs to rotate that many degrees in the negative direction
        if (transform.rotation.y > 300)
            y = transform.rotation.y;
        else
            y = -transform.rotation.y;
        transform.rotation = Quaternion.Euler(x,y,0);//rotate the amount of degrees above so that it is back to the starting point
    }
    void Update()
    {
        if (game.isPlaying)
        {
            CheckForShooting();
            CheckIfMovementSoundNeedsChanging();
            ExecuteApplicableMovements();
        }
        else
            GeneralSource.Stop();//if not playing, ensure that the movement sound for the cannon does not continue
    }

    private void CheckIfMovementSoundNeedsChanging()
    {
        if (Input.GetKeyDown(KeyCode.S) || Input.GetKeyDown(KeyCode.W) || Input.GetKeyDown(KeyCode.A) || Input.GetKeyDown(KeyCode.D) || Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.DownArrow))
        {//if the user is calling for movement, ensure that the sound effect is playing (in this case the audio source has the clip and is looping it when playing)
            GeneralSource.Play();
        }
        if (!Input.GetKey(KeyCode.S) && !Input.GetKey(KeyCode.W) && !Input.GetKey(KeyCode.A) && !Input.GetKey(KeyCode.D) && !Input.GetKey(KeyCode.RightArrow) && !Input.GetKey(KeyCode.LeftArrow) && !Input.GetKey(KeyCode.UpArrow) && !Input.GetKey(KeyCode.DownArrow))
        {//if the user is not calling for any movements at all, ensure that the sound effect is not playing.
            GeneralSource.Stop();
        }
    }

    private void CheckForShooting()
    {
        if (Input.GetKeyDown(KeyCode.Space) && game.CannonballsRemaining > 0)//if the user calls for a shot and they have any balls left
        {
            Shoot();
        }
    }

    private void ExecuteApplicableMovements()
    {
        if (Input.GetKey(KeyCode.A) || Input.GetKey(KeyCode.LeftArrow))//A or left arrow
        {
            RotateLeft();
        }
        if (Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.RightArrow)) //same as above but with d and right arrow
        {
            RotateRight();
        }
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.UpArrow))//same as above with w and up arrow
        {
            RotateUp();
        }
        if (Input.GetKey(KeyCode.S) || Input.GetKey(KeyCode.DownArrow))//same as above but with s and down arrow
        {
            RotateDown();
        }
    }

    private void RotateDown()
    {
        Vector3 newRotation = transform.rotation.eulerAngles; //get the current rotations
        if (newRotation.x > 329)//if between the bounds of the cannons movement
            newRotation.x += movementIncrement;//change the correct direction by the increment amount 
        transform.rotation = Quaternion.Euler(newRotation);//set the rotation of the 
    }

    private void RotateUp()
    {
        Vector3 newRotation = transform.rotation.eulerAngles;
        if (newRotation.x > 330 || newRotation.x < 21)//if between the bounds of the cannons movement
            newRotation.x -= movementIncrement;
        transform.rotation = Quaternion.Euler(newRotation);
    }

    private void RotateRight()
    {
        Vector3 newRotation = transform.rotation.eulerAngles;
        if (newRotation.y < 25 || newRotation.y > 333)//if between the bounds of the cannons movement
            newRotation.y += movementIncrement;
        transform.rotation = Quaternion.Euler(newRotation);
    }

    private void RotateLeft()
    {
        Vector3 newRotation = transform.rotation.eulerAngles;
        if (newRotation.y < 26 || newRotation.y > 334)//if between the bounds of the cannons movement
            newRotation.y -= movementIncrement;//move the increment amount each frame
        transform.rotation = Quaternion.Euler(newRotation);//make the rotation (in this case the movement is only changed in the y direction)
    }

    private void Shoot()
    {
        MakeCannonBallandShootIt();
        game.LoseCannonBall();//lose one from the amount you have left (gets added back in the cannonball script if it hits the target)
        source.PlayOneShot(ShootSound);
        barrel.Recoil();
        Instantiate(FlashPrefab, FlashPoint.position, Quaternion.identity);//make the cannon glow momentarily with a flash.
    }

    private void MakeCannonBallandShootIt()
    {
        cannonBall = Instantiate(CannonBallPrefab, FiringPoint.position, Quaternion.identity);//make the cannon ball object from the prefab, in the firing point position
        cannonBall.game = game;//give it access to the game which its script needs to control the amount of cannon balls remaining
        cannonBall.transform.SetParent(gameObject.transform);//make it a child of this game object
        cannonBall.cannonParent = FiringPoint.transform;//make it a child of the firing point so that it always fires straight from the end of the cannon, and not just straight in the z direction
        cannonBall.ShootCannonBall();//actually shoot the cannonball
    }
}
