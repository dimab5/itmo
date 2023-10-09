using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

public class ResultPassingSpace : IResultPassingSpace
{
    public ResultPassingSpace(decimal time, int fuel, IShip ship)
    {
        Time = time;
        Fuel = fuel;
        Ship = ship;
    }

    public decimal Time { get; }
    public int Fuel { get; }
    public IShip Ship { get; }
}