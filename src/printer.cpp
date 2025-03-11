#include "printer.h"

printer::printer (std::string filename, scene* c) {
  file = std::ofstream (filename, std::ios::out | std::ios::trunc);
  context = c;
}

void printer::print_uniforms() {
    file << "uniform vec3 camTransform;" << std::endl;
}

// src: https://iquilezles.org/articles/distfunctions/
void printer::print_sdf_functions () {
  file << "float opUnion( float d1, float d2 ) {  return min(d1,d2); }" << std::endl;
  file << "vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }" << std::endl;
  file << "float sdSphere (vec3 p, float s) { return length(p) - s; }" << std::endl;
  file << "float sdBox (vec3 p, vec3 b) {vec3 q = abs(p) - b;return length(max(q,0.0)) + min(max(q.x,max(q.y,q.z)),0.0);}" << std::endl;
  file << "float sdCone(vec3 p, float r, float h) { vec2 q = vec2(length(p.xz) - r, p.y + 0.5 * h); vec2 e = vec2(-r, h); vec2 d1 = q - e * clamp(dot(q, e) / dot(e, e), 0.0, 1.0); vec2 d2 = vec2(max(q.x, 0.0), -q.y); return sqrt(min(dot(d1, d1), dot(d2, d2))) * sign(max(max(d1.x, d1.y), d2.y)); }" << std::endl;
  file << "float sdTorus(vec3 p, vec2 t) { vec2 q = vec2(length(p.xz) - t.x, p.y); return length(q) - t.y; }" << std::endl;
  file << "float sdCylinder( vec3 p, float r, float h ) { vec2 d = abs(vec2(length(p.xz), p.y)) - vec2(r, h); return min(max(d.x, d.y), 0.0) + length(max(d, 0.0));}" << std::endl;
  file << "float opSmoothUnion( float d1, float d2, float k ) { float h = clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0); return mix(d2, d1, h) - k * h * (1.0 - h); }" << std::endl;
  file << "float opSubtraction( float d1, float d2 ) { return max(d1,-d2); }" << std::endl;
  file << "float opSmoothSubtraction( float d1, float d2, float k ) { float h = clamp(0.5 - 0.5 * (d2 + d1) / k, 0.0, 1.0); return mix(d1, -d2, h) + k * h * (1.0 - h); }" << std::endl;
  file << "float opIntersection( float d1, float d2 ) { return max(d1, d2); }" << std::endl;
  file << "float opSmoothIntersection( float d1, float d2, float k ) { float h = clamp(0.5 - 0.5 * (d2 - d1) / k, 0.0, 1.0); return mix(d2, d1, h) + k * h * (1.0 - h); }" << std::endl;
  file << "vec3 rotate_x(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +1.0, +.0, +.0, +.0, +ca, -sa, +.0, +sa, +ca); }" << std::endl;
  file << "vec3 rotate_y(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +ca, +.0, -sa, +.0, +1.0, +.0, +sa, +.0, +ca); }" << std::endl;
  file << "vec3 rotate_z(vec3 v, float angle) { float ca = cos(angle); float sa = sin(angle); return v * mat3( +ca, -sa, +.0, +sa, +ca, 0., +.0, +.0, 1.); }" << std::endl;
}


void printer::print_raymarch (int steps) {
  file << "vec4 raymarchV4(in vec3 ro, in vec3 rd) {" << std::endl;
  file << "\tfloat t = 0.0;" << std::endl;
  file << "\tfor (int i = 0; i < " << steps << "; i++) {" << std::endl;
  file << "\tvec3  rt = ro + rd*t;" << std::endl;
  file << "\tvec4 f = mapV4(rt);\n\
            \tfloat d = f.x;\n\
            \tif (d < 0.001) {\n\
            \tf.x = t;\n\
            \t\t    return f;\n\
            \t}\n\
            \telse {\n\
            \t\t   t += 0.9*d;\n\
            \t}\n\
            \tif (t > 100.) {\n\
            \t\tf.x = -1;\n\
            \t\treturn f;\n\
            \t}" << std::endl;
  file << " }" << std::endl;
  file << "}" << std::endl;

  file << "float raymarch(in vec3 ro, in vec3 rd)  { return raymarchV4(ro, rd).x; }" << std::endl;
}


/*
    This is the function where the scene gets describeddd
*/
void printer::print_map() {
    file << "vec4 mapV4(in vec3 p) {" << std::endl;
    file << "   vec4 sdf = vec4 (0., 0., 0., 0.);" << std::endl;
    file << "   vec4 sdf_ = vec4 (0., 0., 0., 0.);" << std::endl;
    int d = 0;
    int i = 0;
    for (auto &p : context->shapes) {
        d = p->print(file, d);
        if (i > 0) {
            // union operation is implicit when there are multiple shapes in the scene.
            if (p->is_custom) {
                file << "   sdf = opUnion(sdf, sdf_);" << std::endl;
            }
            else {
                file << "   sdf = opUnion(sdf, vec4(d" << d << ", " << p->col->print() << "));" << std::endl;
            }
        }
        else {
            if (p->is_custom) {
                file << "   sdf = sdf_;" << std::endl;
            }
            else {
                file << "   sdf = vec4(d" << d << ", " << p->col->print() << ");" << std::endl;
            }
        }
        d++; i++;
    }
    file << "\t return sdf;" << std::endl;
    file << "}" << std::endl;

    file << "float map(in vec3 p) { return mapV4(p).x; }" << std::endl;

    file << "vec3 calcNormal( in vec3 pos ){\n\
        vec2 e = vec2(1.0, -1.0) * 0.5773 * 0.001;\n\
        return normalize(e.xyy * map(pos + e.xyy) +\n\
        e.yyx * map(pos + e.yyx) +\n\
        e.yxy * map(pos + e.yxy) +\n\
        e.xxx * map(pos + e.xxx)); \n}" << std::endl;
}

/* These functions come from https://iquilezles.org/articles/rmshadows/
*/
void printer::print_shadow_functions() {
    file << "float shadow(in vec3 ro, in vec3 rd, float mint, float maxt) {\n\
        float t = mint;\n\
        for (int i = 0; i < 256 && t < maxt; i++)\n\
        {\n\
            float h = map(ro + rd * t);\n\
            if (h < 0.0005)\n\
                return 0.0;\n\
            t += h;\n\
        }\n\
        return 1.0;\n\
    }" << std::endl;
}

void printer::print_render() {
    file << "vec3 render(in vec3 ro, in vec3 rd)  {" << std::endl;
    file << "   vec3 col = vec3(0.,0.,0.);" << std::endl;
    file << "   vec4  ray = raymarchV4(ro, rd);" << std::endl;
    file << "   float t = ray.x;" << std::endl;
    file << "   vec3 Cd = ray.yzw;" << std::endl;
    file << "   if (t > 0.0) {" << std::endl;
    file << "       vec3 p = ro + rd * t;" << std::endl;
    file << "       vec3 N = calcNormal(p);" << std::endl;
    file << "       vec3 L, CL, distL;" << std::endl;
    file << "       float LdotN, shadL, falloffL;" << std::endl;

    // TODO: insert lighting / shadow equations here.
    file << "       col += " << context->ambient_factor << " * Cd;" << std::endl;
    for (const auto& light : context->lights) {
        light->print(file);
    }

    file << "   return col;}" << std::endl;
    file << "   return " << context->background.print() << ";" << std::endl;
    file << "}" << std::endl;
}

void printer::print_main() {
    file << "out vec4 FragColor;" << std::endl;
    file << "in vec2 pos;" << std::endl;
    file << "void main () {" << std::endl;
    file << "   vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); " << std::endl;
    file << "   vec3 pix = vec3(pXY.x, pXY.y, 12.) + camTransform;" << std::endl;
    file << "   vec3 ro  = vec3(0.,0., 15. ) + camTransform;" << std::endl;
    file << "   vec3 rd  = normalize(pix - ro);" << std::endl;
    file << "   vec3 col = render(ro, rd);" << std::endl;
    file << "  FragColor = vec4(col, 1.0f);" << std::endl;
    file << "}" << std::endl;


}
void printer::print () {

  if (file.is_open ()) {
    file << "#version 330 core" << std::endl;

    print_uniforms();
    print_sdf_functions ();
    print_map();
    print_raymarch (500);
    print_shadow_functions();
    print_render();
    print_main ();

    file.close ();

  } else {
    std::cerr << "File opening error" << std::endl;
  }

}