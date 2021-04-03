using UnityEngine;

public class BoundaryCollision : MonoBehaviour {

    public bool playerHitBoundary = false;

    /// <summary>
    /// Unity collider function means agent has hit the wall
    /// </summary>
    /// <param name="other"></param>
    void OnCollisionEnter(Collision other)
    {
        if(other.transform.tag.Equals("Player"))
        {
            playerHitBoundary = true;
        }
    }

}
