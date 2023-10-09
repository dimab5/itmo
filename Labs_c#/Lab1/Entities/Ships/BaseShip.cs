using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public abstract class BaseShip : IShip
{
    protected BaseShip()
    {
        ImpulseEngine = default;
        JumpEngine = default;
        Deflector = default;
        CorpusStrength = default;
    }

    public IImpulseEngine? ImpulseEngine { get; protected set; }
    public IJumpEngine? JumpEngine { get; protected set; }
    public IClassDeflector? Deflector { get; set; }
    public ICorpusStrength? CorpusStrength { get; protected set; }

    public void GetDamage(IReadOnlyList<IObstacle> obstacles)
    {
        foreach (IObstacle obstacle in obstacles)
        {
            if (Deflector?.HealthLevel.IsDead() is false)
            {
                Deflector.GetDamage(obstacle.DealDamage);
            }
            else if (CorpusStrength != null && !CorpusStrength.HealthLevel.IsDead())
            {
                CorpusStrength.GetDamage(obstacle.DealDamage);
            }
        }
    }
}