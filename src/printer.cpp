#include "printer.h"

printer::printer (std::string filename, scene* c) {
  file = std::ofstream (filename, std::ios::out | std::ios::trunc);
  context = c;
}

void printer::print_sdf_functions () {
  file << "float opUnion( float d1, float d2 ) {  return min(d1,d2); }" << std::endl;
  file << "vec4  opUnion(vec4 d1, vec4 d2) { return (d1.x < d2.x ? d1 : d2); }" << std::endl;
  file << "float sdSphere (vec3 p, float s) { return length(p) - s; }" << std::endl;
}


void printer::print_raymarch (int steps) {
  file << "vec4 raymarch(in vec3 ro, in vec3 rd) {" << std::endl;
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
}


/*
    This is the function where the scene gets describeddd
*/
void printer::print_map() {
    file << "vec4 mapV4(in vec3 p) {" << std::endl;
    file << "   vec4 sdf = vec4 (0., 0., 0., 0.);" << std::endl;
    int d = 0;
    for (auto &p : context->shapes) {
        p->print(file, d);
        // file << "float d" << ++d << " = sdPenis" << std::endl;
        if (d > 0) {
            file << "   sdf = opUnion(sdf, vec4(d" << d << ", vec3 (1.0, 0.0, 0.0 )));" << std::endl;
        }
        else {
            file << "   sdf = vec4(d" << d << ", vec3(1.0, 0.0, 0.0));" << std::endl;
        }
        d++;
    }
    file << "\t return sdf;" << std::endl;
    file << "}" << std::endl;

    file << "float map(in vec3 p) { return mapV4(p).x; }" << std::endl;
}

void printer::print_render() {

}

void printer::print_main() {
    file << "out vec4 FragColor;" << std::endl;
    file << "in vec2 pos;" << std::endl;
    file << "void main () {" << std::endl;
    file << "  FragColor = vec4(pos, 0.3f, 1.0f);" << std::endl;
    file << "}" << std::endl;


}
void printer::print () {

  if (file.is_open ()) {
    file << "#version 330 core" << std::endl;

    print_sdf_functions ();
    print_map();
    print_raymarch (500);
    print_render();
    print_main ();

    file.close ();

  } else {
    std::cerr << "File opening error" << std::endl;
  }

}