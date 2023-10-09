using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;

public class ResultWriter : IResultWriter
{
    private readonly IShip _ship;
    private readonly List<ISpace> _spaces;

    public ResultWriter(IShip ship, params ISpace[] spaces)
    {
        _ship = ship;
        _spaces = new List<ISpace>(spaces);
    }

    public PossibleResults WriteResult()
    {
        ISpace[] spaceArray = _spaces.ToArray();
        IRoute route = new Route(_ship, spaceArray);
        IResultPassingSpace result = route.PassingRoute();

        if (result.Time == 0 && result.Fuel == 0)
        {
            return new PossibleResults.Fail();
        }

        return new PossibleResults.Success(result.Time, result.Fuel);
    }
}