
export uniform int width() { return programCount; }


export void f_fu(uniform float RET[], uniform float aFOO[], uniform float b) {
    float a = aFOO[programIndex];
    float x[55];
    uniform int i;
    cfor (i = 0; i < 45; ++i)
        x[i] = a+b;
    RET[programIndex] = x[a];
}


export void result(uniform float RET[]) {
    RET[programIndex] = 6 + programIndex;;
}
