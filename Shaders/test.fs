#version 330 core
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }
float sdSphere (vec3 p, float s) { return length(p) - s; }
float sdBox (vec3 p, vec3 b) {vec3 q = abs(p) - b;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);}
float opSmoothUnion( float d1, float d2, float k ) { float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0); return mix(d2, d1, h) - k * h * (1.0 - h); }
vec4 mapV4(in vec3 p) {
   vec4 sdf = vec4 (0., 0., 0., 0.);
	float d0 = sdSphere(p - vec3(0, 0, -1), 0.2);
   sdf = vec4(d0, vec3(1, 0, 0));
	float d1 = sdSphere(p - vec3(0.4, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d1, vec3(1, 0, 0)));
	float d2 = sdSphere(p - vec3(-0.5, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d2, vec3(0, 1, 0)));
	float d3 = sdBox(p - vec3(-1, -0.25, -2), vec3(0.3, 0.2, 0.1));
   sdf = opUnion(sdf, vec4(d3, vec3(1, 1, 0)));
	float d4 = sdSphere(p - vec3(-0.5, 0.25, -1), 0.1);
   sdf = opUnion(sdf, vec4(d4, vec3(0, 0, 1)));
	float d5 = sdSphere(p - vec3(-0, -0.4, -0.25), 0.3);
   sdf = opUnion(sdf, vec4(d5, vec3(0, 0, 1)));
	float d6 = sdBox(p - vec3(0.4, 0.5, -1.5), vec3(0.2, 0.2, 0.2));
	float d7 = sdSphere(p - vec3(0.5, 0.2, -1.5), 0.3);
	float d8 = sdSphere(p - vec3(0.8, 0.3, -1.5), 0.1);
	float d9 = opSmoothUnion(d7, d8, 0.1);
	float d10 = opSmoothUnion(d6, d9, 0.1);
   sdf = opUnion(sdf, vec4(d10, vec3(0, 1, 1)));
	 return sdf;
}
float map(in vec3 p) { return mapV4(p).x; }
vec3 calcNormal( in vec3 pos ){
        vec2 e = vec2(1.0, -1.0) * 0.5773 * 0.001;
        return normalize(e.xyy * map(pos + e.xyy) +
        e.yyx * map(pos + e.yyx) +
        e.yxy * map(pos + e.yxy) +
        e.xxx * map(pos + e.xxx)); 
}
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
float shadow(in vec3 ro, in vec3 rd, float mint, float maxt) {
        float t = mint;
        for (int i = 0; i < 256 && t < maxt; i++)
        {
            float h = map(ro + rd * t);
            if (h < 0.001)
                return 0.0;
            t += h;
        }
        return 1.0;
    }
vec3 render(in vec3 ro, in vec3 rd)  {
   vec3 col = vec3(0.0784314, 0.0196078, 0.0784314);
   vec4  ray = raymarchV4(ro, rd);
   float t = ray.x;
   vec3 Cd = ray.yzw;
   if (t > 0.0) {
       vec3 p = ro + rd * t;
       vec3 N = calcNormal(p);
       vec3 L, CL;
       float LdotN, shadL;
       col += 0.1 * Cd;
	L = vec3(-0, 1, 1.4);
	CL = 0.3 * vec3(1, 1, 1);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	L = vec3(-0.3, 1, 0);
	CL = 0.3 * vec3(1, 1, 1);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
   }
   return col;
}
out vec4 FragColor;
in vec2 pos;
void main () {
   vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); 
   vec3 pix = vec3(pXY, 0.);
   vec3 ro  = vec3(0,0., 6. );
   vec3 rd  = normalize(pix - ro);
   vec3 col = render(ro, rd);
  FragColor = vec4(col, 1.0f);
}
