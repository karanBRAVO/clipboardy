# clipboardy

A cross-platform clipboard sync tool.

## Architecture

![clipboardy excalidraw](https://github.com/user-attachments/assets/684986ff-a991-46ea-ba98-37c603a5f698)

## Tech Stack

- WebSocket Server: c++ (using `boost` library)
- WebSocket Client: c++ (using `boost` library)
- Clipboard Manager: c++ (using `clip` library)

## Getting Started

- Download `boost` from [official site](https://www.boost.org/releases/latest/) and then unzip it.

- Install `cmake` from [official site](https://cmake.org/download/).

```bash
# for linux (install all at once)
sudo apt install build-essential cmake libboost-all-dev
```

- Build the project from source (make sure `cmake` is installed on your system)

```bash
export BOOST_ROOT=/path/to/boost/dir
mkdir -p build && cd build/
cmake ..
cmake --build .
```

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.
For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
