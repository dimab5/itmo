namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;

public interface IJumpEngine
{
    int Speed { get; }
    int RangeTravel { get; set; }
    int FuelConsumption(int distance);
}