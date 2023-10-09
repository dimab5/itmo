using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

public class SecondClassCorpus : ICorpusStrength
{
    private const int CorpusStrength2Health = 202;
    private const double CorpusClass2Rate = 0.9;

    public SecondClassCorpus()
    {
        HealthLevel = new Health(CorpusStrength2Health);
    }

    public IHealth HealthLevel { get; set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * CorpusClass2Rate);
        HealthLevel = new Health(tempHealth);
    }
}