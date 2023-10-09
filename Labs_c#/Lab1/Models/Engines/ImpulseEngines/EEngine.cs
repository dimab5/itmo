using System;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;

public class EEngine : IImpulseEngine
{
    private const int EEngineFuelConsumption = 200;
    private const int StartEngine = 100;

    public EEngine()
    {
    }

    public int FuelConsumption(int distance)
    {
        return (distance * EEngineFuelConsumption) + StartEngine;
    }

    public int Speed(int distance)
    {
        return (int)Math.Exp(distance);
    }
}