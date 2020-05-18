#version 430 core

in vec3 position;     
in vec2 uv_coord;
in vec3 normal;   
in vec3 aColour;

uniform mat4 projection = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 model = mat4(1);
uniform mat3 normal_matrix = mat3(1); // This will be used to calculate our normals in eye space
  
out vec2 tex_coord; 
out vec3 norm;
out vec4 vert_position;
out vec3 vsColour;



void main(void)
{
    vsColour = aColour;
    norm = normalize(normal_matrix * normalize(normal));
    tex_coord = uv_coord;
    vert_position = vec4(position, 1.0);
    gl_Position  = projection * view * model *vec4(position,1.0);	

}

  
