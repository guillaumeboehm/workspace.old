
varying vec3 pm;  // position in model space

void main()
{
    gl_FragColor = vec4(pm.x, pm.y, pm.z, 1.0);
}
