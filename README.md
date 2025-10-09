# Simple Web Browser

A lightweight, modern web browser application built with C++ and wxWidgets, designed for simplicity, extensibility, and efficient browsing. This project demonstrates core browser functionalities such as tab management, bookmarks, session restoration, and settings control, all within a clean and user-friendly interface.

## Features

- **Tabbed Browsing:** Easily open, close, and manage multiple tabs.
- **Bookmark Manager:** Add, remove, and organize bookmarks for quick access to favorite sites.
- **Session Management:** Automatically restore previous browsing sessions for seamless continuity.
- **Settings Manager:** Persistent browser settings with observer pattern for real-time updates.
- **Private Browsing:** Option to open tabs in private mode for enhanced privacy.
- **Reader Mode:** Simplified view for distraction-free reading.
- **Localization Support:** Arabic language support and UTF-8 encoding for internationalization.
- **Modern UI:** Built using wxWidgets with AUI (Advanced User Interface) for docking and flexible layouts.

## Getting Started

### Prerequisites

- **C++14 or higher**
- **wxWidgets 3.2+** (with webview, aui, core, base modules)
- **CMake** (for build configuration)
- **Linux** (tested on Ubuntu 24.04)

### Build Instructions

1. **Clone the repository:**
   ```bash
   git clone https://github.com/Eslamlinux/simple-web-browser.git
   cd simple-web-browser
   ```

2. **Configure the project:**
   ```bash
   cmake -B build
   ```

3. **Build the application:**
   ```bash
   cmake --build build
   ```

4. **Run the browser:**
   ```bash
   ./build/browser
   ```

### Installation

To install system-wide (optional):
```bash
sudo cmake --install build
```

## Project Structure

- `browser_app.*` - Main application entry point and initialization.
- `browser_frame.*` - Main window, tab and menu management.
- `browser_tab.*` - Individual tab logic and webview integration.
- `bookmark_manager.*` - Bookmark CRUD operations.
- `session_manager.*` - Session save/restore logic.
- `settings_manager.*` - Persistent settings and observer notifications.
- `CMakeLists.txt` - Build configuration.

## Contributing

Contributions are welcome! Please fork the repository and submit pull requests for new features, bug fixes, or improvements.

## License

This project is licensed under the MIT License.

## Author

Developed by [Eslamlinux](https://github.com/Eslamlinux).
