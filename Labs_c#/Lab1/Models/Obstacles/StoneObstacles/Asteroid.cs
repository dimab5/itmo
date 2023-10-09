namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.StoneObstacles;

public class Asteroid : IStoneObstacle
{
    public Asteroid(int count)
    {
        Count = count;
    }

    public int Count { get; set; }

    public int DealDamage { get; } = 25;
}