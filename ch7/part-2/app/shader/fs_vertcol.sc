$input v_color0

uniform vec4 u_color;

#include <bgfx_shader.sh>

void main() {
    gl_FragColor = v_color0 * u_color;
}
