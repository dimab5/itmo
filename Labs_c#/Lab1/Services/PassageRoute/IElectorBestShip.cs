using Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;
using Itmo.ObjectOrientedProgramming.Lab1.Services.PassageSpace;

namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;

public interface IElectorBestShip
{
    IShip? ChooseOptimalShip(params IResultPassingSpace[] results);
}