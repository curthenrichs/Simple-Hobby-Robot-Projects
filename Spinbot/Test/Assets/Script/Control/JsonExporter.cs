
using UnityEngine;
using System;
using System.IO;
using System.Collections.Generic;

[System.Serializable]
public class EntityCollection
{
    public List<NeuralNetwork> entities;
}

public class JsonExporter : MonoBehaviour {

    string path;
    EntityCollection collection;


    void Start ()
    {
        path = Application.dataPath + "/EntityData/Entity_" + GetEpochTime() + ".json";
        collection = new EntityCollection();
        collection.entities = new List<NeuralNetwork>();
    }

    public void AddEntity(NeuralNetwork net)
    {
        collection.entities.Add(net);
    }

    public void ExportJson()
    {
        File.WriteAllText(path,JsonUtility.ToJson(collection));
    }

    public long GetEpochTime()
    {
        DateTime dtCurTime = DateTime.Now;
        DateTime dtEpochStartTime = Convert.ToDateTime("1/1/1970 8:00:00 AM");
        TimeSpan ts = dtCurTime.Subtract(dtEpochStartTime);

        long epochtime;
        epochtime = ((((((ts.Days * 24) + ts.Hours) * 60) + ts.Minutes) * 60) + ts.Seconds);
        return epochtime;
    }
}
