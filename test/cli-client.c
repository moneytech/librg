#define LIBRG_IMPLEMENTATION
#define LIBRG_DEBUG
#include <librg.h>

typedef struct {
    zplm_vec3_t a;
    zplm_vec3_t b;
    zplm_vec3_t c;
    zplm_vec3_t d;
    zplm_vec3_t e;
    zplm_vec3_t f;
} foo_t;

enum {
    component_foo = librg_component_last,
};

librg_component(foo, component_foo, foo_t);

void on_connect_request(librg_event_t *event) {
    librg_data_wu32(event->data, 42);
    librg_log("on_connect_request\n");
}

void on_connect_accepted(librg_event_t *event) {
    librg_log("on_connect_accepted\n");
    librg_log("my entity: %u\n", event->entity);
}

void on_connect_refused(librg_event_t *event) {
    librg_log("on_connect_refused\n");
}

void on_entity_create(librg_event_t *event) {
    foo_t foo;
    librg_data_rptr(event->data, &foo, sizeof(foo_t));
    librg_attach_foo(event->ctx, event->entity, &foo);
}

void on_entity_update(librg_event_t *event) {
    librg_data_rf32(event->data);
    // librg_log("sent: %f on upd", librg_data_rf32(event->data));
}


// // client
// void damage_car(librg_entity_t entity) {
//     librg_log("client: damanging the car\n");
//     librg_send(21, librg_lambda(data), { librg_data_wentity(&data, entity); });
// }

// void onvehcielcreate(librg_message_t *msg) {
//     u32 guid = librg_data_ru32(&msg->data);

//     librg_entity_t entity = librg_entity_create_shared(guid, 0);
//     librg_attach_foo(entity, (foo_t) { 123 });

//     librg_log("server created vehicle %lu\n", entity.id);

//     damage_car(entity);
// }

// void on_damage_finished(librg_message_t *msg) {
//     u32 guid = librg_data_ru32(&msg->data);
//     librg_entity_t entity = librg_entity_get(guid);

//     foo_t *foo = librg_fetch_foo(entity);

//     ZPL_ASSERT(foo && foo->a == 123);

//     librg_log("damaged car finished\n");
// }


void on_components_register(librg_ctx_t *ctx) {
    librg_component_register(ctx, component_foo, sizeof(foo_t));
}


int main() {
    char *test = "===============      CLIENT      =================\n" \
                 "==                                              ==\n" \
                 "==                 ¯\\_(ツ)_/¯                   ==\n" \
                 "==                                              ==\n" \
                 "==================================================\n";
    librg_log("%s\n\n", test);

    librg_ctx_t original     = {0};
    original.tick_delay      = 1000;
    original.mode            = LIBRG_MODE_CLIENT;
    original.world_size      = zplm_vec3(5000.0f, 5000.0f, 0.f);
    original.max_entities    = 12000;

	#define size 8
    librg_ctx_t ctxs[size];

    for (int i = 0; i < size; ++i) {
        ctxs[i] = original;

        librg_init(&ctxs[i], on_components_register);

        librg_event_add(&ctxs[i], LIBRG_CONNECTION_REQUEST, on_connect_request);
        librg_event_add(&ctxs[i], LIBRG_CONNECTION_ACCEPT, on_connect_accepted);
        librg_event_add(&ctxs[i], LIBRG_CONNECTION_REFUSE, on_connect_refused);

        librg_event_add(&ctxs[i], LIBRG_ENTITY_CREATE, on_entity_create);
        librg_event_add(&ctxs[i], LIBRG_ENTITY_UPDATE, on_entity_update);

        librg_network_start(&ctxs[i], (librg_address_t) { .host = "localhost", .port = 7777 });
    }

    while (true) {
        for (int i = 0; i < size; ++i) {
            librg_tick(&ctxs[i]);
        }

        zpl_sleep_ms(100);
    }

    return 0;
}
