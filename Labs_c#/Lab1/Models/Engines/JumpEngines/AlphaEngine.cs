namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;

public class AlphaEngine : IJumpEngine
{
    public AlphaEngine()
    {
    }

    public int Speed { get; } = 100;
    public int RangeTravel { get; set; } = 500;

    public int FuelConsumption(int distance)
    {
        return distance;
    }
}