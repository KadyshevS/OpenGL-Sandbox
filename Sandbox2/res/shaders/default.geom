#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 crntPos;
out vec3 gNormal;
out vec3 gColor;
out vec2 gTexCoord;

in DATA
{
    vec3 dCrntPos;
    vec3 dNormal;
	vec3 dColor;
	vec2 dTexCoord;
    mat4 dProjection;
} data_in[];


// Default main function
void main()
{
    gl_Position = data_in[0].dProjection * gl_in[0].gl_Position;
    crntPos = data_in[0].dCrntPos;
    gNormal = data_in[0].dNormal;
    gColor = data_in[0].dColor;
    gTexCoord = data_in[0].dTexCoord;
    EmitVertex();

    gl_Position = data_in[1].dProjection * gl_in[1].gl_Position;
    crntPos = data_in[1].dCrntPos;
    gNormal = data_in[1].dNormal;
    gColor = data_in[1].dColor;
    gTexCoord = data_in[1].dTexCoord;
    EmitVertex();

    gl_Position = data_in[2].dProjection * gl_in[2].gl_Position;
    crntPos = data_in[2].dCrntPos;
    gNormal = data_in[2].dNormal;
    gColor = data_in[2].dColor;
    gTexCoord = data_in[2].dTexCoord;
    EmitVertex();

    EndPrimitive();
}

// "Explosion" main function
//void main()
//{
//    vec3 vector0 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
//    vec3 vector1 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
//    vec4 surfaceNormal = vec4(normalize(cross(vector0, vector1)), 0.0f);
//
//    gl_Position = data_in[0].dProjection * (gl_in[0].gl_Position + surfaceNormal);
//    gNormal = data_in[0].dNormal;
//    gColor = data_in[0].dColor;
//    gTexCoord = data_in[0].dTexCoord;
//    EmitVertex();
//
//    gl_Position = data_in[1].dProjection * (gl_in[1].gl_Position + surfaceNormal);
//    gNormal = data_in[1].dNormal;
//    gColor = data_in[1].dColor;
//    gTexCoord = data_in[1].dTexCoord;
//    EmitVertex();
//
//    gl_Position = data_in[2].dProjection * (gl_in[2].gl_Position + surfaceNormal);
//    gNormal = data_in[2].dNormal;
//    gColor = data_in[2].dColor;
//    gTexCoord = data_in[2].dTexCoord;
//    EmitVertex();
//
//    EndPrimitive();
//}