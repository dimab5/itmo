using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;

public class DeflectorClass3 : IClassDeflector
{
    private const int DeflectorClass3Health = 1600;
    private const double DeflectorClass3Rate = 1;

    public DeflectorClass3()
    {
        HealthLevel = new Health(DeflectorClass3Health);
    }

    public IHealth HealthLevel { get; private set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * DeflectorClass3Rate);
        HealthLevel = new Health(tempHealth);
    }
}