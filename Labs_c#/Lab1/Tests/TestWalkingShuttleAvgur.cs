using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.AntimatterFlares;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests.Tests;

public class TestWalkingShuttleAvgur
{
    public static IEnumerable<object[]> Data =>
        new List<object[]>
        {
            new object[]
            {
                new WalkingShuttle(), new Avgur(),
                new NebulaeIncreasedDensitySpace(10000, new AntimatterFlare(1)),
                new PossibleResults.Fail(),
            },
        };

    [Theory]
    [MemberData(nameof(Data))]
    public void Route_WalkingShuttleAvgur_ShouldReturnFailInNebulaeIncreasedDensitySpace(
        IShip firstShip, IShip secondShip, ISpace space, PossibleResults firstExpectedValue)
    {
        var firstShipTest = new ResultWriter(firstShip, space);
        var secondShipTest = new ResultWriter(secondShip, space);

        PossibleResults firstResult = firstShipTest.WriteResult();
        PossibleResults secondResult = secondShipTest.WriteResult();

        Assert.Equal(firstResult, firstExpectedValue);
        Assert.Equal(secondResult, firstExpectedValue);
    }
}