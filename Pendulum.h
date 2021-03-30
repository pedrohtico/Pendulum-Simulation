#pragma once

#include <allegro5/allegro5.h>

typedef struct Circle {
	double cx, cy, radius;
	ALLEGRO_COLOR color;
} Circle;

class Pendulum {
protected:
	Circle bob;
	double px, py; // pivot x, pivot y
	double L, H;  // string length and bob height
	double mass;
	double amplitude, ang_vel, ang_acc;
	double damping;
	double kinetic_en, potential_en, mechanical_en;

public:
	Pendulum(double px, double py, double L, double amplitude, double mass) {
		this->px = px;
		this->py = py;
		this->L = L;
		this->amplitude = amplitude;
		this->mass = mass;
		this->bob.radius = mass;
		this->bob.color = al_map_rgb_f(0.9, 0.9, 0.9);
		this->ang_acc = this->ang_vel = 0;
		this->damping = 1;
		this->H = 0;
		this->kinetic_en = this->potential_en = this->mechanical_en = 0;
	}

	virtual void update(const double &gravity) = 0;
	virtual void render() = 0;

	// SETTERS AND GETTERS

	double get_pivotx() { return this->px; }
	double get_pivoty() { return this->py; }
	double get_L() { return this->L; }
	double get_amplitude() { return this->amplitude; }
};