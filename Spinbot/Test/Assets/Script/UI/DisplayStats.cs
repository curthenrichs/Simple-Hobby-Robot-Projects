
using UnityEngine;


public class DisplayStats : MonoBehaviour {

    public GameObject epochStatsObject;
    public GameObject currentStatsObject;

    private DD_DataDiagram epochStatsGraph;
    private DD_DataDiagram currentStatsGraph;
    private GameObject epochFitLine;
    private GameObject currentFitLine;

    private int individual = 0;

	void Start () {

        currentStatsGraph = currentStatsObject.GetComponentInChildren<DD_DataDiagram>();
        epochStatsGraph = epochStatsObject.GetComponentInChildren<DD_DataDiagram>();

        currentFitLine = currentStatsGraph.AddLine("fitness", Color.red);
        epochFitLine = epochStatsGraph.AddLine("fitness", Color.red);

        currentStatsGraph.InputPoint(currentFitLine, new Vector2(-1, 0));
        epochStatsGraph.InputPoint(epochFitLine, new Vector2(-1, 0));
    }

    public void UpdateCurrentFitness(float fitness)
    {
        currentStatsGraph.InputPoint(currentFitLine, new Vector2(individual, fitness));
        individual++;
    }

    public void UpdateEpochFitness(float fitness, float epoch)
    {
        epochStatsGraph.InputPoint(epochFitLine, new Vector2(epoch, fitness));
    }
}
