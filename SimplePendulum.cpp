#include "SimplePendulum.h"

#include <allegro5/allegro_primitives.h>
#include <math.h>

SimplePendulum::SimplePendulum(double px, double py, double L, double amplitude, double mass)
	: Pendulum(px, py, L, amplitude, mass) {}

void SimplePendulum::update(const double& gravity) {
	ang_acc = (-1 * gravity / L) * sin(amplitude);
	ang_vel += ang_acc;
	ang_vel *= damping;
	amplitude += ang_vel;

	bob.cx = L * sin(amplitude);
	bob.cy = L * cos(amplitude);
	bob.cx += px;
	bob.cy += py;

	H = L * (1 - cos(amplitude));
	potential_en = mass * gravity * H;
	kinetic_en = mass * pow(ang_vel, 2) * 0.5;
}

void SimplePendulum::render() {
	// draw string
	al_draw_line(px, py, bob.cx, bob.cy, bob.color, 1);

	// draw pivot
	al_draw_filled_circle(px, py, 5, al_map_rgb_f(0.8, 0, 0));

	// draw potential energy
	al_draw_line(bob.cx, bob.cy, bob.cx, bob.cy + potential_en / 70, al_map_rgb_f(0, 1, 0), 2);

	//draw kinetic energy
	al_draw_line(bob.cx, bob.cy, bob.cx, bob.cy - kinetic_en * 1000, al_map_rgb_f(1, 1, 0), 2);

	// draw bob
	al_draw_filled_circle(bob.cx, bob.cy, bob.radius, bob.color);
}