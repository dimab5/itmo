using Itmo.ObjectOrientedProgramming.Lab1.Models.Deflectors.ClassDeflectors;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.ImpulseEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.Engines.JumpEngines;
using Itmo.ObjectOrientedProgramming.Lab1.Models.СorpusStrength;

namespace Itmo.ObjectOrientedProgramming.Lab1.Entities.Ships;

public class Avgur : BaseShip
{
    public Avgur()
        : base()
    {
        ImpulseEngine = new EEngine();
        JumpEngine = new AlphaEngine();
        Deflector = new DeflectorClass3();
        CorpusStrength = new ThirdClassCorpus();
    }
}