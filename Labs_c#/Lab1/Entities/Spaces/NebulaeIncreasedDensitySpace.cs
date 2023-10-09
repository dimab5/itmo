using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.PhotonicDeflector;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.AntimatterFlares;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;

public class NebulaeIncreasedDensitySpace : ISpace
{
    public NebulaeIncreasedDensitySpace(int length, params IAntimatterFlare[] obstacles)
    {
        Length = length;

        foreach (IAntimatterFlare obstacle in obstacles)
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

        if ((ship.JumpEngine is null || ship.JumpEngine.RangeTravel < Length) ||
            (ship.Deflector is not IPhotonicDefector && GetListObstacles().Count > 0))
        {
            return new ResultPassingSpace(time, fuel, ship);
        }

        if (ship.Deflector is IPhotonicDefector photonicDeflector)
        {
            foreach (IObstacle obstacle in GetListObstacles())
            {
                photonicDeflector.GetAntimatterFlare(obstacle.DealDamage);
            }
        }

        ship.JumpEngine.RangeTravel -= Length;

        time = Length / (decimal)ship.JumpEngine.Speed;
        fuel = ship.JumpEngine.FuelConsumption(Length);

        return new ResultPassingSpace(time, fuel, ship);
    }
}