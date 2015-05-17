#version 120
// thanks to W5MED3LE for inspiration with this

uniform vec2 windowSize;
uniform sampler2DRect tex;

uniform float stickyness = 2.1; // 10.0-0.1
uniform float sizeMultiplier = 0.2;// 0.01 - 0.5
uniform vec2 distEdges = vec2(0.1, 0.9); // 0.0 - 1.0
uniform float coeff = 2; // 0.01 - 5
uniform float hole = 2.5; // 0 - 3

float dist(vec3 blob, float size, float varianceInverse){
    vec2 p = gl_FragCoord.xy / windowSize;
    float d = distance(p, blob.xy);

    d/=size;
    return coeff * exp(-varianceInverse * d*d) - exp(-hole * d*d);
}


void main() {

    float dist = 0.0;
    
    for(int i = 0; i < 10 ; i++){
        
        vec2 p = vec2(float(i) + 0.5, 0.0);
       
        vec3 texBlob =  texture2DRect(tex, p).xyz;
        texBlob.y = 1.0 - texBlob.y;
        float d = dist(texBlob, sizeMultiplier, stickyness);
        
        dist += d*d;

    }

    float v = smoothstep(distEdges.x, distEdges.y, dist);

    gl_FragColor = vec4(vec3(0.0), v);
}
