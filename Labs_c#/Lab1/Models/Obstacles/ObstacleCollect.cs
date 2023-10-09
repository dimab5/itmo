using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public class ObstacleCollect : IObstaclesCollect
{
    private IShip ship;

    public ObstacleCollect(IShip ship)
    {
        this.ship = ship;
    }

    public void DealDamage(IReadOnlyList<IObstacle> obstacles)
    {
        ship.GetDamage(obstacles);
    }
}