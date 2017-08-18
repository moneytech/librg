#define LIBRG_IMPLEMENTATION
#define LIBRG_DEBUG
#include <librg.h>

enum {
    TYPE_VEHICLE = 242,
};

typedef struct { i32 a; } librg_component(foo);

void on_connect_request(librg_event_t *event) {
    u32 secret = zpl_bs_read_u32(event->data);

    librg_log("user sent number: %u\n", secret);

    if (secret != 42) {
        return librg_event_reject(event);
    }
}
// void on_vehicle_create() {
//     librg_entity_t entity = librg_entity_create();

//     librg_entity_set_type(entity, TYPE_VEHICLE);

//     librg_log("created vehicle with type: %d\n", librg_entity_get_type(entity));
//     // librg_attach_transform(entity);

//     librg_attach_foo(entity, (foo_t) { 42 });

//     librg_send(20, librg_lambda(data), { zpl_bs_write_u32(data, entity.id); });
// }

void on_connect_accepted(librg_event_t *event) {
    librg_log("on_connect_accepted\n");
    // on_vehicle_create();
}

void on_connect_refused(librg_event_t *event) {
    librg_log("on_connect_refused\n");
}


// void oncardamage(librg_message_t *msg) {
//     librg_log("server: damanging the car\n");
//     u32 guid = zpl_bs_read_u32(msg->data);
//     librg_entity_t entity = librg_entity_get(guid);

//     foo_t *foo = librg_fetch_foo(entity);

//     ZPL_ASSERT(foo && foo->a == 42);

//     librg_log("damaged car\n");

//     librg_send(22, librg_lambda(data), { zpl_bs_write_u32(data, entity.id); });
// }

int main() {
    char *test = "===============      SERVER      =================\n" \
                 "==                                              ==\n" \
                 "==                 ¯\\_(ツ)_/¯                   ==\n" \
                 "==                                              ==\n" \
                 "==================================================\n";
    librg_log("%s\n\n", test);

    librg_init((librg_cfg_t) {
        .tick_delay     = 32,
        .mode           = librg_server_ev,
        .world_size     = zplm_vec2(5000.0f, 5000.0f),
        .entity_limit   = 2048,
    });

    librg_event_add(LIBRG_CONNECTION_REQUEST, on_connect_request);
    librg_event_add(LIBRG_CONNECTION_ACCEPT, on_connect_accepted);
    librg_event_add(LIBRG_CONNECTION_REFUSE, on_connect_refused);

    // librg_network_add(21, oncardamage);

    librg_network_start((librg_address_t) { .host = "localhost", .port = 27010 });

    while (true) {
        librg_tick();
        zpl_sleep_ms(1);
    }

    librg_network_stop();
    librg_free();
    return 0;
}
