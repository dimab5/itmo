using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.StoneObstacles;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;

public class OrdinarySpace : ISpace
{
    public OrdinarySpace(int length, params IStoneObstacle[] obstacles)
    {
        Length = length;

        foreach (IStoneObstacle obstacle in obstacles)
        {
            for (int i = 0; i < obstacle.Count; i++)
            {
                AddObstacle(obstacle);
            }
        }
    }

    public int Length { get; set; }

    private List<IObstacle> Obstacles { get; } = new List<IObstacle>();

    public IReadOnlyList<IObstacle> GetListObstacles()
    {
        return Obstacles.AsReadOnly();
    }

    public void AddObstacle(IObstacle obstacle)
    {
        Obstacles.Add(obstacle);
    }

    public IResultPassingSpace ShipResult(IShip ship)
    {
        decimal time = 0;
        int fuel = 0;

        ship.GetDamage(GetListObstacles());

        if (ship.CorpusStrength?.HealthLevel.IsDead() == null)
        {
            return new ResultPassingSpace(time, fuel, ship);
        }

        if (ship.ImpulseEngine != null)
        {
            time = Length / (decimal)ship.ImpulseEngine.Speed(Length);
            fuel = ship.ImpulseEngine.FuelConsumption(Length);
        }

        return new ResultPassingSpace(time, fuel, ship);
    }
}