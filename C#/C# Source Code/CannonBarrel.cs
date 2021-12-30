/*
# Translate found at https://docs.unity3d.com/ScriptReference/Transform.Translate.html
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonBarrel : MonoBehaviour
{
    public void Recoil()//called by the cannon script
    {//move in the negative z direction for a short distance
        transform.Translate(new Vector3(0, -1, 0) * 0.2f);
        Invoke("ReverseDirection", 0.2f);
    }
    private void ReverseDirection()
    {//move back in the positive direction that same amount.
        transform.Translate(new Vector3(0,1,0)*0.2f);
    }
}
