using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public interface IObstaclesCollect
{
    public void DealDamage(IReadOnlyList<IObstacle> obstacles);
}