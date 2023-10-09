namespace Itmo.ObjectOrientedProgramming.Lab1.Services.PassageRoute;

public abstract record PossibleResults
{
    private PossibleResults()
    {
    }

    public sealed record Success(decimal Time, int Fuel) : PossibleResults;

    public sealed record Fail() : PossibleResults;
}