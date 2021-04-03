using UnityEngine;

public class Motor : MonoBehaviour {

    /// <summary>
    /// Unity editable applied torque constant per fixed update while active
    /// simulates the motor as being on or off as the motor is attached to a relay
    /// </summary>
    public float TORQUE;
    /// <summary>
    /// Position that the torque is to be applied so that it is actually applied on the driven
    /// wheel as opposed to the centroid.
    /// </summary>
    public Transform FORCE_POSITION;

    public void ApplyTorque()
    {
        Rigidbody rb = GetComponent<Rigidbody>();
        Vector3 force = -1 * FORCE_POSITION.right * TORQUE;
        rb.AddForceAtPosition(force, FORCE_POSITION.position);
    }
}
