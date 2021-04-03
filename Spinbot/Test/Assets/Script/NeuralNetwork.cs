///<author>Curt Henrichs</author>
///<date>11-9-17</date>

using System.Collections.Generic;

[System.Serializable]
public class NeuralLayer<T>
{
    public List<T> values;

    public NeuralLayer()
    {
        values = new List<T>();
    }

    public T this[int i]
    {
        get
        {
            return values[i];
        }

        set
        {
            if(i > values.Count)
            {
                throw new System.IndexOutOfRangeException();
            }
            else if (i == values.Count)
            {
                values.Add(value);
            }
            else
            {
                values[i] = value;
            }
        }
    }

    public int Length()
    {
        return values.Count;
    }

    public List<T> getList()
    {
        return values;
    }
}

[System.Serializable]
public class WeightVector
{
    public List<float> weights;

    public WeightVector()
    {
        weights = new List<float>();
    }

    public float this[int i]
    {
        get
        {
            return weights[i];
        }

        set
        {
            if (i > weights.Count)
            {
                throw new System.IndexOutOfRangeException();
            }
            else if (i == weights.Count)
            {
                weights.Add(value);
            }
            else
            {
                weights[i] = value;
            }
        }
    }

    public int Length()
    {
        return weights.Count;
    }

    public List<float> getList()
    {
        return weights;
    }
}

/// <summary>
/// Neural network was taken and modifed from an online tutorial (The One : https://youtu.be/Yq0SfuiOVYE)
/// The goal is to provide a simple neural network the peforms feed-forward calculation, has an asexual
/// genetic algorithm for mutation, and is able to generate a JSON formated version of its weight 
/// topology.
/// </summary>
[System.Serializable]
public class NeuralNetwork : System.IComparable
{
    /// <summary>
    /// Stores the fitness function that is computed for the agent
    /// </summary>
    public float fitness;
    /// <summary>
    /// The population of this entity
    /// </summary>
    public int currentPopulationID;
    /// <summary>
    /// The agent identity in the population
    /// </summary>
    public int currentEntityID;
    /// <summary>
    /// The agent's parent's population
    /// </summary>
    public int parentPopulationID;
    /// <summary>
    /// The agent's parent's identiy in parent's population
    /// </summary>
    public int parentEntityID;

    /// <summary>
    /// Cache the dimensions of the network topology
    /// </summary>
    public int[] layers;
    /// <summary>
    /// Neural structure used for feed-forward data storage
    /// </summary>
    private NeuralLayer<NeuralLayer<float>> neurons;
    /// <summary>
    /// Weights associated with each neuron in the network
    /// </summary>
    private NeuralLayer<NeuralLayer<WeightVector>> weights;

    public List<float> flattendedWeights;

    /// <summary>
    /// Constructor builds a newtork with initial, random weights
    /// </summary>
    /// <param name="layers">array of layer sizes</param>
    /// <param name="p_id">population id</param>
    /// <param name="e_id">entity id</param>
    public NeuralNetwork(int[] layers, int p_id = 0, int e_id = 0)
    {
        this.layers = new int[layers.Length];
        for (int i = 0; i < layers.Length; i++)
        {
            this.layers[i] = layers[i];
        }

        InitNeuron();
        InitWeights();

        fitness = 0;
        currentPopulationID = p_id;
        currentEntityID = e_id;
        parentPopulationID = -1;
        parentEntityID = -1;

        flattendedWeights = new List<float>();
        for (int i = 0; i < weights.Length(); i++)
        {
            for(int j = 0; j < weights[i].Length(); j++)
            {
                for(int k = 0; k < weights[i][j].Length(); k++)
                {
                    flattendedWeights.Add(weights[i][j][k]);
                }
            }
        }
    }

    /// <summary>
    /// Copy constructor deep copies the network weights and topology
    /// </summary>
    /// <param name="copyNetwork">network to be copied</param>
    /// <param name="p_id">population id</param>
    /// <param name="e_id">entity id</param>
    public NeuralNetwork(NeuralNetwork copyNetwork, int p_id = 0, int e_id = 0)
    {
        layers = new int[copyNetwork.layers.Length];
        for (int i = 0; i < layers.Length; i++)
        {
            layers[i] = copyNetwork.layers[i];
        }
        InitNeuron();
        InitWeights();
        CopyWeights(copyNetwork.weights);

        fitness = 0;
        currentPopulationID = p_id;
        currentEntityID = e_id;
        parentPopulationID = copyNetwork.currentPopulationID;
        parentEntityID = copyNetwork.currentEntityID;

        flattendedWeights = new List<float>();
        for (int i = 0; i < weights.Length(); i++)
        {
            for (int j = 0; j < weights[i].Length(); j++)
            {
                for (int k = 0; k < weights[i][j].Length(); k++)
                {
                    flattendedWeights.Add(weights[i][j][k]);
                }
            }
        }
    }

    /// <summary>
    /// Initialize the neural network topology
    /// </summary>
    private void InitNeuron()
    {
        //Neuron Initilization
        NeuralLayer<NeuralLayer<float>> neuronsList = new NeuralLayer<NeuralLayer<float>>();
        for (int i = 0; i < layers.Length; i++)
        {
            NeuralLayer<float> layer = new NeuralLayer<float>();
            for (int j = 0; j < layers[i]; j++)
            {
                layer[j] = 0;
            }
            neuronsList[i] = layer;
        }
        neurons = neuronsList;
    }

    /// <summary>
    /// Initialize the weight topology for the given neural network/
    /// Requires that the neural network array is already setup
    /// </summary>
    private void InitWeights()
    {
        NeuralLayer<NeuralLayer<WeightVector>> weightList = new NeuralLayer<NeuralLayer<WeightVector>>();

        for (int i = 1; i < layers.Length; i++)
        {
            NeuralLayer<WeightVector> layerWeightList = new NeuralLayer<WeightVector>();
            int neuronsInPreviousLayer = layers[i - 1];
            for (int j = 0; j < neurons[i].Length(); j++)
            {
                WeightVector neuronWeights = new WeightVector();
                for (int k = 0; k < neuronsInPreviousLayer; k++)
                {
                    neuronWeights[k] = UnityEngine.Random.Range(-1.0f, 1.0f);
                }
                layerWeightList[j] = neuronWeights;
            }
            weightList[i-1] = layerWeightList;
    }
        weights = weightList;
    }

    /// <summary>
    /// Deep copies the weights of one network into this network
    /// </summary>
    /// <param name="copyWeights">the other weights to be copied</param>
    private void CopyWeights(NeuralLayer<NeuralLayer<WeightVector>> copyWeights)
    {
        for (int i = 0; i < weights.Length(); i++)
        {
            for (int j = 0; j < weights[i].Length(); j++)
            {
                for (int k = 0; k < weights[i][j].Length(); k++)
                {
                    weights[i][j][k] = copyWeights[i][j][k];
                }
            }
        }
    }

    /// <summary>
    /// Processes the network for one time step
    /// </summary>
    /// <param name="inputs">Input layer to network data</param>
    /// <returns>output result layer of network</returns>
    public float[] FeedForward(float[] inputs)
    {
        for (int i = 0; i < inputs.Length; i++)
        {
            neurons[0][i] = inputs[i];
        }

        for (int i = 1; i < layers.Length; i++)
        {
            for (int j = 0; j < neurons[i].Length(); j++)
            {
                float value = 0.25f;
                
                for (int k = 0; k < neurons[i - 1].Length(); k++)
                {
                    value += weights[i - 1][j][k] * neurons[i - 1][k];
                }      

                neurons[i][j] = (float)(System.Math.Tanh(value));
            }
        }  

        return neurons[neurons.Length() - 1].getList().ToArray();
    }

    /// <summary>
    /// Genetic algorithm uses mutation whereby copies of current
    /// organism are made with a possible mutation
    /// </summary>
    public void Mutate()
    {
        for (int i = 0; i < weights.Length(); i++)
        {
            for (int j = 0; j < weights[i].Length(); j++)
            {
                for (int k = 0; k < weights[i][j].Length(); k++)
                {
                    float weight = weights[i][j][k];

                    float randomNumber = UnityEngine.Random.Range(0, 1000f);

                    if (randomNumber <= 2f)
                    {
                        weight *= -1;
                    }
                    else if(randomNumber <= 4f)
                    {
                        weight = UnityEngine.Random.Range(-0.5f, 0.5f);
                    }
                    else if(randomNumber <= 6f)
                    {
                        float factor = UnityEngine.Random.Range(0f, 1f) + 1f;
                        weight *= factor;
                    }
                    else if(randomNumber <= 8f)
                    {
                        float factor = UnityEngine.Random.Range(0f, 1f);
                        weight *= factor;
                    }

                    weights[i][j][k] = weight;
                }
            }
        }
    }

    /// <summary>
    /// Genetic algorithm uses crossover whereby copies of weights from one
    /// organism can be taken from another partner (other)
    /// </summary>
    /// <param name="other">Partner for genetic crossover</param>
    public void Crossover(NeuralNetwork other)
    {
        for (int i = 0; i < other.weights.Length(); i++)
        {
            for (int j = 0; j < other.weights[i].Length(); j++)
            {
                for (int k = 0; k < other.weights[i][j].Length(); k++)
                {
                    float random = UnityEngine.Random.Range(0f, 1000f);
                    if(random < 10)
                    {
                        weights[i][j][k] = other.weights[i][j][k];
                    }
                }
            }
        }
    }

    /// <summary>
    /// Increment the fitness factor by input
    /// </summary>
    /// <param name="fit">increment (or decrement) amount</param>
    public void AddFitness(float fit)
    {
        fitness += fit;
    }

    /// <summary>
    /// Comparision of fitness with another network for easy sorting
    /// </summary>
    /// <param name="other">Other network to compare to</param>
    /// <returns></returns>
    public int CompareTo(object other)
    {

        if(other.GetType() == typeof(NeuralNetwork))
        {
            if (other == null) return 1;

            if (fitness > ((NeuralNetwork)(other)).fitness)
            {
                return 1;
            }
            else if (fitness < ((NeuralNetwork)(other)).fitness)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }else
        {
            return -2;
        }
    }
}

