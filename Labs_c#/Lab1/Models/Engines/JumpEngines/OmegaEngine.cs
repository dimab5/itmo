using System;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;

public class OmegaEngine : IJumpEngine
{
    public OmegaEngine()
    {
    }

    public int Speed { get; } = 100;
    public int RangeTravel { get; set; } = 1000;

    public int FuelConsumption(int distance)
    {
        return distance * (int)Math.Log2(distance);
    }
}