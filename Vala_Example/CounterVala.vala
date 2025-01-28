using Gtk;
using GLib;

public class CounterApp : Gtk.Application {
    private int counter = 0;
    private Gtk.Label label;

    private GLib.Settings settings;

    public CounterApp() {
        // Инициализация приложения
        Object(application_id: "org.example.counter.vala",
               flags: ApplicationFlags.FLAGS_NONE);

        // Загрузка GSettings
        settings = new GLib.Settings("org.example.counter.vala");

        this.activate.connect(() => {

            var window = new Gtk.ApplicationWindow(this) {
                title = "Counter",
                default_width = settings.get_int("window-width"),
                default_height = settings.get_int("window-height")
            };

            // Установка сохранённого положения окна, если размеры окна ранее сохранялись
            int width = settings.get_int("window-width");
            int height = settings.get_int("window-height");
            if (width > 0 && height > 0) {
                window.set_default_size(width, height);
            }

            // Загрузка значения счётчика
            counter = settings.get_int("counter-value");

            var vbox = new Gtk.Box(Gtk.Orientation.VERTICAL, 10) {
                margin_top = 20,
                margin_bottom = 20,
                margin_start = 20,
                margin_end = 20
            };
            window.set_child(vbox);

            label = new Gtk.Label(counter.to_string());
            label.add_css_class("large-label");
            vbox.append(label);

            var button_box = new Gtk.Box(Gtk.Orientation.HORIZONTAL, 10) {
                homogeneous = true 
            };
            vbox.append(button_box);


            var add_button = new Gtk.Button.with_label("Increase by 1");
            add_button.clicked.connect(() => {
                counter++;
                label.set_text(counter.to_string());
            });
            button_box.append(add_button);

            var reset_button = new Gtk.Button.with_label("Reset");
            reset_button.clicked.connect(() => {
                counter = 0;
                label.set_text(counter.to_string());
            });
            button_box.append(reset_button);

            // Сохранение настроек при закрытии
            window.close_request.connect(() => {
                settings.set_int("window-width", window.default_width);
                settings.set_int("window-height", window.default_height);
                settings.set_int("counter-value", counter);
                return false;
            });

            window.present();
        });
    }

    public static int main(string[] args) {
        var app = new CounterApp();
        return app.run(args);
    }
}
