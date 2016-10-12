
varying vec3 pm;  // position in model space

void main()
{
    pm.x = clamp(gl_Vertex.x, 0., 1.);
    pm.y = clamp(gl_Vertex.y, 0., 1.);
    pm.z = clamp(gl_Vertex.z, 0., 1.);

    gl_Position = ftransform();
}
