#include <libxfce4panel/libxfce4panel.h>

struct hexclock {
	XfcePanelPlugin parent;
	guint timeout_id;
};

struct hexclock_class {
	XfcePanelPluginClass parent;
};

static XfcePanelPluginClass *parent_class;

static void finalize(GObject *object)
{
	struct hexclock *hexclock = (void *)object;

	if (G_LIKELY(hexclock->timeout_id))
		g_source_remove(hexclock->timeout_id);

	(G_OBJECT_CLASS(parent_class)->finalize)(object);
}

static void class_init(void *g_class, void *data)
{
	parent_class = g_type_class_peek_parent(g_class);
	(G_OBJECT_CLASS(g_class))->finalize = finalize;
}

static int update(void *data)
{
	static gchar string[5];
	guint ticks, seconds;
	GDateTime *t;

	t = g_date_time_new_now_local();

	seconds = g_date_time_get_hour(t) * 60; // hours
	seconds = (seconds + g_date_time_get_minute(t)) * 60; // minutes
	seconds = seconds + g_date_time_get_second(t); // seconds
	ticks = (seconds * 512) / 675;

	g_snprintf(string, sizeof(string), "%04X", ticks);
	gtk_button_set_label(GTK_BUTTON(data), string);

	g_date_time_unref(t);

	return 1;
}

static void init(GTypeInstance *object, void *data)
{
	struct hexclock *hexclock = (void *)object;
	GtkWidget *clock;
	GtkStyleContext *context;
	GtkCssProvider *provider;

	clock = gtk_button_new_with_label(NULL);
	gtk_widget_set_name(clock, "hexclock");
	gtk_button_set_relief(GTK_BUTTON(clock), GTK_RELIEF_NONE);

	context = gtk_widget_get_style_context(clock);
	provider = gtk_css_provider_new();
	gtk_css_provider_load_from_data(provider, "#hexclock { padding: 2px 4px; font-family: monospace; }", -1, NULL);
	gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	update(clock);
	hexclock->timeout_id = g_timeout_add_seconds(1, update, clock);

	gtk_container_add(GTK_CONTAINER(object), clock);
	gtk_widget_show(clock);
}

G_MODULE_EXPORT GType xfce_panel_module_init(GTypeModule *type_module, gboolean *make_resident)
{
	static const GTypeInfo type_info = {
		.class_size = sizeof(struct hexclock_class),
		.class_init = class_init,
		.instance_size = sizeof(struct hexclock),
		.instance_init = init,
	};

	if (make_resident) *make_resident = 0;
	return g_type_module_register_type(G_TYPE_MODULE(type_module), XFCE_TYPE_PANEL_PLUGIN, "XfceClockPlugin", &type_info, 0);
}
