#include <stdio.h>
#include <gio/gio.h>

int main() 
{
    GDBusProxy *proxy;
    GVariant *response;

    proxy = g_dbus_proxy_new_for_bus_sync(G_BUS_TYPE_SESSION, G_DBUS_PROXY_FLAGS_NONE, NULL, 
                                          "com.gialuong.TestServer", "/", 
                                          "com.gialuong.TestInterface", NULL, NULL);

    response = g_dbus_proxy_call_sync(proxy, "org.freedesktop.DBus.Properties.Set", 
                                    g_variant_new(
                                        "(ssv)", 
                                        "com.gialuong.TestInterface", 
                                        "status", 
                                        g_variant_new_uint32(10)
                                    ), 
                                    G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL);
    printf("response set: %s\n", g_variant_print(response, TRUE));
    g_variant_unref(response);

    response = g_dbus_proxy_call_sync(proxy, "org.freedesktop.DBus.Properties.Get",
                                    g_variant_new(
                                        "(ss)", 
                                        "com.gialuong.TestInterface", 
                                        "status"
                                    ),
                                    G_DBUS_CALL_FLAGS_NONE, -1, NULL, NULL);
    printf("response set: %s\n", g_variant_print(response, TRUE));
    g_variant_unref(response);

    g_object_unref(proxy);

    return 0;
}