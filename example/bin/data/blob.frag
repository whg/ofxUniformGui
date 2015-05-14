#version 120

uniform int nblobs;
uniform sampler2DRect tex;
uniform vec2 mouse;
uniform vec2 texsize;
uniform vec2 windowSize;
uniform float time;

uniform float stickyness = 2.1; // 10.0-0.1
uniform float sizeMultiplier = 0.2;// 0.01 - 0.5
uniform vec2 distEdges = vec2(0.1, 0.9); // 0.0 - 1.0

float dist(vec3 blob, float size, float varianceInverse){
    vec2 p = gl_FragCoord.xy / windowSize;
    float d = distance(p, blob.xy);

    d/=size;
    return exp(-varianceInverse * d*d) * 0.2;
}


void main() {

    float dist = 0.0;
    
    for(int i = 0; i < nblobs ; i++){
        
        vec2 p = vec2(float(i) + 0.5, 0.0);
       
        vec3 texBlob =  texture2DRect(tex, p).xyz;
        float texSize = sizeMultiplier;
        texBlob.y = 1.0 - texBlob.y;
        float d = dist(texBlob, texSize, stickyness);
        
        dist += d;

    }

    float v = smoothstep(distEdges.x, distEdges.y, dist);

    
    gl_FragColor = vec4(vec3(0.0), v);// + specColor;

}
