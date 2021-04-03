///<author>Curt Henrichs</author>
///<date>11-9-17</date>
///

// Functional Structure 1
// [9,5,1]
// Functional Structure 2
// [9, 15, 5, 1]



using UnityEngine;

/// <summary>
/// Controller is the enviromentally embedded agent that owns a neural network to naviagate
/// around the space given its light sensors. This agent is used in conjuction with an external
/// manager who is responsible for manipulating the state machine so that a genetic simulation
/// can be performed.
/// </summary>
public class ControllerSingleShot : MonoBehaviour
{

    /// <summary>
    /// Network input layer size for network topology
    /// </summary>
    public const int NETWORK_INPUT_SIZE = 9;
    /// <summary>
    /// 
    /// </summary>
    public const float MOTOR_ACTIVATION_THRESHOLD = 0.5f;
    /// <summary>
    /// Network output layer size for network topology
    /// </summary>
    public const int NETWORK_OUTPUT_SIZE = 1;
    /// <summary>
    /// Time before expiration for the entity test
    /// </summary>
    public const float EXPIRATION_TIME = 30.0f;

    /// <summary>
    /// States for the agents state machine so that the population manager has a hook into control
    /// </summary>
    public enum State_e
    {
        WAITING,    // State placed after reset but before activation
        ALIVE,      // Running neural network for test
        DEAD,       // Timer expired and did not get food
        SUCCESS     // Found food, end of test
    };

    /// <summary>
    /// Current Network topology defention
    /// </summary>
    public static readonly int[] NETWORK_TOPOLOGY = { NETWORK_INPUT_SIZE, 5, NETWORK_OUTPUT_SIZE };

    /// <summary>
    /// Current network under test by the population manager. This network is used to
    /// map the light inputs to the motor output.
    /// </summary>
    public NeuralNetwork network { get; set; }
    /// <summary>
    /// Current age of the organism used to track its approach to death
    /// </summary>
    public float elapsedTime { get; private set; }
    /// <summary>
    /// The original position of this agent before the test so that it can be reset at end of test.
    /// </summary>
    public Vector3 startPosition { get; private set; }
    /// <summary>
    /// The orginal rotation of this agent before the test so that it can be reset at end of test.
    /// </summary>
    public Quaternion startRotation { get; private set; }
    /// <summary>
    /// State machine state for the agent so that it is only moving and reacting during its alive
    /// phase and so that the population manager can manage the experiment.
    /// </summary>
    public State_e currentState { get; private set; }
    /// <summary>
    /// If the neural network triggered movement then notify the manager
    /// </summary>
    public bool moved { get; private set; }

    /// <summary>
    /// Collection of the light sensor scripts which will act as inputs for the neural network
    /// </summary>
    private LightSensor[] lights;
    /// <summary>
    /// Previous light values from the sensors attached
    /// </summary>
    private float[] light_prev;
    /// <summary>
    /// Motor connection
    /// </summary>
    private Motor motor;


    /// <summary>
    /// Unity object start function will initialize the componetry so that the system will
    /// perform as expected during population testing.
    /// </summary>
    void Start()
    {
        network = new NeuralNetwork(NETWORK_TOPOLOGY);
        lights = GetComponentsInChildren<LightSensor>();
        motor = GetComponent<Motor>();

        startPosition = transform.position;
        startRotation = transform.rotation;

        currentState = State_e.DEAD;

        light_prev = new float[6];
        for (int i = 0; i < 6; i++)
        {
            light_prev[i] = 0;
        }
    }

    /// <summary>
    /// Unity object update function will track the age of the agent. If the agent is too old then
    /// the update function will kill it.
    /// </summary>
    void Update()
    {
        if (currentState == State_e.ALIVE)
        {
            elapsedTime += Time.deltaTime;
            if (elapsedTime >= EXPIRATION_TIME)
            {
                currentState = State_e.DEAD;
            }
        }
    }

    /// <summary>
    /// Unity object fixed update function for physics manipulation of agent. The neural network
    /// will be computed on each cycle that the bot is alive. The output can be observed as a
    /// torque on the bot.
    /// </summary>
    void FixedUpdate()
    {
        if (currentState == State_e.ALIVE)
        {
            //generate inputs for neural network
            float[] inputs = new float[NETWORK_INPUT_SIZE];
            for (int i = 0; i < inputs.Length; i++)
            {
                if (i < 3)
                {
                    inputs[i] = lights[i].GetComponent<LightSensor>().AverageLight;
                }
                else
                {
                    inputs[i] = light_prev[i - 3];
                }
            }

            //fill in old light values for next iteration
            for (int i = 0; i < 3; i++)
            {
                light_prev[i + 3] = light_prev[i];
                light_prev[i] = lights[i].GetComponent<LightSensor>().AverageLight;
            }

            //update network
            float[] outputs = network.FeedForward(inputs);

            //produce output
            if (outputs[0] <= MOTOR_ACTIVATION_THRESHOLD)
            {
                motor.ApplyTorque();
                moved = true;
            }
        }
    }

    /// <summary>
    /// Restarts the agents routine by moving it back to start position and setting the state
    /// to wait. The optional parameter is used to override the movement behavior.
    /// </summary>
    /// <param name="skipmove">Override the move back to start position behavior, normally false</param>
    public void Restart(bool skipmove = false)
    {
        currentState = State_e.WAITING;
        elapsedTime = 0;
        moved = false;
        if (!skipmove)
        {
            transform.position = startPosition;
            transform.rotation = startRotation;
        }
    }

    /// <summary>
    /// Sets the agents state to alive thereby starting the simulation
    /// </summary>
    public void Run()
    {
        currentState = State_e.ALIVE;
    }

    /// <summary>
    /// Unity trigger entered function will check for the agent hitting the target. If target is hit
    /// then the state is set to success noting that the simulation has ended.
    /// </summary>
    /// <param name="other"></param>
    void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Target") && currentState == State_e.ALIVE)
        {
            currentState = State_e.SUCCESS;
        }
    }
}