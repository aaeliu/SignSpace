#version 330 core
uniform vec3 camTransform;
uniform float time;
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
   vec4 sdf_1 = vec4 (0., 0., 0., 0.);
   float db;
	float d0 = sdBox(p - vec3(0.000000, -2.750000, -0.000000), vec3(20.000000, 0.750000, 20.000000)); 
   sdf = vec4(d0, vec3(0.901961, 0.901961, 0.941176));
	float d1 = sdSphere(p - vec3(-0.150000, 1.250000, -0.480000), 0.080000);
   sdf = opUnion(sdf, vec4(d1, vec3(0.039216, 0.039216, 0.039216)));
	float d2 = sdSphere(p - vec3(-0.200000, 1.800000, -0.600000), 0.080000);
   sdf = opUnion(sdf, vec4(d2, vec3(0.039216, 0.039216, 0.039216)));
	float d3 = sdSphere(p - vec3(0.100000, 3.300000, -1.120000), 0.120000);
   sdf = opUnion(sdf, vec4(d3, vec3(0.039216, 0.039216, 0.039216)));
	float d4 = sdSphere(p - vec3(-0.750000, 3.100000, -1.150000), 0.120000);
   sdf = opUnion(sdf, vec4(d4, vec3(0.039216, 0.039216, 0.039216)));
	float d5 = sdCylinder(rotate_z(p - vec3(-1.600000, -1.800000, -0.000000),-0.261799), 0.200000, 1.750000); 
   sdf = opUnion(sdf, vec4(d5, vec3(0.588235, 0.274510, 0.196078)));
	float d6 = sdCylinder(rotate_z(p - vec3(1.400000, 2.200000, -2.000000),-0.261799), 0.180000, 1.750000); 
	float d7 = sdCylinder(rotate_z(p - vec3(3.000000, 3.300000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d8 = opSmoothUnion(d6, d7,0.250000); 
	float d9 = sdCylinder(rotate_z(p - vec3(3.000000, 3.500000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d10 = opSmoothUnion(d8, d9,0.250000); 
	float d11 = sdCylinder(rotate_z(p - vec3(2.800000, 3.600000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d12 = opSmoothUnion(d10, d11,0.250000); 
	float d13 = sdSphere(p - vec3(1.800000, 2.700000, -2.000000), 0.100000);
	float d14 = opSmoothSubtraction(d12, d13,0.250000); 
	float d15 = sdSphere(p - vec3(2.500000, 3.300000, -2.000000), 0.130000);
	float d16 = opSmoothSubtraction(d14, d15,0.250000); 
   sdf = opUnion(sdf, vec4(d16, vec3(0.588235, 0.274510, 0.196078)));
vec3 t0 = vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t0, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d17 = sdCone(rotate_x(p - t0, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d18 = sdCone(rotate_x(p - t0, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d19 = opSmoothUnion(d17, d18,0.250000); 
	float d20 = sdCone(rotate_x(p - t0, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d21 = opSmoothUnion(d19, d20,0.250000); 
	sdf  = opUnion(sdf, vec4(d21, vec3(0.274510, 0.623529, 0.274510))); 
	float d22 = sdCylinder(rotate_x(p - t0, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d22, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t1 = vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t1, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d23 = sdCone(rotate_x(p - t1, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d24 = sdCone(rotate_x(p - t1, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d25 = opSmoothUnion(d23, d24,0.250000); 
	float d26 = sdCone(rotate_x(p - t1, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d27 = opSmoothUnion(d25, d26,0.250000); 
	sdf  = opUnion(sdf, vec4(d27, vec3(0.274510, 0.623529, 0.274510))); 
	float d28 = sdCylinder(rotate_x(p - t1, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d28, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t2 = vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t2, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d29 = sdCone(rotate_x(p - t2, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d30 = sdCone(rotate_x(p - t2, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d31 = opSmoothUnion(d29, d30,0.250000); 
	float d32 = sdCone(rotate_x(p - t2, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d33 = opSmoothUnion(d31, d32,0.250000); 
	sdf  = opUnion(sdf, vec4(d33, vec3(0.274510, 0.623529, 0.274510))); 
	float d34 = sdCylinder(rotate_x(p - t2, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d34, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t3 = vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t3, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d35 = sdCone(rotate_x(p - t3, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d36 = sdCone(rotate_x(p - t3, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d37 = opSmoothUnion(d35, d36,0.250000); 
	float d38 = sdCone(rotate_x(p - t3, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d39 = opSmoothUnion(d37, d38,0.250000); 
	sdf  = opUnion(sdf, vec4(d39, vec3(0.274510, 0.623529, 0.274510))); 
	float d40 = sdCylinder(rotate_x(p - t3, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d40, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t4 = vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t4, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d41 = sdCone(rotate_x(p - t4, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d42 = sdCone(rotate_x(p - t4, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d43 = opSmoothUnion(d41, d42,0.250000); 
	float d44 = sdCone(rotate_x(p - t4, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d45 = opSmoothUnion(d43, d44,0.250000); 
	sdf  = opUnion(sdf, vec4(d45, vec3(0.274510, 0.623529, 0.274510))); 
	float d46 = sdCylinder(rotate_x(p - t4, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d46, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t5 = vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t5, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d47 = sdCone(rotate_x(p - t5, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d48 = sdCone(rotate_x(p - t5, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d49 = opSmoothUnion(d47, d48,0.250000); 
	float d50 = sdCone(rotate_x(p - t5, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d51 = opSmoothUnion(d49, d50,0.250000); 
	sdf  = opUnion(sdf, vec4(d51, vec3(0.274510, 0.623529, 0.274510))); 
	float d52 = sdCylinder(rotate_x(p - t5, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d52, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t6 = vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t6, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d53 = sdCone(rotate_x(p - t6, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d54 = sdCone(rotate_x(p - t6, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d55 = opSmoothUnion(d53, d54,0.250000); 
	float d56 = sdCone(rotate_x(p - t6, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d57 = opSmoothUnion(d55, d56,0.250000); 
	sdf  = opUnion(sdf, vec4(d57, vec3(0.274510, 0.623529, 0.274510))); 
	float d58 = sdCylinder(rotate_x(p - t6, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d58, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t7 = vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t7, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d59 = sdCone(rotate_x(p - t7, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d60 = sdCone(rotate_x(p - t7, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d61 = opSmoothUnion(d59, d60,0.250000); 
	float d62 = sdCone(rotate_x(p - t7, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d63 = opSmoothUnion(d61, d62,0.250000); 
	sdf  = opUnion(sdf, vec4(d63, vec3(0.274510, 0.623529, 0.274510))); 
	float d64 = sdCylinder(rotate_x(p - t7, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d64, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t8 = vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t8, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d65 = sdCone(rotate_x(p - t8, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d66 = sdCone(rotate_x(p - t8, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d67 = opSmoothUnion(d65, d66,0.250000); 
	float d68 = sdCone(rotate_x(p - t8, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d69 = opSmoothUnion(d67, d68,0.250000); 
	sdf  = opUnion(sdf, vec4(d69, vec3(0.274510, 0.623529, 0.274510))); 
	float d70 = sdCylinder(rotate_x(p - t8, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d70, vec3(0.588235, 0.274510, 0.196078))); 
}
vec3 t9 = vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - t9, 4.03961);
sdf = opUnion (sdf, vec4(db, 1.0, 0.0, 0.0));if (db < 1.0) {
	float d71 = sdCone(rotate_x(p - t9, sin(time))- vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d72 = sdCone(rotate_x(p - t9, sin(time))- vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d73 = opSmoothUnion(d71, d72,0.250000); 
	float d74 = sdCone(rotate_x(p - t9, sin(time))- vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d75 = opSmoothUnion(d73, d74,0.250000); 
	sdf  = opUnion(sdf, vec4(d75, vec3(0.274510, 0.623529, 0.274510))); 
	float d76 = sdCylinder(rotate_x(p - t9, sin(time))- vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d76, vec3(0.588235, 0.274510, 0.196078))); 
}
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
       col = Cd *vec3(((((sin(time)+1.000000)*50.000000)+20.000000)*0.001569), 0.023529, 0.156863);
       vec3 p = ro + rd * t;
       vec3 N = calcNormal(p);
       vec3 L, CL, distL;
       float LdotN, shadL, falloffL;
       col += 0.001569 * Cd;
	L = vec3(-0.348155, 0.870388, 0.348155);
	CL = 0.2 * vec3(1.000000, 1.000000, 1.000000);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	L = vec3(-0, 1, 0);
	CL = 0.05 * vec3(0.117647, 0.117647, 1.000000);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(-1, 3.8, -0.3) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 0.85 * vec3(1.000000, 0.588235, 0.117647)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(3, -1, -6) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 1 * vec3(1.000000, 0.352941, 0.039216)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
   return col;}
   return vec3((sin(time)*0.470588), 0.019608, ((time+3.000000)*0.003922));
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
