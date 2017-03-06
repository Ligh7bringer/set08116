#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>
#include "glm/ext.hpp"

using namespace std;
using namespace glm;

int main() {
	vec2 a(4.0f, 1.0f);
	vec2 b(1.0f, 3.0f);
    vec3 c(2.5f, 0.0f, 0.0f);
	vec3 d(0.0f, 0.0f, 6.0f);
	vec4 e(0.0f, 3.6f, 0.0f, 0.0f);
	vec4 f(0.0f, 0.0f, 0.0f, 4.3f);

	//converting 2d
	vec3 g(vec2(a));
	vec4 h(vec3(vec2(0.0f, 3.0f), 0.0f), 0.0f);

	// converting 3d
	vec2 i(vec3(2.5f, 0.0f, 0.0f));
	vec4 j(vec3(0.0f, 0.0f, 6.0f), 0.0f);

	//converting 4d
	vec2 k(vec3(vec4(0.0f, 3.6f, 0.0f, 4.3f)));
	vec3 l(vec4(0.0f, 0.0f, 0.0f, 4.3f));

	//addition
	vec2 m = a + b;
	vec2 n = a - b;
	cout << to_string(m) << endl;
	cout << to_string(n) << endl;

	vec3 o = c + d;
	vec3 p = c - d;
	cout << to_string(o) << endl;
	cout << to_string(p) << endl;

	vec4 q = e + f; 
	vec4 r = e - f;
	cout << to_string(q) << endl;
	cout << to_string(r) << endl;

	// * and /
	vec2 s = 2.0f * a;
	vec2 t = b / 3.0f;
	cout << to_string(s) << endl;
	cout << to_string(t) << endl;

	vec3 u = 2.0f * c;
	vec3 v = d / 6.0f;

	vec4 w = 5.0f * e;
	vec4 x = f / 4.3f;

	//length
	float ll = length(c);
	cout << to_string(ll) << endl;

	//normalise
	vec4 nn = normalize(f);
	cout << to_string(nn) << endl;

	float dd = dot(a, b);
	cout << to_string(dd) << endl;

	vec2 pp = proj(a, b);
	cout << to_string(pp) << endl;

	vec3 cp = cross(c, d);
	cout << to_string(cp) << endl;
	
	//to be continued


	cin.get();
}