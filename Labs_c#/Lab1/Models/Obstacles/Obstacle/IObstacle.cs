namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;

public interface IObstacle
{
    int Count { get; protected set; }
    int DealDamage { get; }
}