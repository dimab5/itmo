using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public class Vaclas : BaseShip
{
    public Vaclas()
    {
        ImpulseEngine = new EEngine();
        JumpEngine = new GammaEngine();
        Deflector = new DeflectorClass1();
        CorpusStrength = new SecondClassCorpus();
    }
}