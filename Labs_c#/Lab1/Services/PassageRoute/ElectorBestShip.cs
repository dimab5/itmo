using System.Linq;
using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;

public class ElectorBestShip : IElectorBestShip
{
    public ElectorBestShip()
    {
    }

    public IShip? ChooseOptimalShip(params IResultPassingSpace[] results)
    {
        IShip? bestShip = null;
        int minFuel = 0;
        IResultPassingSpace[] resultsArray = results.ToArray();

        int i = 0;
        for (; i < resultsArray.Length; i++)
        {
            if (resultsArray[i].Fuel > 0 && resultsArray[i].Time > 0)
            {
                minFuel = resultsArray[i].Fuel;
                bestShip = resultsArray[i].Ship;
                break;
            }
        }

        for (; i < resultsArray.Length; i++)
        {
            if (resultsArray[i].Fuel > 0 && resultsArray[i].Time > 0 && minFuel > resultsArray[i].Fuel)
            {
                minFuel = resultsArray[i].Fuel;
                bestShip = resultsArray[i].Ship;
            }
        }

        return bestShip;
    }
}