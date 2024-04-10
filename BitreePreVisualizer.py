import tkinter as tk
from tkinter import Canvas, ttk

class TreeNode:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

def deserialize_preorder(data):
    def helper(queue):
        val = next(queue)
        if val == "#":
            return None
        node = TreeNode(int(val))
        node.left = helper(queue)
        node.right = helper(queue)
        return node

    data = data.split(",")
    queue = iter(data)
    return helper(queue)

def draw_tree(canvas, root, x, y, x_spacing):
    if root:
        canvas.create_oval(x - 10, y - 10, x + 10, y + 10, fill="white")
        canvas.create_text(x, y, text=str(root.val))
        if root.left:
            x_left = x - x_spacing
            y_left = y + 50
            canvas.create_line(x, y + 10, x_left, y_left - 10, arrow=tk.LAST)
            draw_tree(canvas, root.left, x_left, y_left, x_spacing / 2)
        if root.right:
            x_right = x + x_spacing
            y_right = y + 50
            canvas.create_line(x, y + 10, x_right, y_right - 10, arrow=tk.LAST)
            draw_tree(canvas, root.right, x_right, y_right, x_spacing / 2)

def visualize_binary_tree():
    def visualize():
        serialized_tree = input_entry.get()
        root = deserialize_preorder(serialized_tree)
        canvas.delete("all")

        x_start = 600
        y_start = 80
        x_spacing = 300

        draw_tree(canvas, root, x_start, y_start, x_spacing)

    window = tk.Tk()
    window.title("Binary Tree Visualization")

    input_label = ttk.Label(window, text="Enter Preorder Serialization:")
    input_label.pack()

    input_entry = ttk.Entry(window)
    input_entry.pack()

    visualize_button = ttk.Button(window, text="Visualize", command=visualize)
    visualize_button.pack()

    canvas = Canvas(window, width=1200, height=600)
    canvas.pack()

    window.mainloop()

if __name__ == "__main__":
    visualize_binary_tree()
