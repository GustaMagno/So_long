# so_long - 42 Lisbon 🎮


A small 2D game designed to improve skills in graphics, window management, and event handling using the **MiniLibX** library.

## 📝 Description
**so_long** is a project at **42 Lisboa** that challenges students to create a simple graphical game. The goal is for the player to collect all items on a map and reach the exit with the minimum number of movements possible.

## 🚀 Key Features
- **Graphic Management:** Using MiniLibX to render sprites and manage windows.
- **Event Handling:** Capturing keyboard inputs (ESC, WASD/Arrows) and window close events.
- **Map Parsing:** Reading and validating `.ber` files to ensure they follow specific rules (walls, starting position, items, exit).
- **Movement Counter:** Real-time display of the number of steps taken in the terminal or on the screen.

## 🛠️ Technologies
- **Language:** C[cite: 3]
- **Graphics Library:** MiniLibX (Linux or MacOS)
- **Concepts:** Memory management, 2D arrays (matrices), Flood Fill algorithm (for path validation).

## 🎮 How to play
1. **Clone the MLX repository:**

   ```bash
   git clone https://github.com/42paris/minilibx-linux.git
   ```
3. Run the Makefile

   ```bash
   make r
