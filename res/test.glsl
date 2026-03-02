#shader vert
#version 330 core

layout(location = 0) in vec2 i_position;

void main()
{
    gl_Position = vec4(i_position, 0, 1);
}

#shader frag
#version 330 core

layout(location = 0) out vec4 o_color;

void main()
{
    o_color = vec4(1, 0, 0, 1);
}
