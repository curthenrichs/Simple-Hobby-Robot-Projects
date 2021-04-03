///<author>Curt Henrichs</author>
///<date>2-26-18</date>

using UnityEngine;

/// <summary>
/// Handles the behavior of the distraction targets used on latter training entities to
/// prove the correct response to sensor varience.
/// </summary>
public class Distractions : MonoBehaviour {

	/// <summary>
    /// Initially set all targets included to off
    /// </summary>
	void Start () {
		foreach(Transform child in transform)
        {
            child.gameObject.SetActive(false);
        }
	}
	
    /// <summary>
    /// Set the state of targets (enabled/disabled) on UI change
    /// </summary>
    /// <param name="state">UI Toggle parameter</param>
    public void SetDistractionStatus(bool state)
    {
        foreach (Transform child in transform)
        {
            child.gameObject.SetActive(state);
        }
    }
}
