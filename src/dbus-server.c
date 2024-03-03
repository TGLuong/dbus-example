#include <gio/gio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

GDBusNodeInfo *introspection_data = NULL;

const gchar introspection_xml[] = 
"<node>"
    "<interface name='com.gialuong.TestInterface'>"
        "<method name='Area'>"
            "<arg type='u' name='width' direction='in'/>"
            "<arg type='u' name='height' direction='in'/>"
            "<arg type='u' name='area' direction='out'/>"
        "</method>"
    "</interface>"
"</node>";

static void
handle_method_call(GDBusConnection *connection, 
                    const gchar *sender, 
                    const gchar *object_path, 
                    const gchar *interface_name, 
                    const gchar *method_name,
                    GVariant *parameters, 
                    GDBusMethodInvocation *invocation, 
                    gpointer user_data)
{
    printf("Call to: -o %s -m %s.%s \n", object_path, interface_name, method_name);

    if (g_strcmp0(method_name, "Area") == 0)
    {
        uint32_t width, height, area;
        g_variant_get(parameters, "(uu)", &width, &height);

        area = width * height;

        g_dbus_method_invocation_return_value(invocation, g_variant_new("(u)", area));
    }
}

static GVariant *
handle_get_property(GDBusConnection *connection,
                    const gchar *sender,
                    const gchar *object_path,
                    const gchar *interface_name,
                    const gchar *property_name,
                    GError **error,
                    gpointer user_data)
{
    return NULL;
}

static gboolean 
handle_set_property(GDBusConnection *connection, 
                    const gchar *sender,
                    const gchar *object_path, 
                    const gchar *interface_name,
                    const gchar *property_name, 
                    GVariant *value,
                    GError **error, 
                    gpointer user_data)
{

}

static const GDBusInterfaceVTable interface_vtable = 
{
    .method_call = handle_method_call,
    .get_property = handle_get_property,
    .set_property = handle_set_property
};

void
bus_acquired_handler(GDBusConnection *connection, 
                        const gchar *name, 
                        gpointer user_data)
{
    printf("bus acquired: %s\n", name);
    guint registration_id;

    registration_id = g_dbus_connection_register_object(connection,
                                                        "/",
                                                        introspection_data->interfaces[0],
                                                        &interface_vtable,
                                                        NULL,
                                                        NULL,
                                                        NULL);

}

void 
name_acquired_handler(GDBusConnection *connection, 
                        const gchar *name, 
                        gpointer user_data)
{

}

void
name_lost_handler(GDBusConnection *connection, 
                    const gchar *name, 
                    gpointer user_data)
{
    
}

int main() 
{
    guint32 watcher_id;
    GMainLoop *loop;

    introspection_data = g_dbus_node_info_new_for_xml(introspection_xml, NULL);
    if (introspection_data == NULL)
    {
        printf("create introspection data form xml error");
        exit(-1);
    }

    watcher_id = g_bus_own_name(G_BUS_TYPE_SESSION, "com.gialuong.TestServer",
                                G_BUS_NAME_OWNER_FLAGS_NONE, bus_acquired_handler, 
                                name_acquired_handler, name_lost_handler, NULL, NULL);
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}