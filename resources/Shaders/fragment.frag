#version 430 core


in vec2 tex_coord;  
in vec3 norm;
in vec4 vert_position;
in vec3 vsColour;


uniform sampler2D sampler;
uniform vec3 light_color = vec3(0.8, 0.8, 0.5);
uniform vec3 light_position;
uniform float specularity = 1; 

uniform vec3 testCol = {1.0, 0.0, 0.0};

uniform mat4 view=mat4(1);
uniform mat4 model=mat4(1);

#define EPSILON 0.0000000000000001

out vec4 outColor;

vec3 PointLight(
        in vec3 position,       // Lights' worldspace position
        in vec3 intensities,    // RGB
        in float constant,      // Falloff
        in float linear,        // Falloff
        in float quadratic){    // Falloff
        
        // Ambience.            Allows us to see past the diffused light.
        float ambient_strength = 0.1;
        vec3 ambient = ambient_strength * intensities;

        // Diffussion           Decides intensity of scattered light.
        vec3 N = normalize(norm);
        vec3 light_dir = normalize(position - vec3(model * vert_position));
        float diffusion = max(0.5, dot(N, light_dir));
        vec3 diffuse = diffusion * intensities;

        // Specularity          Adds a strong lightspot in middle of light.
        vec3 view_dir = normalize(vec3(inverse(view) * vec4(0,0,0,1) - model * vert_position));
        vec3 reflect_dir = reflect(-light_dir, N);
        float spec_power = pow(max(0.0, dot(view_dir, reflect_dir)), 32);
        vec3 specular = specularity * spec_power * intensities;

        // Attenuation          Intensity reduction when traveling through space.
        float distance = length(position - vec3(model * vert_position));
        float attenuation = 12 / (constant + linear * distance + quadratic * distance * distance + EPSILON);
        
        return (ambient + diffuse + specular) * attenuation;
        }



void main() {
    vec4 tex = texture(sampler, tex_coord);
    vec3 light;

    light = PointLight(light_position, light_color, 0.5, 0.25, 0.125);

    outColor = vec4(testCol, 1.f) * vec4(tex.rgb * light, tex.a);

}





