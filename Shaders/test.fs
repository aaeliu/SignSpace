#version 330 core
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }
float sdSphere (vec3 p, float s) { return length(p) - s; }
vec4 mapV4(in vec3 p) {
   vec4 sdf = vec4 (0., 0., 0., 0.);
	float d0 = sdSphere(p + vec3(0, 0, 1), 1.5);
   sdf = vec4(d0, vec3(1.0, 0.0, 0.0));
	float d1 = sdSphere(p + vec3(0.5, 0, 1), 1.5);
   sdf = opUnion(sdf, vec4(d1, vec3 (1.0, 0.0, 0.0 )));
	 return sdf;
}
float map(in vec3 p) { return mapV4(p).x; }
vec4 raymarch(in vec3 ro, in vec3 rd) {
	float t = 0.0;
	for (int i = 0; i < 500; i++) {
	vec3  rt = ro + rd*t;
	vec4 f = mapV4(rt);
            	float d = f.x;
            	if (d < 0.001) {
            	f.x = t;
            		    return f;
            	}
            	else {
            		   t += 0.9*d;
            	}
            	if (t > 100.) {
            		f.x = -1;
            		return f;
            	}
 }
}
out vec4 FragColor;
in vec2 pos;
void main () {
  FragColor = vec4(pos, 0.3f, 1.0f);
}
