#include <stdio.h>
#include <stdint.h>
#include <gio/gio.h>

int main()
{
    /// Create dbus message
    GVariant *variant = NULL, *value = NULL;
    GVariantBuilder builder;
    g_variant_builder_init(&builder, G_VARIANT_TYPE_ARRAY);
    g_variant_builder_add(&builder, "{sv}", "name", g_variant_new_string("gia luong"));
    g_variant_builder_add(&builder, "{sv}", "birth", g_variant_new_uint32(2000));
    g_variant_builder_add(&builder, "{sv}", "title", g_variant_new_string("software engineer"));
    g_variant_builder_add(&builder, "{sv}", "country", g_variant_new_string("Viet Nam"));
    variant = g_variant_builder_end(&builder);

    printf("dbus message creation: %s\n", g_variant_print(variant, 0));

    /// Extract element of a dbus message
    const char *name, *title, *country;
    uint32_t birth;

    if ((value = g_variant_lookup_value(variant, "name", G_VARIANT_TYPE_STRING)) != NULL)
    {
        name = g_variant_get_string(value, NULL);
        g_variant_unref(value);
    }

    if ((value = g_variant_lookup_value(variant, "birth", G_VARIANT_TYPE_UINT32)) != NULL)
    {
        birth = g_variant_get_uint32(value);
        g_variant_unref(value);
    }

    if ((value = g_variant_lookup_value(variant, "title", G_VARIANT_TYPE_STRING)) != NULL)
    {
        title = g_variant_get_string(value, NULL);
        g_variant_unref(value);
    }

    if ((value = g_variant_lookup_value(variant, "country", G_VARIANT_TYPE_STRING)) != NULL)
    {
        country = g_variant_get_string(value, NULL);
        g_variant_unref(value);
    }

    printf("Dbus message extraction:\n");
    printf("name: %s\n", name);
    printf("birth: %d\n", birth);
    printf("title: %s\n", title);
    printf("country: %s\n", country);

    g_variant_unref(variant);

    return 0;
}