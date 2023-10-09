using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

public class FirstClassCorpus : ICorpusStrength
{
    private const int CorpusStrength1Health = 20;
    private const double CorpusClass1Rate = 0.8;

    public FirstClassCorpus()
    {
        HealthLevel = new Health(CorpusStrength1Health);
    }

    public IHealth HealthLevel { get; set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * CorpusClass1Rate);
        HealthLevel = new Health(tempHealth);
    }
}