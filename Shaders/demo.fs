// BASIC RAY-MARCHING CLASS DEMO!
//
// Numerous methods borrowed from iq articles:
//   https://iquilezles.org/www/index.htm
// 
// 3D signed distance functions:
//   https://iquilezles.org/articles/distfunctions
// 
// Shadows:
//   https://iquilezles.org/articles/rmshadows
// 
// Ray-marching SDFs:
//   https://iquilezles.org/articles/raymarchingdf
// 
// Normals for SDFs:
//   https://iquilezles.org/articles/normalsSDF
// subtracts d1 from d2
float opUnion( float d1, float d2 ) {  return min(d1,d2); }
vec4  opUnion(vec4 d1, vec4 d2) {
 return (d1.x < d2.x ? d1 : d2);   
}

float opIntersection( float d1, float d2 ) { return max(d1,d2); }
vec4  opIntersection( vec4  d1, vec4  d2 ) {
 return (d1.x > d2.x ? d1 : d2);   
    
}
float opSubtraction( float d1, float d2 ) { return max(-d1,d2); }
vec4  opSubtraction( vec4  d1, vec4  d2 ) { 
  return opIntersection(vec4(-d1.x,d1.yzw), d2);
}

float opSmoothUnion( float d1, float d2, float k ) {
    float h = clamp( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) - k*h*(1.0-h); }

float opSmoothSubtraction( float d1, float d2, float k ) {
    float h = clamp( 0.5 - 0.5*(d2+d1)/k, 0.0, 1.0 );
    return mix( d2, -d1, h ) + k*h*(1.0-h); }

float opSmoothIntersection( float d1, float d2, float k ) {
    float h = clamp( 0.5 - 0.5*(d2-d1)/k, 0.0, 1.0 );
    return mix( d2, d1, h ) + k*h*(1.0-h); }
    

    
vec3 rotate_y(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		+ca, +.0, -sa,
		+.0,+1.0, +.0,
		+sa, +.0, +ca);
}
vec3 rotate_x(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		+1.0, +.0, +.0,
		+.0, +ca, -sa,
		+.0, +sa, +ca);
}
vec3 rotate_z(vec3 v, float angle)
{
	float ca = cos(angle); float sa = sin(angle);
	return v*mat3(
		+ca, -sa, +.0,
		+sa, +ca, 0.,
		+.0, +.0, 1.);
}
float opOnion( in float sdf, in float thickness )
{
    return abs(sdf)-thickness;
}

float sdSphere( vec3 p, float s )
{
  return length(p)-s;
}

float sdTorus( vec3 p, vec2 t )
{
  vec2 q = vec2(length(p.xz)-t.x,p.y);
  return length(q)-t.y;
}

float sdRoundCone( vec3 p, float r1, float r2, float h )
{
  vec2 q = vec2( length(p.xz), p.y );
    
  float b = (r1-r2)/h;
  float a = sqrt(1.0-b*b);
  float k = dot(q,vec2(-b,a));
    
  if( k < 0.0 ) return length(q) - r1;
  if( k > a*h ) return length(q-vec2(0.0,h)) - r2;
        
  return dot(q, vec2(a,b) ) - r1;
}
const vec3 catCenter = vec3(0., 0., -0.5);
const vec3 catCol = vec3(242., 235., 233.)/255.;
const vec3 collar = vec3(181., 23., 2.)/255.;
const vec3 gold = vec3(230., 184., 21.)/255.;

vec4 mapV4(in vec3 p)
{
    vec3 center = p - catCenter;
    vec4 sdf = vec4(100000., -1., 0., 0.);
    float d1 = sdSphere(center, 0.13);
    sdf = vec4(d1, vec3(1., 0., 0.));
    float d2 = sdSphere(center+vec3(0.6, 0., 0.), 0.26);
    float d3 = opUnion (d1, d2);
    sdf = opUnion(sdf, vec4(d2, vec3(0., 0., 1.)));

    return sdf;
}

float map(in vec3 p)
{
    return mapV4(p).x;// just sdf value
}


vec3 calcNormal( in vec3 pos )
{
    vec2 e = vec2(1.0,-1.0)*0.5773*0.001;
    return normalize( e.xyy*map( pos + e.xyy ) + 
					  e.yyx*map( pos + e.yyx ) + 
					  e.yxy*map( pos + e.yxy ) + 
					  e.xxx*map( pos + e.xxx ) );
}

// Vector raymarch: 
// .x   : t* value of surface, or -1 if didn't hit anything.
// .yzw : pass-thru from mapV4.yzw
// 
vec4 raymarchV4(in vec3 ro, in vec3 rd) 
{
    //int steps = int(round(200.0*iMouse.y/iResolution.y));
    float t = 0.0;
    for(int i=0; i<513; i++) {
        vec3  rt = ro + rd*t;
        vec4  f  = mapV4(rt);
		float d  = f.x;
        
        if(d<0.001) {// We hit it or went too far
            f.x = t; // replace .x's sdf with t*
            //f.yzw = vec3(1.,0.,0.);
            return f;
        }
        else {// keep marching
         	t += 0.9*d; // conservative/smaller step for inexact/warped SDFs
        }
        
        if(t > 100.) {
            f.x = -1.;// -ve t* --> didn't hit anything
            return f;
        }
    }
    
	return vec4(-1., vec3(0.)); // didn't hit anything
}

/// Returns t* value of surface, or -1. if didn't hit anything.
float raymarch(in vec3 ro, in vec3 rd) 
{
    return raymarchV4(ro,rd).x;  
}

float shadow( in vec3 ro, in vec3 rd, float mint, float maxt )
{
    for( float t=mint; t<maxt; )
    {
        float h = map(ro + rd*t);
        if( h<0.001 )
            return 0.;
        t += 0.95*h;//can do slightly less for not-quite-SDFs
    }
    return 1.0;
}
float softshadow( in vec3 ro, in vec3 rd, float mint, float maxt, float k )
{
    float res = 1.0;
    float ph = 1e20;
    for( float t=mint; t<maxt; )
    {
        float h = map(ro + rd*t);
        if( h<0.001 )
            return 0.0;
        
        float y = h*h/(2.0*ph);
        float d = sqrt(h*h-y*y);
        res = min( res, k*d/max(0.0,t-y) );
        ph = h;
        t += 0.95*h;//slightly less for not-quite-SDFs
    }
    return res;
}

vec3 render(in vec3 ro, in vec3 rd) 
{
    vec3  col = vec3(0.,0.,0.);    // init color to background
    vec4  ray = raymarchV4(ro, rd);// compute distance along ray to surface
    float t   = ray.x;
    vec3  Cd  = ray.yzw;// can passthru other shading values, e.g., objectID, but we did color.
    

    
    if(t>0.0) {//hit surface --> shade it:   
      //return vec3(1.0, 0.,0.);
	    vec3  p  = ro + rd*t; // point on surface
        vec3  N  = calcNormal(p); // sdf normal
        
        // DETERMINE MATERIAL COLOR: (todo: all orange for now)
        //vec3  Cd = vec3(231./255., 111./255., 3./255.); // diffuse color
        
        // DIRECTIONAL LIGHT:
        vec3  posL   = ro+ .5*vec3(0.5, 5.,0.);// light at eye (safe!)
        vec3  L      = normalize(posL - p);
        vec3  CL     = vec3(1.);// directional light color
        float LdotN  = clamp(dot(L,N), 0., 1.);
        //float shadL  = shadow(p, L, 0.01, 10.);
        float sshadL = softshadow(p, L, 0.05, length(posL-p), 2.);
	    col = Cd * CL * LdotN * sshadL;// * sshadL; // * occ;
        
        //ominous red glow
        /*vec3  posL2  = catCenter + 3.*vec3(sin(10.*iTime),cos(3.*iTime),cos(5.*iTime));
        vec3  L2     = normalize(posL2 - p);
        vec3  CL2    = vec3(1.,1., 1.);
        float L2dotN = clamp(dot(L2,N), 0., 1.);
        float shadL2  = shadow(p, L2, 0.02, length(posL2-p));
        col += Cd * CL2 * L2dotN * shadL2; // * occ;     */
        

    }
    
    return col;
}
out vec4 FragColor;
in vec2 pos;
void main(  )
{
    vec2 pXY = vec2(pos.x, pos.y * 6.0/8.0); // normalized coordinates (unit height)
    vec3 pix = vec3(pXY,    0.);    // position of virtual pixel (Z=0 depth)
    vec3 ro  = vec3(0,0., 3. );    // ray origin (EYE POSITION).. controls field-of-view
    vec3 rd  = normalize(pix - ro); // ray direction
    
    vec3 col = render(ro, rd); // ray-march and evaluate color

    // Output to screen
    FragColor = vec4(col,1.0);
}