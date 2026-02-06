# Ray3D

Ray3D is a **C++ OpenGL project** developed to explore and implement a real-time **3D rendering and lighting pipeline** from the ground up.  
The project focuses on clean abstraction of OpenGL, modular design, and a strong understanding of graphics fundamentals rather than engine-level tooling.

---

## 🎯 Project Goals

- Understand modern OpenGL rendering workflows
- Build reusable rendering abstractions instead of writing raw OpenGL calls everywhere
- Implement a basic yet extensible lighting pipeline
- Develop a solid 3D math and camera system

---

## ✨ Features

- Shader-based rendering using modern OpenGL
- Custom **Vertex and Fragment shaders** written in GLSL
- Dynamic lighting system with:
  - Point lights
  - Ambient lighting
  - Emissive materials
- First-person camera system with full 3D navigation
- Procedural primitive generation (cubes, pyramids, etc.)
- Correct UV mapping and normal calculation for lighting

---

## 🧱 Architecture & Design

Ray3D encapsulates raw OpenGL calls into reusable C++ abstractions, including:

- **Shader** – shader compilation, linking, and uniform management
- **Texture** – texture loading and binding
- **Mesh** – vertex/index buffer management and draw calls
- **Camera** – view and projection matrix handling

This approach keeps rendering code **clean, readable, and scalable** while maintaining full control over the graphics pipeline.

---

## 📐 Mathematics & Transformations

- Model, View, and Projection matrix pipeline
- Linear algebra operations using **GLM**
- Support for translation, rotation, and scaling in 3D space
- Perspective camera with adjustable parameters

---

## 🛠 Tech Stack

- **Language:** C++
- **Graphics API:** OpenGL
- **Shaders:** GLSL
- **Math Library:** GLM
- **Windowing/Input:** GLFW
  
---

## ▶️ How to Build & Run

1. Clone the repository
2. Ensure OpenGL and required dependencies are installed
3. Build the project using your preferred C++ compiler
4. Run the executable to explore the 3D scene

> Exact build steps may vary based on platform and setup.

---

## 📝 Notes

- This project is intended as a **learning-focused renderer**, not a full engine.
- The emphasis is on understanding graphics fundamentals and clean system design.
- Designed to be extensible for future experiments (shadows, multiple lights, PBR, etc.).

---

## 👤 Author

**Vansh Bansal**  
Game Developer | C++ | OpenGL | Unreal Engine
