///<author>Curt Henrichs</author>
///<date>11-9-17</date>

using UnityEngine;

/// <summary>
/// LightSensor generates a light value from all targets within the field of view.
/// This object should be used so that the agent can see the targets.
/// </summary>
public class LightSensor : MonoBehaviour {

    /// <summary>
    /// Unity adjustable field of view used to control the gausian distribution
    /// </summary>
    public float MAX_FOV_ANGLE = 30;
    /// <summary>
    /// Unity adjustable constant to scale the resulting light value before averaging
    /// </summary>
    public float LIGHT_SCALER = 1;
    /// <summary>
    /// Current light value generated from all targets in the last update frame
    /// </summary>
    public float AverageLight { get; private set; }

    /// <summary>
    /// Update function find all instances of the target and process each for its "light"
    /// value which in effect is the distance and angle the sensor makes with the target.
    /// </summary>
	void Update () {

        //the cost of this is acceptable for now
        GameObject[] targets = GameObject.FindGameObjectsWithTag("Target");

        //generate average light value
        AverageLight = 0;
        for (int i = 0; i < targets.Length; i++)
        {
			if (targets[i].activeSelf) {
				//calculate direction to the target
				Vector3 targetPosition = targets[i].GetComponent<Transform>().position;
				targetPosition.y = 0;
				Vector3 currentPosition = transform.position;
				currentPosition.y = 0;
				Vector3 targetDirection = targetPosition - currentPosition;

				//calculate the angle and distance to the target
				float angle = Vector3.Angle(transform.up, targetDirection);
				float distance  = Mathf.Abs(Vector3.Distance(targetPosition, currentPosition));

				//calculate the light value as a factor of distance and the gaussian distribution relative
				// to the angle. Finally set an upper and lower bound for the result.
				float light = 1 / ((distance <= 0) ? 1 : distance);
				float angleEffect = Mathf.Exp(-1 * (Mathf.PI / (2 * Mathf.Pow(MAX_FOV_ANGLE,2))) * Mathf.Pow(angle, 2));
				light = LIGHT_SCALER * light * angleEffect;
				if(light > 1)
				{
					light = 1;
				}
				else if(light < 0)
				{
					light = 0;
				}
				AverageLight += light;
			}
        }
        AverageLight /= targets.Length;
	}
}
