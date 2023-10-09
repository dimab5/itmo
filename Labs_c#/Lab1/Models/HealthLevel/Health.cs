namespace Itmo.ObjectOrientedProgramming.Lab1.Models.HealthLevel;

public class Health : IHealth
{
    public Health(int health)
    {
        if (health < 0)
        {
            health = 0;
        }

        HealthValue = health;
    }

    public int HealthValue { get; }

    public bool IsDead()
    {
        return HealthValue == 0;
    }
}