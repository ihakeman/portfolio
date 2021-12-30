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
