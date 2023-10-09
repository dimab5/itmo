using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.PhotonicDeflector;

public interface IPhotonicDefector : IClassDeflector
{
    void GetAntimatterFlare(int damage);
}