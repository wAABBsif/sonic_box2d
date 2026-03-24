#shader vert
#version 330 core

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texture_coords;
layout(location = 2) in float in_depth;
layout(location = 3) in int in_texture_index;

out vec2 frag_texture_coords;
flat out int frag_texture_index;

uniform sampler2D textures[16];

sampler2D get_tex(int idx)
{
    //this is really stupid
    switch (int(idx))
    {
        case 0:
            return textures[0];
        case 1:
            return textures[1];
        case 2:
            return textures[2];
        case 3:
            return textures[3];
        case 4:
            return textures[4];
        case 5:
            return textures[5];
        case 6:
            return textures[6];
        case 7:
            return textures[7];
        case 8:
            return textures[8];
        case 9:
            return textures[9];
        case 10:
            return textures[10];
        case 11:
            return textures[11];
        case 12:
            return textures[12];
        case 13:
            return textures[13];
        case 14:
            return textures[14];
        case 15:
            return textures[15];
    }

    return textures[0];
}

void main()
{
    gl_Position = vec4(in_position, in_depth, 1);
    frag_texture_coords = in_texture_coords;
    frag_texture_index = in_texture_index;

    frag_texture_coords /= textureSize(get_tex(frag_texture_index), 0);
}

#shader frag
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 frag_texture_coords;
flat in int frag_texture_index;

uniform sampler2D textures[16];

sampler2D get_tex(int idx)
{
    //this is really stupid
    switch (int(idx))
    {
        case 0:
            return textures[0];
        case 1:
            return textures[1];
        case 2:
            return textures[2];
        case 3:
            return textures[3];
        case 4:
            return textures[4];
        case 5:
            return textures[5];
        case 6:
            return textures[6];
        case 7:
            return textures[7];
        case 8:
            return textures[8];
        case 9:
            return textures[9];
        case 10:
            return textures[10];
        case 11:
            return textures[11];
        case 12:
            return textures[12];
        case 13:
            return textures[13];
        case 14:
            return textures[14];
        case 15:
            return textures[15];
    }

    return textures[0];
}

void main()
{
    out_color = texture(textures[frag_texture_index], frag_texture_coords);
}
