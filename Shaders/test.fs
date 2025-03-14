#version 330 core
uniform vec3 camTransform;
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }
float sdSphere (vec3 p, float s) { return length(p) - s; }
float sdBox (vec3 p, vec3 b) {vec3 q = abs(p) - b;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);}
float sdCone(vec3 p, float r, float h) { vec2 q = vec2(length(p.xz) - r, p.y + 0.5 * h); vec2 e = vec2(-r, h); vec2 d1 = q - e * clamp(dot(q, e) / dot(e, e), 0.0, 1.0); vec2 d2 = vec2(max(q.x, 0.0), -q.y); return sqrt(min(dot(d1, d1), dot(d2, d2))) * sign(max(max(d1.x, d1.y), d2.y)); }
float sdTorus(vec3 p, vec2 t) { vec2 q = vec2(length(p.xz) - t.x, p.y); return length(q) - t.y; }
float sdCylinder( vec3 p, float r, float h ) { vec2 d = abs(vec2(length(p.xz), p.y)) - vec2(r, h); return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));}
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
   vec4 sdf_ = vec4 (0., 0., 0., 0.);
	float d0 = sdBox(p - vec3(0, -2.75, 0), vec3(20, 0.75, 20)); 
	float d1 = sdSphere(p - vec3(0, -0.75, -2), 2);
	float d2 = opSmoothUnion(d0, d1,0.2); 
	float d3 = sdSphere(p - vec3(-0.15, 1.25, -2), 1.5);
	float d4 = opSmoothUnion(d2, d3,0.2); 
	float d5 = sdSphere(p - vec3(-0.3, 3.2, -2), 1);
	float d6 = opSmoothUnion(d4, d5,0.2); 
   sdf = vec4(d6, vec3(0.901961, 0.901961, 0.941176));
	float d7 = sdSphere(p - vec3(-0.15, 1.25, -0.48), 0.08);
   sdf = opUnion(sdf, vec4(d7, vec3(0.0392157, 0.0392157, 0.0392157)));
	float d8 = sdSphere(p - vec3(-0.2, 1.8, -0.6), 0.08);
   sdf = opUnion(sdf, vec4(d8, vec3(0.0392157, 0.0392157, 0.0392157)));
	float d9 = sdSphere(p - vec3(0.1, 3.3, -1.12), 0.12);
   sdf = opUnion(sdf, vec4(d9, vec3(0.0392157, 0.0392157, 0.0392157)));
	float d10 = sdSphere(p - vec3(-0.75, 3.1, -1.15), 0.12);
   sdf = opUnion(sdf, vec4(d10, vec3(0.0392157, 0.0392157, 0.0392157)));
	float d11 = sdCylinder(rotate_z(p - vec3(-0.4, 3.8, -2),-0.261799), 1.25, 0.1); 
   sdf = opUnion(sdf, vec4(d11, vec3(0.0784314, 0.0784314, 0.0784314)));
	float d12 = sdCylinder(rotate_z(p - vec3(-0.56, 4.6, -2),-0.261799), 1, 0.75); 
   sdf = opUnion(sdf, vec4(d12, vec3(0.0784314, 0.0784314, 0.0784314)));
	float d13 = sdCylinder(rotate_x(rotate_y(p - vec3(-1.6, -1.8, 0),0.523599),1.570796), 0.2, 1.75); 
   sdf = opUnion(sdf, vec4(d13, vec3(0.588235, 0.27451, 0.196078)));
	float d14 = sdCylinder(rotate_z(p - vec3(1.4, 2.2, -2),0.872665), 0.18, 1.75); 
	float d15 = sdCylinder(rotate_z(p - vec3(3, 3.3, -2),1.919862), 0.07, 0.2); 
	float d16 = opSmoothUnion(d14, d15,0.1); 
	float d17 = sdCylinder(rotate_z(p - vec3(3, 3.5, -2),1.047198), 0.07, 0.2); 
	float d18 = opSmoothUnion(d16, d17,0.1); 
	float d19 = sdCylinder(rotate_z(p - vec3(2.8, 3.6, -2),0.261799), 0.07, 0.2); 
	float d20 = opSmoothUnion(d18, d19,0.1); 
	float d21 = sdSphere(p - vec3(1.8, 2.7, -2), 0.1);
	float d22 = opSmoothSubtraction(d20, d21,0.3); 
	float d23 = sdSphere(p - vec3(2.5, 3.3, -2), 0.13);
	float d24 = opSmoothSubtraction(d22, d23,0.3); 
   sdf = opUnion(sdf, vec4(d24, vec3(0.588235, 0.27451, 0.196078)));
	float d25 = sdCone(p - vec3(-6, 2, -6), 1, 1.6); 
   sdf_ = vec4(d25, vec3(0.27451, 0.623529, 0.27451));
	float d26 = sdCone(p - vec3(-6, 1, -6), 1.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d26, vec3(0.27451, 0.623529, 0.27451))); 
	float d27 = sdCone(p - vec3(-6, 0.4, -6), 1.4, 2.4); 
	sdf_  = opUnion(sdf_, vec4(d27, vec3(0.27451, 0.623529, 0.27451))); 
	float d28 = sdCylinder(p - vec3(-6, 0, -6), 0.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d28, vec3(0.588235, 0.27451, 0.196078))); 
   sdf = opUnion(sdf, sdf_);
	float d29 = sdCone(p - vec3(-2.5, 2, -6), 1, 1.6); 
   sdf_ = vec4(d29, vec3(0.27451, 0.623529, 0.27451));
	float d30 = sdCone(p - vec3(-2.5, 1, -6), 1.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d30, vec3(0.27451, 0.623529, 0.27451))); 
	float d31 = sdCone(p - vec3(-2.5, 0.4, -6), 1.4, 2.4); 
	sdf_  = opUnion(sdf_, vec4(d31, vec3(0.27451, 0.623529, 0.27451))); 
	float d32 = sdCylinder(p - vec3(-2.5, 0, -6), 0.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d32, vec3(0.588235, 0.27451, 0.196078))); 
   sdf = opUnion(sdf, sdf_);
	float d33 = sdCone(p - vec3(1, 2, -6), 1, 1.6); 
   sdf_ = vec4(d33, vec3(0.27451, 0.623529, 0.27451));
	float d34 = sdCone(p - vec3(1, 1, -6), 1.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d34, vec3(0.27451, 0.623529, 0.27451))); 
	float d35 = sdCone(p - vec3(1, 0.4, -6), 1.4, 2.4); 
	sdf_  = opUnion(sdf_, vec4(d35, vec3(0.27451, 0.623529, 0.27451))); 
	float d36 = sdCylinder(p - vec3(1, 0, -6), 0.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d36, vec3(0.588235, 0.27451, 0.196078))); 
   sdf = opUnion(sdf, sdf_);
	float d37 = sdCone(p - vec3(4.5, 2, -6), 1, 1.6); 
   sdf_ = vec4(d37, vec3(0.27451, 0.623529, 0.27451));
	float d38 = sdCone(p - vec3(4.5, 1, -6), 1.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d38, vec3(0.27451, 0.623529, 0.27451))); 
	float d39 = sdCone(p - vec3(4.5, 0.4, -6), 1.4, 2.4); 
	sdf_  = opUnion(sdf_, vec4(d39, vec3(0.27451, 0.623529, 0.27451))); 
	float d40 = sdCylinder(p - vec3(4.5, 0, -6), 0.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d40, vec3(0.588235, 0.27451, 0.196078))); 
   sdf = opUnion(sdf, sdf_);
	float d41 = sdCone(p - vec3(8, 2, -6), 1, 1.6); 
   sdf_ = vec4(d41, vec3(0.27451, 0.623529, 0.27451));
	float d42 = sdCone(p - vec3(8, 1, -6), 1.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d42, vec3(0.27451, 0.623529, 0.27451))); 
	float d43 = sdCone(p - vec3(8, 0.4, -6), 1.4, 2.4); 
	sdf_  = opUnion(sdf_, vec4(d43, vec3(0.27451, 0.623529, 0.27451))); 
	float d44 = sdCylinder(p - vec3(8, 0, -6), 0.4, 2); 
	sdf_  = opUnion(sdf_, vec4(d44, vec3(0.588235, 0.27451, 0.196078))); 
   sdf = opUnion(sdf, sdf_);
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
   vec3 col = vec3(0.,0.,0.);
   vec4  ray = raymarchV4(ro, rd);
   float t = ray.x;
   vec3 Cd = ray.yzw;
   if (t > 0.0) {
       col = Cd *vec3(0.0027451, 0.00196078, 0.196078);
       vec3 p = ro + rd * t;
       vec3 N = calcNormal(p);
       vec3 L, CL, distL;
       float LdotN, shadL, falloffL;
       col += 0.1 * Cd;
	L = vec3(-0.348155, 0.870388, 0.348155);
	CL = 0.2 * vec3(1, 1, 1);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	L = vec3(-0, 1, 0);
	CL = 0.05 * vec3(0.117647, 0.117647, 1);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(-1, 3.8, -0.3) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 0.85 * vec3(1, 0.588235, 0.117647)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(3, -1, -6) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 1 * vec3(1, 0.352941, 0.0392157)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
   return col;}
   return vec3(0.027451, 0.0196078, 0.0784314);
}
out vec4 FragColor;
in vec2 pos;
void main () {
   vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); 
   vec3 pix = vec3(pXY.x, pXY.y, 12.) + camTransform;
   vec3 ro  = vec3(0.,0., 15. ) + camTransform;
   vec3 rd  = normalize(pix - ro);
   vec3 col = render(ro, rd);
  FragColor = vec4(col, 1.0f);
}
