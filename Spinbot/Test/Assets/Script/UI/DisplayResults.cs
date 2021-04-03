///<author>Curt Henrichs</author>
///<date>2-26-18</date>

using UnityEngine;
using UnityEngine.UI;

/// <summary>
/// UI handler to display the current oeprational training results from the population manager
/// This is different from training statistics which note trends on the training data.
/// </summary>
public class DisplayResults : MonoBehaviour {

    /// <summary>
    /// Current population epoch
    /// </summary>
    public Text epoch;
    /// <summary>
    /// Current entity indentification
    /// </summary>
    public Text entity;
    /// <summary>
    /// UI field to note current state of population manager entity testing
    /// </summary>
    public Text state;
    /// <summary>
    /// UI field to note current quadrant under test
    /// </summary>
    public Text quadrant;
    /// <summary>
    /// UI field to note fitness
    /// </summary>
    public Text fitness;
    /// <summary>
    /// Link to PopulationManager script to save on lookup
    /// </summary>
    private PopulationManager manager;

    /// <summary>
    /// Get reference to population manager script for update function
    /// </summary>
	void Start () {
        manager = this.GetComponent<PopulationManager>();
	}
	
    /// <summary>
    /// Update the text with the new data from the population manager script
    /// </summary>
	void Update () {
        epoch.text = "Epoch: " + manager.Population_Count;
        entity.text = "Entity: " + manager.Current_Agent_Identity;
        state.text = "State: " + manager.currentState;
        quadrant.text = "Quadrant: " + manager.currentQuad;
        fitness.text = "Fitness: " + manager.current_fitness;
    }
}
