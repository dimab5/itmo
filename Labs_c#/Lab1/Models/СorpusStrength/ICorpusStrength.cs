using Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

namespace Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

public interface ICorpusStrength
{
    IHealth HealthLevel { get; set; }
    void GetDamage(int damage);
}