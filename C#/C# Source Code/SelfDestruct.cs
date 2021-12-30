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
