using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;

public class DeflectorClass1 : IClassDeflector
{
    private const int DeflectorClass1Health = 50;
    private const double DeflectorClass1Rate = 0.5;

    public DeflectorClass1()
    {
        HealthLevel = new Health(DeflectorClass1Health);
    }

    public IHealth HealthLevel { get; private set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * DeflectorClass1Rate);
        HealthLevel = new Health(tempHealth);
    }
}