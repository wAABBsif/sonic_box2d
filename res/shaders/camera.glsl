#shader vert
#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texture_coords;

out vec2 frag_texture_coords;

uniform sampler2D tex;
uniform mat3 mat;

void main()
{
    gl_Position = vec4((mat * vec3(in_position, 1)).xy, 0, 1);
    frag_texture_coords = in_texture_coords;
}

#shader frag
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 frag_texture_coords;

uniform sampler2D tex;

void main()
{
    out_color = texture(tex, frag_texture_coords);
}
