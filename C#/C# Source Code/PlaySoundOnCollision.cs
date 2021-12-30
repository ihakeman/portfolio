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