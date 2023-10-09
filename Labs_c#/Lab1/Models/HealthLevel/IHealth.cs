namespace Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

public interface IHealth
{
    int HealthValue { get; }
    bool IsDead();
}