namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.AntimatterFlares;

public class AntimatterFlare : IAntimatterFlare
{
    public AntimatterFlare(int count)
    {
        Count = count;
    }

    public int Count { get; set; }

    public int DealDamage { get; } = 1;
}