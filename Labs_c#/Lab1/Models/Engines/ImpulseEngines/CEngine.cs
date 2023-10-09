namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;

public class CEngine : IImpulseEngine
{
    private const int CEngineFuelConsumption = 100;
    private const int CSpeed = 50;
    private const int StartEngine = 50;

    public CEngine()
    {
    }

    public int FuelConsumption(int distance)
    {
        return (distance * CEngineFuelConsumption) + StartEngine;
    }

    public int Speed(int distance)
    {
        return CSpeed;
    }
}