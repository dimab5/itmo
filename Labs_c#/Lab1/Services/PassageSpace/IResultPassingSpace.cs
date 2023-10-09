using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

public interface IResultPassingSpace
{
    public decimal Time { get; }
    public int Fuel { get; }
    public IShip Ship { get; }
}