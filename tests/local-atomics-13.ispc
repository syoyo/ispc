
export uniform int width() { return programCount; }

uniform unsigned int32 s = 0;

export void f_f(uniform float RET[], uniform float aFOO[]) {
    float a = aFOO[programIndex]; 
    int32 b = 0;
    if (programIndex < 28 && (programIndex & 1))
        b = atomic_or_local(&s, (1 << programIndex));
    RET[programIndex] = popcnt(reduce_max(b));
}

export void result(uniform float RET[]) {
    RET[programIndex] = (programCount == 1) ? 0 : ((min(28, programCount)/2) - 1);
}
