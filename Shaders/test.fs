#version 330 core
uniform vec3 camTransform;
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }
float sdSphere (vec3 p, float s) { return length(p) - s; }
float sdBox (vec3 p, vec3 b) {vec3 q = abs(p) - b;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);}
float sdCone(vec3 p, float r, float h) { vec2 q = vec2(length(p.xz) - r, p.y + 0.5 * h); vec2 e = vec2(-r, h); vec2 d1 = q - e * clamp(dot(q, e) / dot(e, e), 0.0, 1.0); vec2 d2 = vec2(max(q.x, 0.0), -q.y); return sqrt(min(dot(d1, d1), dot(d2, d2))) * sign(max(max(d1.x, d1.y), d2.y)); }
float sdTorus(vec3 p, vec2 t) { vec2 q = vec2(length(p.xz) - t.x, p.y); return length(q) - t.y; }
float sdCylinder( vec3 p, float h, float r ) { vec2 d = abs(vec2(length(p.xz), p.y)) - vec2(r, h); return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));}
float opSmoothUnion( float d1, float d2, float k ) { float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0); return mix(d2, d1, h) - k * h * (1.0 - h); }
float opSubtraction( float d1, float d2 ) { return max(d1,-d2); }
float opSmoothSubtraction( float d1, float d2, float k ) { float h = clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0); return mix(d1, -d2, h) + k * h * (1.0 - h); }
float opIntersection( float d1, float d2 ) { return max(d1, d2); }
float opSmoothIntersection( float d1, float d2, float k ) { float h = clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0); return mix(d2, d1, h) + k * h * (1.0 - h); }
vec3 rotate_x(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +1.0, +.0, +.0, +.0, +ca, -sa, +.0, +sa, +ca); }
vec3 rotate_y(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +ca, +.0, -sa, +.0, +1.0, +.0, +sa, +.0, +ca); }
vec3 rotate_z(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +ca, -sa, +.0, +sa, +ca, 0., +.0, +.0, 1.); }
vec4 mapV4(in vec3 p) {
   vec4 sdf = vec4 (0., 0., 0., 0.);
	float d0 = sdSphere(p - vec3(0, 0, -1), 0.2);
	float d1 = sdBox(p - vec3(0.15, 0, -1), vec3(0.08, 0.1, 0.2)); 
	float d2 = opSubtraction(d0, d1);
   sdf = vec4(d2, vec3(1, 0, 0));
	float d3 = sdSphere(p - vec3(0.4, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d3, vec3(1, 0, 0)));
	float d4 = sdSphere(p - vec3(-0.5, 0, -1), 0.1);
   sdf = opUnion(sdf, vec4(d4, vec3(0, 1, 0)));
	float d5 = sdCone(p - vec3(-0.5, 0.5, -1), 0.2, 0.6); 
   sdf = opUnion(sdf, vec4(d5, vec3(0, 1, 0)));
	float d6 = sdBox(rotate_y(p - vec3(-1, -0.25, -2),0.785398), vec3(0.3, 0.2, 0.5)); 
   sdf = opUnion(sdf, vec4(d6, vec3(1, 1, 0)));
	float d7 = sdSphere(p - vec3(-0.5, 0.25, -1), 0.1);
   sdf = opUnion(sdf, vec4(d7, vec3(0, 0, 1)));
	float d8 = sdSphere(p - vec3(-0, -0.4, -0.25), 0.3);
   sdf = opUnion(sdf, vec4(d8, vec3(0, 0, 1)));
	float d9 = sdBox(rotate_z(p - vec3(0.4, 0.5, -1.5),0.785398), vec3(0.2, 0.2, 0.2)); 
	float d10 = sdSphere(p - vec3(0.5, 0.2, -1.5), 0.3);
	float d11 = opSmoothUnion(d9, d10,0.1); 
	float d12 = sdSphere(p - vec3(0.8, 0.3, -1.5), 0.1);
	float d13 = opSmoothUnion(d11, d12,0.1); 
	float d14 = sdSphere(p - vec3(0.3, 0.8, -1.5), 0.3);
	float d15 = opSmoothUnion(d13, d14,0.1); 
	float d16 = sdBox(p - vec3(0.4, 0.5, -1.5), vec3(0.1, 0.1, 2)); 
	float d17 = sdBox(rotate_z(p - vec3(0.4, 0.5, -1.5),0.523599), vec3(0.1, 0.1, 2)); 
	float d18 = opSmoothUnion(d16, d17,0.1); 
	float d19 = opSmoothSubtraction(d15, d18,0.1); 
	float d20 = sdBox(rotate_z(p - vec3(0.3, 0.8, -1.5),0.523599), vec3(0.2, 0.2, 0.5)); 
	float d21 = opSmoothSubtraction(d19, d20,0.1); 
   sdf = opUnion(sdf, vec4(d21, vec3(0, 1, 1)));
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
            if (h < 0.0005)
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
       vec3 L, CL, distL;
       float LdotN, shadL, falloffL;
       col += 0.2 * Cd;
	L = vec3(-0, 1, 0);
	CL = 1 * vec3(1, 1, 1);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(-0.5, -1, -1) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 1 * vec3(1, 1, 0)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(1.5, -1, -1) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 1 * vec3(1, 0, 1)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
   }
   return col;
}
out vec4 FragColor;
in vec2 pos;
void main () {
   vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); 
   vec3 pix = vec3(pXY.x, pXY.y, 2.) + camTransform;
   vec3 ro  = vec3(0.,0., 8. ) + camTransform;
   vec3 rd  = normalize(pix - ro);
   vec3 col = render(ro, rd);
  FragColor = vec4(col, 1.0f);
}
