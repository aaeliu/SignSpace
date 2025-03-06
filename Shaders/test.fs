#version 330 core
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }
float sdSphere (vec3 p, float s) { return length(p) - s; }
vec4 mapV4(in vec3 p) {
   vec4 sdf = vec4 (0., 0., 0., 0.);
	float d0 = sdSphere(p - vec3(0, 0, -1), 0.2);
   sdf = vec4(d0, vec3(1, 0, 0));
	float d1 = sdSphere(p - vec3(0.4, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d1, vec3(1, 0, 0)));
	float d2 = sdSphere(p - vec3(-0.5, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d2, vec3(0, 1, 0)));
	float d3 = sdSphere(p - vec3(-0.5, 0.25, -1), 0.1);
   sdf = opUnion(sdf, vec4(d3, vec3(0, 0, 1)));
	 return sdf;
}
float map(in vec3 p) { return mapV4(p).x; }
vec4 raymarchV4(in vec3 ro, in vec3 rd) {
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
float raymarch(in vec3 ro, in vec3 rd)  { return raymarchV4(ro, rd).x; }
vec3 render(in vec3 ro, in vec3 rd)  {
   vec3 col = vec3(0.0784314, 0.0784314, 0.0784314);
   vec4  ray = raymarchV4(ro, rd);
   float t = ray.x;
   vec3 Cd = ray.yzw;
   if (t > 0.0) {
       col = Cd;
   }
   return col;
}
out vec4 FragColor;
in vec2 pos;
void main () {
   vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); 
   vec3 pix = vec3(pXY,    1.);
   vec3 ro  = vec3(0,0., 6. );
   vec3 rd  = normalize(pix - ro);
   vec3 col = render(ro, rd);
  FragColor = vec4(col, 1.0f);
}
