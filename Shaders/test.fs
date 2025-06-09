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
   float db;
vec3 t0 = p - vec3(-8.000000, -8.000000, -35.000000);
db = 0;if (db < 1.0) {
	float d0 = sdSphere(t0 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d1 = sdSphere(t0 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d2 = opSmoothUnion(d0, d1,0.450000); 
	float d3 = sdSphere(t0 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d4 = opSmoothUnion(d2, d3,0.450000); 
	float d5 = sdTorus(t0 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d6 = opSmoothUnion(d4, d5,0.450000); 
	float d7 = sdSphere(t0 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d8 = opSmoothSubtraction(d6, d7,0.300000); 
	float d9 = sdSphere(t0 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d10 = opSmoothSubtraction(d8, d9,0.300000); 
   sdf = vec4(d10, vec3(1.000000, 0.780392, 0.960784));
	float d11 = sdCone(rotate_z(t0 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d11, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t1 = rotate_y(rotate_z(p - vec3(-8.000000, -3.000000, -35.000000),0.174533),0.523599);
db = 0;if (db < 1.0) {
	float d12 = sdSphere(t1 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d13 = sdSphere(t1 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d14 = opSmoothUnion(d12, d13,0.450000); 
	float d15 = sdSphere(t1 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d16 = opSmoothUnion(d14, d15,0.450000); 
	float d17 = sdTorus(t1 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d18 = opSmoothUnion(d16, d17,0.450000); 
	float d19 = sdSphere(t1 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d20 = opSmoothSubtraction(d18, d19,0.300000); 
	float d21 = sdSphere(t1 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d22 = opSmoothSubtraction(d20, d21,0.300000); 
	sdf  = opUnion(sdf, vec4(d22, vec3(1.000000, 0.780392, 0.960784))); 
	float d23 = sdCone(rotate_z(t1 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d23, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t2 = rotate_y(rotate_z(p - vec3(-8.000000, 2.000000, -35.000000),0.349066),1.047198);
db = 0;if (db < 1.0) {
	float d24 = sdSphere(t2 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d25 = sdSphere(t2 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d26 = opSmoothUnion(d24, d25,0.450000); 
	float d27 = sdSphere(t2 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d28 = opSmoothUnion(d26, d27,0.450000); 
	float d29 = sdTorus(t2 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d30 = opSmoothUnion(d28, d29,0.450000); 
	float d31 = sdSphere(t2 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d32 = opSmoothSubtraction(d30, d31,0.300000); 
	float d33 = sdSphere(t2 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d34 = opSmoothSubtraction(d32, d33,0.300000); 
	sdf  = opUnion(sdf, vec4(d34, vec3(1.000000, 0.780392, 0.960784))); 
	float d35 = sdCone(rotate_z(t2 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d35, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t3 = rotate_y(rotate_z(p - vec3(-8.000000, 7.000000, -35.000000),0.523599),1.570796);
db = 0;if (db < 1.0) {
	float d36 = sdSphere(t3 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d37 = sdSphere(t3 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d38 = opSmoothUnion(d36, d37,0.450000); 
	float d39 = sdSphere(t3 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d40 = opSmoothUnion(d38, d39,0.450000); 
	float d41 = sdTorus(t3 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d42 = opSmoothUnion(d40, d41,0.450000); 
	float d43 = sdSphere(t3 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d44 = opSmoothSubtraction(d42, d43,0.300000); 
	float d45 = sdSphere(t3 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d46 = opSmoothSubtraction(d44, d45,0.300000); 
	sdf  = opUnion(sdf, vec4(d46, vec3(1.000000, 0.780392, 0.960784))); 
	float d47 = sdCone(rotate_z(t3 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d47, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t4 = rotate_x(rotate_z(p - vec3(-3.000000, -8.000000, -35.000000),0.174533),0.785398);
db = 0;if (db < 1.0) {
	float d48 = sdSphere(t4 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d49 = sdSphere(t4 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d50 = opSmoothUnion(d48, d49,0.450000); 
	float d51 = sdSphere(t4 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d52 = opSmoothUnion(d50, d51,0.450000); 
	float d53 = sdTorus(t4 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d54 = opSmoothUnion(d52, d53,0.450000); 
	float d55 = sdSphere(t4 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d56 = opSmoothSubtraction(d54, d55,0.300000); 
	float d57 = sdSphere(t4 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d58 = opSmoothSubtraction(d56, d57,0.300000); 
	sdf  = opUnion(sdf, vec4(d58, vec3(1.000000, 0.780392, 0.960784))); 
	float d59 = sdCone(rotate_z(t4 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d59, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t5 = rotate_x(rotate_y(rotate_z(p - vec3(-3.000000, -3.000000, -35.000000),0.349066),0.523599),0.785398);
db = 0;if (db < 1.0) {
	float d60 = sdSphere(t5 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d61 = sdSphere(t5 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d62 = opSmoothUnion(d60, d61,0.450000); 
	float d63 = sdSphere(t5 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d64 = opSmoothUnion(d62, d63,0.450000); 
	float d65 = sdTorus(t5 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d66 = opSmoothUnion(d64, d65,0.450000); 
	float d67 = sdSphere(t5 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d68 = opSmoothSubtraction(d66, d67,0.300000); 
	float d69 = sdSphere(t5 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d70 = opSmoothSubtraction(d68, d69,0.300000); 
	sdf  = opUnion(sdf, vec4(d70, vec3(1.000000, 0.780392, 0.960784))); 
	float d71 = sdCone(rotate_z(t5 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d71, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t6 = rotate_x(rotate_y(rotate_z(p - vec3(-3.000000, 2.000000, -35.000000),0.523599),1.047198),0.785398);
db = 0;if (db < 1.0) {
	float d72 = sdSphere(t6 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d73 = sdSphere(t6 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d74 = opSmoothUnion(d72, d73,0.450000); 
	float d75 = sdSphere(t6 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d76 = opSmoothUnion(d74, d75,0.450000); 
	float d77 = sdTorus(t6 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d78 = opSmoothUnion(d76, d77,0.450000); 
	float d79 = sdSphere(t6 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d80 = opSmoothSubtraction(d78, d79,0.300000); 
	float d81 = sdSphere(t6 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d82 = opSmoothSubtraction(d80, d81,0.300000); 
	sdf  = opUnion(sdf, vec4(d82, vec3(1.000000, 0.780392, 0.960784))); 
	float d83 = sdCone(rotate_z(t6 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d83, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t7 = rotate_x(rotate_y(rotate_z(p - vec3(-3.000000, 7.000000, -35.000000),0.698132),1.570796),0.785398);
db = 0;if (db < 1.0) {
	float d84 = sdSphere(t7 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d85 = sdSphere(t7 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d86 = opSmoothUnion(d84, d85,0.450000); 
	float d87 = sdSphere(t7 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d88 = opSmoothUnion(d86, d87,0.450000); 
	float d89 = sdTorus(t7 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d90 = opSmoothUnion(d88, d89,0.450000); 
	float d91 = sdSphere(t7 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d92 = opSmoothSubtraction(d90, d91,0.300000); 
	float d93 = sdSphere(t7 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d94 = opSmoothSubtraction(d92, d93,0.300000); 
	sdf  = opUnion(sdf, vec4(d94, vec3(1.000000, 0.780392, 0.960784))); 
	float d95 = sdCone(rotate_z(t7 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d95, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t8 = rotate_x(rotate_z(p - vec3(2.000000, -8.000000, -35.000000),0.349066),1.570796);
db = 0;if (db < 1.0) {
	float d96 = sdSphere(t8 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d97 = sdSphere(t8 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d98 = opSmoothUnion(d96, d97,0.450000); 
	float d99 = sdSphere(t8 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d100 = opSmoothUnion(d98, d99,0.450000); 
	float d101 = sdTorus(t8 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d102 = opSmoothUnion(d100, d101,0.450000); 
	float d103 = sdSphere(t8 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d104 = opSmoothSubtraction(d102, d103,0.300000); 
	float d105 = sdSphere(t8 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d106 = opSmoothSubtraction(d104, d105,0.300000); 
	sdf  = opUnion(sdf, vec4(d106, vec3(1.000000, 0.780392, 0.960784))); 
	float d107 = sdCone(rotate_z(t8 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d107, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t9 = rotate_x(rotate_y(rotate_z(p - vec3(2.000000, -3.000000, -35.000000),0.523599),0.523599),1.570796);
db = 0;if (db < 1.0) {
	float d108 = sdSphere(t9 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d109 = sdSphere(t9 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d110 = opSmoothUnion(d108, d109,0.450000); 
	float d111 = sdSphere(t9 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d112 = opSmoothUnion(d110, d111,0.450000); 
	float d113 = sdTorus(t9 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d114 = opSmoothUnion(d112, d113,0.450000); 
	float d115 = sdSphere(t9 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d116 = opSmoothSubtraction(d114, d115,0.300000); 
	float d117 = sdSphere(t9 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d118 = opSmoothSubtraction(d116, d117,0.300000); 
	sdf  = opUnion(sdf, vec4(d118, vec3(1.000000, 0.780392, 0.960784))); 
	float d119 = sdCone(rotate_z(t9 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d119, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t10 = rotate_x(rotate_y(rotate_z(p - vec3(2.000000, 2.000000, -35.000000),0.698132),1.047198),1.570796);
db = 0;if (db < 1.0) {
	float d120 = sdSphere(t10 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d121 = sdSphere(t10 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d122 = opSmoothUnion(d120, d121,0.450000); 
	float d123 = sdSphere(t10 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d124 = opSmoothUnion(d122, d123,0.450000); 
	float d125 = sdTorus(t10 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d126 = opSmoothUnion(d124, d125,0.450000); 
	float d127 = sdSphere(t10 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d128 = opSmoothSubtraction(d126, d127,0.300000); 
	float d129 = sdSphere(t10 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d130 = opSmoothSubtraction(d128, d129,0.300000); 
	sdf  = opUnion(sdf, vec4(d130, vec3(1.000000, 0.780392, 0.960784))); 
	float d131 = sdCone(rotate_z(t10 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d131, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t11 = rotate_x(rotate_y(rotate_z(p - vec3(2.000000, 7.000000, -35.000000),0.872665),1.570796),1.570796);
db = 0;if (db < 1.0) {
	float d132 = sdSphere(t11 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d133 = sdSphere(t11 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d134 = opSmoothUnion(d132, d133,0.450000); 
	float d135 = sdSphere(t11 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d136 = opSmoothUnion(d134, d135,0.450000); 
	float d137 = sdTorus(t11 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d138 = opSmoothUnion(d136, d137,0.450000); 
	float d139 = sdSphere(t11 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d140 = opSmoothSubtraction(d138, d139,0.300000); 
	float d141 = sdSphere(t11 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d142 = opSmoothSubtraction(d140, d141,0.300000); 
	sdf  = opUnion(sdf, vec4(d142, vec3(1.000000, 0.780392, 0.960784))); 
	float d143 = sdCone(rotate_z(t11 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d143, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t12 = rotate_x(rotate_z(p - vec3(7.000000, -8.000000, -35.000000),0.523599),2.356194);
db = 0;if (db < 1.0) {
	float d144 = sdSphere(t12 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d145 = sdSphere(t12 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d146 = opSmoothUnion(d144, d145,0.450000); 
	float d147 = sdSphere(t12 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d148 = opSmoothUnion(d146, d147,0.450000); 
	float d149 = sdTorus(t12 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d150 = opSmoothUnion(d148, d149,0.450000); 
	float d151 = sdSphere(t12 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d152 = opSmoothSubtraction(d150, d151,0.300000); 
	float d153 = sdSphere(t12 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d154 = opSmoothSubtraction(d152, d153,0.300000); 
	sdf  = opUnion(sdf, vec4(d154, vec3(1.000000, 0.780392, 0.960784))); 
	float d155 = sdCone(rotate_z(t12 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d155, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t13 = rotate_x(rotate_y(rotate_z(p - vec3(7.000000, -3.000000, -35.000000),0.698132),0.523599),2.356194);
db = 0;if (db < 1.0) {
	float d156 = sdSphere(t13 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d157 = sdSphere(t13 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d158 = opSmoothUnion(d156, d157,0.450000); 
	float d159 = sdSphere(t13 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d160 = opSmoothUnion(d158, d159,0.450000); 
	float d161 = sdTorus(t13 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d162 = opSmoothUnion(d160, d161,0.450000); 
	float d163 = sdSphere(t13 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d164 = opSmoothSubtraction(d162, d163,0.300000); 
	float d165 = sdSphere(t13 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d166 = opSmoothSubtraction(d164, d165,0.300000); 
	sdf  = opUnion(sdf, vec4(d166, vec3(1.000000, 0.780392, 0.960784))); 
	float d167 = sdCone(rotate_z(t13 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d167, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t14 = rotate_x(rotate_y(rotate_z(p - vec3(7.000000, 2.000000, -35.000000),0.872665),1.047198),2.356194);
db = 0;if (db < 1.0) {
	float d168 = sdSphere(t14 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d169 = sdSphere(t14 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d170 = opSmoothUnion(d168, d169,0.450000); 
	float d171 = sdSphere(t14 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d172 = opSmoothUnion(d170, d171,0.450000); 
	float d173 = sdTorus(t14 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d174 = opSmoothUnion(d172, d173,0.450000); 
	float d175 = sdSphere(t14 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d176 = opSmoothSubtraction(d174, d175,0.300000); 
	float d177 = sdSphere(t14 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d178 = opSmoothSubtraction(d176, d177,0.300000); 
	sdf  = opUnion(sdf, vec4(d178, vec3(1.000000, 0.780392, 0.960784))); 
	float d179 = sdCone(rotate_z(t14 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d179, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t15 = rotate_x(rotate_y(rotate_z(p - vec3(7.000000, 7.000000, -35.000000),1.047198),1.570796),2.356194);
db = 0;if (db < 1.0) {
	float d180 = sdSphere(t15 - vec3(0.000000, 1.600000, -0.000000), 1.300000);
	float d181 = sdSphere(t15 - vec3(0.800000, 1.200000, 0.900000), 0.600000);
	float d182 = opSmoothUnion(d180, d181,0.450000); 
	float d183 = sdSphere(t15 - vec3(-0.800000, 1.200000, 0.800000), 0.800000);
	float d184 = opSmoothUnion(d182, d183,0.450000); 
	float d185 = sdTorus(t15 - vec3(0.000000, 0.600000, -0.000000), vec2(1.300000, 0.500000)); 
	float d186 = opSmoothUnion(d184, d185,0.450000); 
	float d187 = sdSphere(t15 - vec3(0.800000, 2.800000, 0.600000), 0.400000);
	float d188 = opSmoothSubtraction(d186, d187,0.300000); 
	float d189 = sdSphere(t15 - vec3(0.100000, 3.000000, 0.400000), 0.700000);
	float d190 = opSmoothSubtraction(d188, d189,0.300000); 
	sdf  = opUnion(sdf, vec4(d190, vec3(1.000000, 0.780392, 0.960784))); 
	float d191 = sdCone(rotate_z(t15 - vec3(0.000000, -1.500000, -0.000000),3.141593), 1.000000, 4.000000); 
	sdf  = opUnion(sdf, vec4(d191, vec3(0.670588, 0.498039, 0.349020))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
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
       col = Cd *vec3(0.000000, 0.000000, 0.000000);
       vec3 p = ro + rd * t;
       vec3 N = calcNormal(p);
       vec3 L, CL, distL;
       float LdotN, shadL, falloffL;
       col += 0.400000 * Cd;
	L = vec3(0.000000, 0.928477, 0.148556);
	CL = 0.700000 * vec3(1.000000, 1.000000, 1.000000);
	LdotN = clamp(dot(L, N), 0., 1.);
	shadL = shadow(p, L, 0.01, 1.0);
	col += Cd * CL * LdotN * shadL;
	distL = vec3(2.000000, 3.000000, -1.000000) - p;
	L = normalize ( distL );
	shadL = shadow(p, L, 0.01, length(distL));
	falloffL = dot(distL, distL);
	falloffL *= falloffL; 
	CL = 0.500000 * vec3(1.000000, 0.866667, 0.549020)/falloffL;
	LdotN = clamp(dot(L, N), 0., 1.);
	col += Cd * CL * LdotN * shadL;
   return col;}
   return vec3(0.780392, 0.909804, 1.000000);
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
