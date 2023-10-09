namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.StoneObstacles;

public class Meteorite : IStoneObstacle
{
    public Meteorite(int count)
    {
        Count = count;
    }

    public int Count { get; set; }

    public int DealDamage { get; } = 50;
}