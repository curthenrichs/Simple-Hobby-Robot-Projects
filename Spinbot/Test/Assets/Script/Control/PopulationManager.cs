///<author>Curt Henrichs</author>
///<date>2-25-18</date>

using System;
using UnityEngine;

//TOOD Logging
//TODO UI / Visualization of data
//TODO Fitness function reevalutation

public class PopulationManager : MonoBehaviour {

//=============================================================================
//                                Constants
//=============================================================================

    /// <summary>
    /// Time to delay between trials in steps
    /// </summary>
    private const float DELAY_TIME_EXPIRE = 10.0f;
    /// <summary>
    /// Number of entities in each epoch
    /// </summary>
    private const int POPULATION_SIZE = 100;
    
    /// <summary>
    /// Population manager state-machine states for training neural agent 
    /// </summary>
    public enum State_e
    {
        RESET,  // Resets position of agent between trials
        RUN,    // Runs agent trial
        DELAY,  // Time after test to let physics of agent settle down
        END     // End of agent trial
    }

    /// <summary>
    /// Population manager quadrant trial state-machine for four-way testing
    /// of neural network
    /// </summary>
    public enum Quadrant_e
    {
        QUAD_1, // Quadrant 1 defined 0 to 90 deg
        QUAD_2, // Quadrant 2 defined 90 to 180 deg
        QUAD_3, // Quadrant 3 defined 180 t0 270 deg
        QUAD_4  // Quadrant 4 defined 270 to 360 (0) deg
    }

//=============================================================================
//                             Enviroment Links
//=============================================================================

    /// <summary>
    /// Link to gameobjecct representing the agent's target in the enviroment
    /// </summary>
    public GameObject target;
    /// <summary>
    /// Link to gameobject representing the agent's body in the enviroment
    /// </summary>
    public GameObject agent;
    /// <summary>
    /// Links to JSON export object which handles logging / storage
    /// </summary>
    public GameObject jsonExporterObject;

//=============================================================================
//                     Fitness Function Tuning Parameters
//=============================================================================

    /// <summary>
    /// Linear factor modifying the remaining distance for fitness function
    /// </summary>
    public float DISTANCE_FACTOR = 100f;
    /// <summary>
    /// Time simulation factor to control rate of physics simulation
    /// </summary>
    public float TIME_SCALE = 1;
    /// <summary>
    /// Runs the simulation else stays in a stalled state
    /// </summary>
    public bool Run = true;

//=============================================================================
//                           Training Status
//=============================================================================

    /// <summary>
    /// Current Epoch that training is in
    /// </summary>
    public int Population_Count = 0;
    /// <summary>
    /// Current entitiy in Epoch being tested
    /// </summary>
    public int Current_Agent_Identity = 0;
    /// <summary>
    /// Current state of training state-machine for given entity
    /// </summary>
    public State_e currentState;
    /// <summary>
    /// Current quadrant being tested on given entity
    /// </summary>
    public Quadrant_e currentQuad;
    /// <summary>
    /// Current evaluated fitness for the entity under test
    /// </summary>
    public float current_fitness = 0;

//=============================================================================
//                      Private Population Attributes
//=============================================================================

    /// <summary>
    /// Array of all entities within the current population
    /// </summary>
    private NeuralNetwork[] population;
    /// <summary>
    /// Counter to track steps to delay before next trial
    /// </summary>
    private float delayTime;
    /// <summary>
    /// End state fitness for each quadrant of entity under test
    /// </summary>
    private float[] fitness_quad = new float[4];
    /// <summary>
    /// 
    /// </summary>
    private float highestFitness = 0;

//=============================================================================
//                            Public Functions
//=============================================================================

    /// <summary>
    /// On initialization of the population manager the agent state machine will be
    /// reset and an initial epoch generated.
    /// </summary>
    void Start () {
        currentState = State_e.RESET;
        currentQuad = Quadrant_e.QUAD_1;
        GenerateNewPopulation();
        highestFitness = 0;
    }

    /// <summary>
    /// Runs population management state-machine that tests each individual entity against 
    /// four test cases (four quadrants). Additionally, the update function generates 
    /// another population.
    /// </summary>
	void Update () {

        if (Run)
        {
            //bind timescale attribute to time module
            if (Time.timeScale != TIME_SCALE)
            {
                Time.timeScale = TIME_SCALE;
            }

            //Iterate through each agent, for each run the life-cycle state machine. 
            //  At end generate new population
            if (Current_Agent_Identity < POPULATION_SIZE)
            {
                ControllerSingleShot agentCtrl = agent.GetComponent<ControllerSingleShot>();
                switch (currentState)
                {
                    case State_e.RESET:
                        MoveTarget(currentQuad);
                        agentCtrl.network = population[Current_Agent_Identity];
                        agentCtrl.Restart();
                        agentCtrl.Run();
                        currentState = State_e.RUN;
                        break;

                    case State_e.RUN:
                        if (agentCtrl.currentState == ControllerSingleShot.State_e.DEAD || agentCtrl.currentState == ControllerSingleShot.State_e.SUCCESS)
                        {
                            currentState = State_e.DELAY;
                            delayTime = 0;
                        }
                        current_fitness = CalculateFitness();
                        break;

                    case State_e.DELAY:
                        delayTime += Time.deltaTime;
                        if (delayTime >= DELAY_TIME_EXPIRE)
                        {
                            current_fitness = fitness_quad[(int)(currentQuad)] = CalculateFitness();
                            if (currentQuad >= Quadrant_e.QUAD_4)
                            {
                                currentState = State_e.END;
                            }
                            else
                            {
                                currentState = State_e.RESET;
                                currentQuad++;
                            }
                        }
                        break;

                    case State_e.END:
                        float f = AssignFitnessToAgent(fitness_quad);
                        if (f > highestFitness)
                        {
                            highestFitness = f;
                        }

                        NeuralNetwork net = agent.GetComponent<ControllerSingleShot>().network;
                        jsonExporterObject.GetComponent<JsonExporter>().AddEntity(net);

                        GetComponent<DisplayStats>().UpdateCurrentFitness(f);
                        currentState = State_e.RESET;
                        currentQuad = Quadrant_e.QUAD_1;
                        Current_Agent_Identity++;
                        break;
                }
            }
            //end of population, start next epoch
            else
            {
                Current_Agent_Identity = 0;
                SortPopulationByFitness();
                GenerateNextPopulation();

                GetComponent<DisplayStats>().UpdateEpochFitness(highestFitness, Population_Count);
            }
        }
        else
        {
            Time.timeScale = 0;
        }
    }

//=============================================================================
//                            Private Functions
//=============================================================================

    /// <summary>
    /// Calculates the current agent's fitness for the given trial. Function
    /// is dependent on if the agent is alive, dead, or successful resulting in
    /// higher fitness for hitting the target faster.
    /// </summary>
    /// <returns>current fitness of the agent's network</returns>
    private float CalculateFitness()
    {
        float fitness = 0;
        ControllerSingleShot agentCtrl = agent.GetComponent<ControllerSingleShot>();
        ControllerSingleShot.State_e agentState = agentCtrl.currentState;

        //calculate the distance between agent and target
        Vector3 targetPosition = target.transform.position;
        targetPosition.y = 0;
        Vector3 agentPosition = agent.transform.position;
        agentPosition.y = 0;
        float distance = Mathf.Abs(Vector3.Distance(targetPosition, agentPosition));
        Vector2 agentStartPosition = agentCtrl.startPosition;
        agentStartPosition.y = 0;
        float distanceFromStart = Mathf.Abs(Vector3.Distance(targetPosition, agentStartPosition));

        //calculate fitness as dependent on the state of the agent
        switch (agentState)
        {
            case ControllerSingleShot.State_e.ALIVE:
                fitness = (1 / (distance < 1 ? 1 : distance));
                break;
            case ControllerSingleShot.State_e.DEAD:
                fitness = (1 / (distance < 1 ? 1 : distance));
                break;
            case ControllerSingleShot.State_e.SUCCESS:
                fitness = 1 + (ControllerSingleShot.EXPIRATION_TIME - agentCtrl.elapsedTime) * (distanceFromStart / DISTANCE_FACTOR);
                break;
            case ControllerSingleShot.State_e.WAITING:
                fitness = 0;
                break;
            default:
                fitness = 0;
                break;
        }
        return fitness;
    }

    /// <summary>
    /// Assigns a fitness to the agent's neural network given tests fitness 
    /// value to be accumulated for overall fitness
    /// </summary>
    /// <param name="fitness_quad">Array of quadrants (tests)</param>
    private float AssignFitnessToAgent(float[] fitness_quad)
    {
        float retVal = 0;

        ControllerSingleShot agentCtrl = agent.GetComponent<ControllerSingleShot>();
        agentCtrl.network.fitness = 0;
        foreach(float f in fitness_quad)
        {
            agentCtrl.network.AddFitness(f);
            retVal += f;
        }
        return retVal / 4;
    }

    /// <summary>
    /// Sorts population so that the most fit agent is first
    /// </summary>
    private void SortPopulationByFitness()
    {
        Array.Sort(population);
    }

    /// <summary>
    /// Generates a random population for the starting epoch
    /// </summary>
    private void GenerateNewPopulation()
    {
        population = new NeuralNetwork[POPULATION_SIZE];
        for(int i = 0;  i < population.Length; i++)
        {
            population[i] = new NeuralNetwork(ControllerSingleShot.NETWORK_TOPOLOGY,Population_Count,i);
        }
    }

    /// <summary>
    /// Generates the next population based on the fitest agents in the current population
    /// This function expects that population is presorted.
    /// </summary>
    private void GenerateNextPopulation()
    {
        NeuralNetwork[] newPop = new NeuralNetwork[POPULATION_SIZE];
        Population_Count++;

        //first 10 are kept as they are
        for (int i = 0; i < 10; i++)
        {
            newPop[i] = new NeuralNetwork(population[population.Length - i - 1], Population_Count, i);
        }

        //each of the top 9 produces 10 children
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                int index = i * 10 + 10 + j;
                newPop[index] = new NeuralNetwork(newPop[i], Population_Count, index);
                newPop[index].Crossover(newPop[j]);
                newPop[index].Mutate();
            }
        }

        population = newPop;
    }

    /// <summary>
    /// Moves the agents target to a random point in the specified quadrant. This
    /// will provide novel training data to the model
    /// </summary>
    /// <param name="qaudrant">Enumeration specifing 2D cartesian coordinate</param>
    private void MoveTarget(Quadrant_e qaudrant)
    {
        float angle_min, angle_max;
        switch (qaudrant)
        {
            case Quadrant_e.QUAD_1:
                angle_min = 0;
                angle_max = 90;
                break;
            case Quadrant_e.QUAD_2:
                angle_min = 90;
                angle_max = 180;
                break;
            case Quadrant_e.QUAD_3:
                angle_min = 180;
                angle_max = 270;
                break;
            case Quadrant_e.QUAD_4:
                angle_min = 270;
                angle_max = 360;
                break;
            default:
                angle_min = 0;
                angle_max = 0;
                break;
        }

        float radius = UnityEngine.Random.Range(8f, 12f);
        float angle = UnityEngine.Random.Range(angle_min, angle_max);
        Vector3 newPostion = new Vector3(radius * Mathf.Cos(Mathf.Deg2Rad * angle), 
                                         0.5f, 
                                         radius * Mathf.Sin(Mathf.Deg2Rad * angle));
        target.transform.position = newPostion;
    }
}
