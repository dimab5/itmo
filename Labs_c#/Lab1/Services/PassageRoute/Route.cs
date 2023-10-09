using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;

public class Route : IRoute
{
    public Route(IShip inputShip, params ISpace[] spaces)
    {
        Ship = inputShip;

        foreach (ISpace space in spaces)
        {
            RouteSpaces.Add(space);
        }
    }

    public IShip Ship { get; }

    private List<ISpace> RouteSpaces { get; set; } = new List<ISpace>();

    public IResultPassingSpace PassingRoute()
    {
        decimal time = 0;
        int fuel = 0;

        foreach (ISpace space in RouteSpaces)
        {
            var spacePassage = new SpaceFlight(Ship, space);
            IResultPassingSpace tempResult = spacePassage.PassingSpace();

            if (tempResult.Time == 0 && tempResult.Fuel == 0)
            {
                return new ResultPassingSpace(tempResult.Time, tempResult.Fuel, tempResult.Ship);
            }

            time += tempResult.Time;
            fuel += tempResult.Fuel;
        }

        return new ResultPassingSpace(time, fuel, Ship);
    }
}