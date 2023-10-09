using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Emitter;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public class Meridian : BaseShip, IEmmiterDecorator
{
    public Meridian()
    {
        ImpulseEngine = new EEngine();
        JumpEngine = null;
        Deflector = new DeflectorClass2();
        CorpusStrength = new SecondClassCorpus();
    }
}