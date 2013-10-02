typedef float<4> float4;

struct ShadeSample
{
    // output
    float4 Oi;
    float4 Ci;

    // input
    float4 Cs;
    float4 Os;
    float   u;
    float   v;
};

// OK
extern "C" void muda(void* uniform ss, void* uniform a);
// NG
//extern "C" void muda(void* uniform ss, float4& uniform a);
//extern "C" void muda(uniform struct ShadeSample& ss, float4& uniform a);
// extern "C" void muda(void* varying ss, void* uniform a); -> seg fault

// Very simple shader.
export void
shader(uniform struct ShadeSample samples[], uniform int n)
{
    foreach (i = 0 ... n) {
        varying struct ShadeSample ss = samples[i];
        muda(&ss, &ss.Cs); // OK
        // muda(&ss, ss.Cs); // NG
        // muda(&samples[i], samples[i].Cs); // NG

        samples[i].Ci[0] = ss.Ci[0]; // expects 0.5, but get 0.0
        samples[i].Ci[1] = samples[i].u; 
        samples[i].Ci[2] = samples[i].v; 
    }
}
