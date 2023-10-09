using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;

public interface ISpace
{
    int Length { get; }
    IReadOnlyList<IObstacle> GetListObstacles();
    void AddObstacle(IObstacle obstacle);
    IResultPassingSpace ShipResult(IShip ship);
}