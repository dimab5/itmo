using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public class WalkingShuttle : BaseShip
{
    public WalkingShuttle()
    {
        ImpulseEngine = new CEngine();
        JumpEngine = null;
        CorpusStrength = new FirstClassCorpus();
        Deflector = null;
    }
}