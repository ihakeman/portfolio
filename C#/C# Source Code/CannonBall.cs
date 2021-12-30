using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonBall : ParticleEffects
{
    private float StartVelocity=1250f;
    private Rigidbody physics;
    public Transform cannonParent;
    public Game game;
    private AudioSource source;
    public AudioClip HitTargetSFX;
    public AudioClip MissedTargetSFX;


    private void Awake()
    {
        physics = GetComponent<Rigidbody>();
        source = GameObject.FindGameObjectWithTag("Sound").GetComponent<AudioSource>();//get access to the general audio source
    }
    public void ShootCannonBall()
    {
        transform.parent = null;//release from the cannon
        physics.isKinematic = false;
        physics.AddForce(cannonParent.transform.position*StartVelocity);//add velocity to the cannon ball
    }
    private void OnCollisionEnter(Collision collision)
    {
        if (gameObject.transform.position.z > 18.75)
        {//when it has a collision if it is passed the z that the targets could be, play the sound effect for hitting the forest,
            source.PlayOneShot(MissedTargetSFX);
            if(game.CannonballsRemaining<=0)
            {
                game.Lose();
            }
        }
        else
        {//if not past the z of the targets, it must have hit one so play the hit the target sound effect (and create the associated particle effect of the target)
            game.IncrementScore();
            game.AddCannonBall();
            source.PlayOneShot(HitTargetSFX);
            CreateParticleEffect();
        }
        Destroy(gameObject);//regardless of where it was, destroy the cannon  ball.
    }
}
