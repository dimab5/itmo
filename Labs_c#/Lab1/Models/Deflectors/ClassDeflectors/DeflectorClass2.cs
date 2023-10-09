using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;

public class DeflectorClass2 : IClassDeflector
{
    private const int DeflectorClass2Health = 300;
    private const double DeflectorClass2Rate = 0.75;

    public DeflectorClass2()
    {
        HealthLevel = new Health(DeflectorClass2Health);
    }

    public IHealth HealthLevel { get; private set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * DeflectorClass2Rate);
        HealthLevel = new Health(tempHealth);
    }
}