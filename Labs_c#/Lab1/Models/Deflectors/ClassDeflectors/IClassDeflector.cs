using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;

public interface IClassDeflector
{
    IHealth HealthLevel { get; }
    void GetDamage(int damage);
}