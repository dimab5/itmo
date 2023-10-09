using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

public class SpaceFlight : ISpaceFlight
{
    private readonly IShip ship;
    private ISpace space;

    public SpaceFlight(IShip inputShip, ISpace inputSpace)
    {
        ship = inputShip;
        space = inputSpace;
    }

    public IResultPassingSpace PassingSpace()
    {
        return space.ShipResult(ship);
    }
}