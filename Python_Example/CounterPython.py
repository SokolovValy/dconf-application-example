import tkinter as tk
from gi.repository import Gio

# Ключи и схема GSettings 
SCHEMA = "org.example.counter.python"
KEY_WINDOW_WIDTH = "window-width"
KEY_WINDOW_HEIGHT = "window-height"
KEY_WINDOW_X = "window-x"
KEY_WINDOW_Y = "window-y"
KEY_COUNTER_VALUE = "counter-value"

gsettings = Gio.Settings.new(SCHEMA)

def save_settings():
    """Сохранение текущих настроек окна и значение счётчика."""
    global count
    gsettings.set_int(KEY_WINDOW_WIDTH, root.winfo_width())
    gsettings.set_int(KEY_WINDOW_HEIGHT, root.winfo_height())
    gsettings.set_int(KEY_WINDOW_X, root.winfo_x())
    gsettings.set_int(KEY_WINDOW_Y, root.winfo_y())
    gsettings.set_int(KEY_COUNTER_VALUE, count)


def load_settings():
    """Загрузка настройки окна и значение счётчика."""
    global count
    try:
        width = gsettings.get_int(KEY_WINDOW_WIDTH)
        height = gsettings.get_int(KEY_WINDOW_HEIGHT)
        x = gsettings.get_int(KEY_WINDOW_X)
        y = gsettings.get_int(KEY_WINDOW_Y)
        count = gsettings.get_int(KEY_COUNTER_VALUE)
        root.geometry(f"{width}x{height}+{x}+{y}")
    except Exception:
        count = 0 


def increment():
    global count
    count += 1
    label.config(text=str(count))


def reset():
    global count
    count = 0
    label.config(text=str(count))

root = tk.Tk()
root.title("Counter")

# Загрузка настроек
load_settings()

def on_close():
    save_settings()
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_close)

label = tk.Label(root, text=str(count), font=("Arial", 32))
label.pack(pady=20)

button_add = tk.Button(root, text="Increase by 1", command=increment, font=("Arial", 12))
button_add.pack(side=tk.LEFT, padx=10, pady=10)

button_reset = tk.Button(root, text="Reset", command=reset, font=("Arial", 12))
button_reset.pack(side=tk.RIGHT, padx=10, pady=10)

root.mainloop()
