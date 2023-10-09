using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.PhotonicDeflector;

public class PhotonicDefector : IPhotonicDefector
{
    private const int PhotonicDeflectorHealth = 4;
    private readonly IClassDeflector _deflector;

    public PhotonicDefector(IClassDeflector deflector)
    {
        this._deflector = deflector;
        HealthLevel = new Health(deflector.HealthLevel.HealthValue);
        PhotonicHealthLevel = new Health(PhotonicDeflectorHealth);
    }

    public IHealth HealthLevel { get; private set; }
    public IHealth PhotonicHealthLevel { get; private set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - damage;
        HealthLevel = new Health(tempHealth);
    }

    public void GetAntimatterFlare(int damage)
    {
        int tempHealth = PhotonicHealthLevel.HealthValue - 1;
        PhotonicHealthLevel = new Health(tempHealth);
    }
}