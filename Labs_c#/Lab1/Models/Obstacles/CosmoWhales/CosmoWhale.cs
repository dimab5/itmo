namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.CosmoWhales;

public class CosmoWhale : ICosmoWhale
{
    public CosmoWhale(int count)
    {
        Count = count;
    }

    public int Count { get; set; }

    public int DealDamage { get; } = 500;
}