///<author>Curt Henrichs</author>
///<date>2-26-18</date>

using UnityEngine;

/// <summary>
/// UI handler for training parameters that affect the population manager
/// </summary>
public class DisplayParams : MonoBehaviour {

    /// <summary>
    /// Link to population manager script to save on lookup
    /// </summary>
    private PopulationManager manager;

    /// <summary>
    /// Get link to manager script, initialize to not run
    /// </summary>
	void Start () {
        manager = this.GetComponent<PopulationManager>();
        manager.Run = false;
    }

    /// <summary>
    /// Adjust timescale of training simulation by value (bounded 0 to 100)
    /// </summary>
    /// <param name="value">new time scale to apply 0 to 100 (min,max)</param>
    public void SetSimulationSpeed(float value)
    {
        manager.TIME_SCALE = value;
    }

    /// <summary>
    /// Adjust the run status of the population manager training algorithm.
    /// </summary>
    /// <param name="state"></param>
    public void SetToggleRun(bool state)
    {
        manager.Run = state;
    }
}
