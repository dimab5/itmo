using System.Collections.Generic;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Obstacles.Obstacle;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public interface IShip
{
    IImpulseEngine? ImpulseEngine { get; }
    IJumpEngine? JumpEngine { get; }
    IClassDeflector? Deflector { get; set; }
    ICorpusStrength? CorpusStrength { get; }
    public void GetDamage(IReadOnlyList<IObstacle> obstacles);
}