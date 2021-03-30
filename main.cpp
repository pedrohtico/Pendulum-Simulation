#include <iostream>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#include "SimplePendulum.h"

void must_init(const bool &expr, const std::string &description) {
	if (expr) return;
	
	std::cout << "Couldn't initialize " << description << std::endl;
	exit(1);
}

int main() {
	// ----- Allegro Initialization -----
	must_init(al_init(), "allegro5");
	must_init(al_install_keyboard(), "allegro5 keyboard");

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	must_init(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
	ALLEGRO_DISPLAY* disp = al_create_display(800, 600);
	must_init(disp, "display");

    must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));

    // ----- MAIN LOOP -----

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    const double PI = 3.14159265358979323846; // PI_CONSTANT
    
    // gravitys
    const double earth_gravity = 9.80665;
    const double moon_gravity = 1.625;
    const double sun_gravity = 274;
    const double jupyter_gravity = 24.79;
    double px = 400;
    double py = 100;
    SimplePendulum* p1 = new SimplePendulum(px, py, 150, PI / 2, 5);
    SimplePendulum* p2 = new SimplePendulum(px, py, 300, PI / 4, 15);
    SimplePendulum* p3 = new SimplePendulum(px, py, 350, 3 * PI / 2, 10);

    // CHANGE GRAVITY FOR ALL PENDULUMS HERE
    double g = moon_gravity;

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            // ----- UPDATE -----
            p1->update(g);
            p2->update(g);
            p3->update(g);

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            // ----- RENDER -----
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            p1->render();
            p2->render();
            p3->render();

            al_flip_display();

            redraw = false;
        }
    }

    // ----- TERMINATION -----
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}