
export uniform int width() { return programCount; }

uniform unsigned int32 s = 0;

export void f_f(uniform float RET[], uniform float aFOO[]) {
    float a = aFOO[programIndex]; 
    float b = 0;
    if (programIndex < 29 && (programIndex & 1))
        b = atomic_or_local(&s, (1 << programIndex));
    RET[programIndex] = s;
}

export void result(uniform float RET[]) {
    uniform int sum = 0;
    for (uniform int i = 0; i < min(programCount, 29); ++i)
        if (i & 1)
            sum += (1 << i);
    RET[programIndex] = sum;
}
