using System.Collections.Generic;
using System.Diagnostics;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Spaces;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.PhotonicDeflector;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.AntimatterFlares;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;
using Xunit;

namespace Itmo.ObjectOrientedProgramming.Lab1.Tests.Tests;

public class TestVaclas
{
    public static IEnumerable<object[]> Data =>
        new List<object[]>
        {
            new object[]
            {
                new Vaclas(), SetPhotonicdeflector(new Vaclas()),
                new NebulaeIncreasedDensitySpace(1000, new AntimatterFlare(1)),
                new PossibleResults.Fail(), new PossibleResults.Success(10, 1000000),
            },
        };

    [Theory]
    [MemberData(nameof(Data))]
    public void Route_Vaclas_ShouldReturnFailSuccessInNebulaeIncreasedDensitySpace(
        IShip firstShip, IShip secondShip, ISpace space, PossibleResults firstExpectedValue, PossibleResults secondExpectedValue)
    {
        var firstShipTest = new ResultWriter(firstShip, space);
        var secondShipTest = new ResultWriter(secondShip, space);

        PossibleResults firstResult = firstShipTest.WriteResult();
        PossibleResults secondResult = secondShipTest.WriteResult();

        Assert.Equal(firstResult, firstExpectedValue);
        Assert.Equal(secondResult, secondExpectedValue);
    }

    private static IShip SetPhotonicdeflector(IShip ship)
    {
        Debug.Assert(ship.Deflector != null, "ship.Deflector != null");
        ship.Deflector = new PhotonicDefector(ship.Deflector);
        return ship;
    }
}