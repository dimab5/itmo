using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests.Tests;

public class TestAvgurStella
{
    public static IEnumerable<object[]> Data =>
        new List<object[]>
        {
            new object[]
            {
                new Avgur(), new Stella(),
                new NebulaeIncreasedDensitySpace(1000),
            },
        };

    [Theory]
    [MemberData(nameof(Data))]
    public void Route_AvgurStella_ShouldReturnStellaInNebulaeIncreasedDensitySpace(
        IShip firstShip, IShip secondShip, ISpace space)
    {
        var testBestShip = new ElectorBestShip();

        IRoute routeWalkingShuttle = new Route(firstShip, space);
        IRoute routeVaclas = new Route(secondShip, space);

        IResultPassingSpace resultWalkingShuttle = routeWalkingShuttle.PassingRoute();
        IResultPassingSpace resultVaclas = routeVaclas.PassingRoute();

        IShip? result = testBestShip.ChooseOptimalShip(resultWalkingShuttle, resultVaclas);

        Assert.True(result is Stella);
    }
}