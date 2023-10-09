using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.CosmoWhales;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests.Tests;

public class TestAllShips
{
    public static IEnumerable<object[]> Data =>
        new List<object[]>
        {
            new object[]
            {
                new WalkingShuttle(), new Vaclas(), new Meridian(), new Avgur(), new Stella(),
                new NebulaeNitrideParticles(50000, new CosmoWhale(1)),
                new OrdinarySpace(50000), new NebulaeIncreasedDensitySpace(1000),
                new PossibleResults.Fail(),
            },
        };

    [Theory]
    [MemberData(nameof(Data))]
    public void Route_All_Ships(
        IShip ship1, IShip ship2, IShip ship3, IShip ship4, IShip ship5, ISpace space1, ISpace space2, ISpace space3, PossibleResults firstExpected)
    {
        var ship1Test = new ResultWriter(ship1, space1, space2, space3);
        var ship2Test = new ResultWriter(ship2, space1, space2, space3);
        var ship3Test = new ResultWriter(ship3, space1, space2, space3);
        var ship4Test = new ResultWriter(ship4, space1, space2, space3);
        var ship5Test = new ResultWriter(ship5, space1, space2, space3);

        PossibleResults result1 = ship1Test.WriteResult();
        PossibleResults result2 = ship2Test.WriteResult();
        PossibleResults result3 = ship3Test.WriteResult();
        PossibleResults result4 = ship4Test.WriteResult();
        PossibleResults result5 = ship5Test.WriteResult();

        Assert.Equal(result1, firstExpected);
        Assert.NotEqual(result2, firstExpected);
        Assert.Equal(result3, firstExpected);
        Assert.Equal(result4, firstExpected);
        Assert.Equal(result5, firstExpected);
    }
}