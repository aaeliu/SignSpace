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
vec3 t0 = rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799);
db = sdSphere(p - vec3(0.000000, 0.000000, -(2.000000)), 5.88396);
if (db < 1.0) {
db = sdSphere( rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799), 4.21403);
if (db < 1.0) {
	float d5 = sdSphere(rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799) - vec3(0.000000, -0.750000, -0.000000), 2.000000);
	float d6 = sdSphere(rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799) - vec3(-0.150000, 1.250000, -0.000000), 1.500000);
	float d7 = opSmoothUnion(d5, d6,0.250000); 
	float d8 = sdSphere(rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799) - vec3((sin(time)*-0.300000), 3.200000, -0.000000), 1.000000);
	float d9 = opSmoothUnion(d7, d8,0.250000); 
	sdf  = opUnion(sdf, vec4(d9, vec3(0.901961, 0.901961, 0.941176))); 
}
db = sdSphere( rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799), 5.88396);
if (db < 1.0) {
	float d10 = sdCylinder(rotate_z(rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799) - vec3(-0.400000, 3.800000, -0.000000),-0.261799), 1.250000, 0.100000); 
	sdf  = opUnion(sdf, vec4(d10, vec3(0.078431, 0.078431, 0.078431))); 
	float d11 = sdCylinder(rotate_z(rotate_z(p - vec3(0.000000, 0.000000, -(2.000000)),-0.261799) - vec3(-0.560000, 4.600000, -0.000000),-0.261799), 1.000000, 0.750000); 
	sdf  = opUnion(sdf, vec4(d11, vec3(0.078431, 0.078431, 0.078431))); 
}
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
	float d12 = sdCylinder(rotate_z(p - vec3(-1.600000, -1.800000, -0.000000),-0.261799), 0.200000, 1.750000); 
   sdf = opUnion(sdf, vec4(d12, vec3(0.588235, 0.274510, 0.196078)));
	float d13 = sdCylinder(rotate_z(p - vec3(1.400000, 2.200000, -2.000000),-0.261799), 0.180000, 1.750000); 
	float d14 = sdCylinder(rotate_z(p - vec3(3.000000, 3.300000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d15 = opSmoothUnion(d13, d14,0.250000); 
	float d16 = sdCylinder(rotate_z(p - vec3(3.000000, 3.500000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d17 = opSmoothUnion(d15, d16,0.250000); 
	float d18 = sdCylinder(rotate_z(p - vec3(2.800000, 3.600000, -2.000000),-0.261799), 0.070000, 0.200000); 
	float d19 = opSmoothUnion(d17, d18,0.250000); 
	float d20 = sdSphere(p - vec3(1.800000, 2.700000, -2.000000), 0.100000);
	float d21 = opSmoothSubtraction(d19, d20,0.250000); 
	float d22 = sdSphere(p - vec3(2.500000, 3.300000, -2.000000), 0.130000);
	float d23 = opSmoothSubtraction(d21, d22,0.250000); 
   sdf = opUnion(sdf, vec4(d23, vec3(0.588235, 0.274510, 0.196078)));
vec3 t1 = p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000));
db = sdSphere(p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d24 = sdCone(p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000)) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d25 = sdCone(p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000)) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d26 = opSmoothUnion(d24, d25,0.250000); 
	float d27 = sdCone(p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000)) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d28 = opSmoothUnion(d26, d27,0.250000); 
	sdf  = opUnion(sdf, vec4(d28, vec3(0.274510, 0.623529, 0.274510))); 
	float d29 = sdCylinder(p - vec3((sin((time*3.000000))+-10.000000), (cos((time*3.000000))+2.000000), -(15.000000)) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d29, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t2 = rotate_x(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),0.349066);
db = sdSphere(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d30 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),0.349066) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d31 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),0.349066) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d32 = opSmoothUnion(d30, d31,0.250000); 
	float d33 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),0.349066) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d34 = opSmoothUnion(d32, d33,0.250000); 
	sdf  = opUnion(sdf, vec4(d34, vec3(0.274510, 0.623529, 0.274510))); 
	float d35 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+-7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),0.349066) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d35, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t3 = rotate_x(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),0.698132);
db = sdSphere(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d36 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),0.698132) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d37 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),0.698132) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d38 = opSmoothUnion(d36, d37,0.250000); 
	float d39 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),0.698132) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d40 = opSmoothUnion(d38, d39,0.250000); 
	sdf  = opUnion(sdf, vec4(d40, vec3(0.274510, 0.623529, 0.274510))); 
	float d41 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+-5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),0.698132) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d41, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t4 = rotate_x(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.047198);
db = sdSphere(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d42 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.047198) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d43 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.047198) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d44 = opSmoothUnion(d42, d43,0.250000); 
	float d45 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.047198) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d46 = opSmoothUnion(d44, d45,0.250000); 
	sdf  = opUnion(sdf, vec4(d46, vec3(0.274510, 0.623529, 0.274510))); 
	float d47 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+-2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.047198) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d47, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t5 = rotate_x(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)),1.396263);
db = sdSphere(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d48 = sdCone(rotate_x(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)),1.396263) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d49 = sdCone(rotate_x(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)),1.396263) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d50 = opSmoothUnion(d48, d49,0.250000); 
	float d51 = sdCone(rotate_x(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)),1.396263) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d52 = opSmoothUnion(d50, d51,0.250000); 
	sdf  = opUnion(sdf, vec4(d52, vec3(0.274510, 0.623529, 0.274510))); 
	float d53 = sdCylinder(rotate_x(p - vec3(sin((time*3.000000)), (cos((time*3.000000))+2.000000), -(15.000000)),1.396263) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d53, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t6 = rotate_x(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.745329);
db = sdSphere(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d54 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.745329) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d55 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.745329) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d56 = opSmoothUnion(d54, d55,0.250000); 
	float d57 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.745329) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d58 = opSmoothUnion(d56, d57,0.250000); 
	sdf  = opUnion(sdf, vec4(d58, vec3(0.274510, 0.623529, 0.274510))); 
	float d59 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+2.500000), (cos((time*3.000000))+2.000000), -(15.000000)),1.745329) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d59, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t7 = rotate_x(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.094395);
db = sdSphere(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d60 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.094395) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d61 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.094395) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d62 = opSmoothUnion(d60, d61,0.250000); 
	float d63 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.094395) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d64 = opSmoothUnion(d62, d63,0.250000); 
	sdf  = opUnion(sdf, vec4(d64, vec3(0.274510, 0.623529, 0.274510))); 
	float d65 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+5.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.094395) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d65, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t8 = rotate_x(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),2.443461);
db = sdSphere(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d66 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),2.443461) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d67 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),2.443461) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d68 = opSmoothUnion(d66, d67,0.250000); 
	float d69 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),2.443461) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d70 = opSmoothUnion(d68, d69,0.250000); 
	sdf  = opUnion(sdf, vec4(d70, vec3(0.274510, 0.623529, 0.274510))); 
	float d71 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+7.500000), (cos((time*3.000000))+2.000000), -(15.000000)),2.443461) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d71, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t9 = rotate_x(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.792527);
db = sdSphere(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d72 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.792527) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d73 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.792527) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d74 = opSmoothUnion(d72, d73,0.250000); 
	float d75 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.792527) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d76 = opSmoothUnion(d74, d75,0.250000); 
	sdf  = opUnion(sdf, vec4(d76, vec3(0.274510, 0.623529, 0.274510))); 
	float d77 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+10.000000), (cos((time*3.000000))+2.000000), -(15.000000)),2.792527) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d77, vec3(0.588235, 0.274510, 0.196078))); 
}
else { sdf = opUnion (sdf, vec4(db, 1.0, 1.0, 1.0)); }
vec3 t10 = rotate_x(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)),3.141593);
db = sdSphere(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)), 4.03961);
if (db < 1.0) {
	float d78 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)),3.141593) - vec3(0.000000, 0.000000, -0.000000), 1.000000, 1.600000); 
	float d79 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)),3.141593) - vec3(0.000000, -1.000000, -0.000000), 1.400000, 2.000000); 
	float d80 = opSmoothUnion(d78, d79,0.250000); 
	float d81 = sdCone(rotate_x(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)),3.141593) - vec3(0.000000, -1.600000, -0.000000), 1.400000, 2.400000); 
	float d82 = opSmoothUnion(d80, d81,0.250000); 
	sdf  = opUnion(sdf, vec4(d82, vec3(0.274510, 0.623529, 0.274510))); 
	float d83 = sdCylinder(rotate_x(p - vec3((sin((time*3.000000))+12.500000), (cos((time*3.000000))+2.000000), -(15.000000)),3.141593) - vec3(0.000000, -2.000000, -0.000000), 0.400000, 2.000000); 
	sdf  = opUnion(sdf, vec4(d83, vec3(0.588235, 0.274510, 0.196078))); 
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
