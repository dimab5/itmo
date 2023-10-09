namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;

public class GammaEngine : IJumpEngine
{
    public GammaEngine()
    {
    }

    public int Speed { get; } = 100;
    public int RangeTravel { get; set; } = 1500;

    public int FuelConsumption(int distance)
    {
        return distance * distance;
    }
}