typedef float<3> vector;

struct ShadeSample
{
    // output
    vector Oi;
    vector Ci;

    // input
    vector Cs;
    vector Os;
    float   u;
    float   v;
};

// Very simple shader.
export void
shader(uniform struct ShadeSample samples[], uniform int n)
{
    foreach (i = 0 ... n) {
        samples[i].Ci = samples[i].Cs * samples[i].Cs;
        samples[i].Oi = samples[i].Os;
    }
}
