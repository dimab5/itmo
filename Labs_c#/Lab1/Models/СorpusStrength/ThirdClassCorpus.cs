using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

public class ThirdClassCorpus : ICorpusStrength
{
    private const int CorpusStrength3Health = 750;
    private const double CorpusClass3Rate = 1;

    public ThirdClassCorpus()
    {
        HealthLevel = new Health(CorpusStrength3Health);
    }

    public IHealth HealthLevel { get; set; }

    public void GetDamage(int damage)
    {
        int tempHealth = HealthLevel.HealthValue - (int)(damage * CorpusClass3Rate);
        HealthLevel = new Health(tempHealth);
    }
}