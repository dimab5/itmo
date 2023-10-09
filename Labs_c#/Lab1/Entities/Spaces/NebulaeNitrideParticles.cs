using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Emitter;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.CosmoWhales;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;

public class NebulaeNitrideParticles : ISpace
{
    public NebulaeNitrideParticles(int length, params CosmoWhale[] obstacles)
    {
        Length = length;

        foreach (CosmoWhale obstacle in obstacles)
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

        if (ship.ImpulseEngine is not EEngine)
        {
            return new ResultPassingSpace(time, fuel, ship);
        }

        ship.GetDamage(GetListObstacles());

        if (ship.CorpusStrength != null && ship.CorpusStrength.HealthLevel.IsDead() && ship is not IEmmiterDecorator)
        {
            return new ResultPassingSpace(time, fuel, ship);
        }

        time = Length / (decimal)ship.ImpulseEngine.Speed(Length);
        fuel = ship.ImpulseEngine.FuelConsumption(Length);

        return new ResultPassingSpace(time, fuel, ship);
    }
}