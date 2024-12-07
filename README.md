## Quickstart

```sh
# Build everything
$ cmake -S . -B build
$ cmake --build build

# Build only the editor
$ cmake -S . -B build -DBUILD_EDITOR=ON -DBUILD_GAME=OFF
$ cmake --build build

# Build only the game
$ cmake -S . -B build -DBUILD_EDITOR=OFF -DBUILD_GAME=ON
$ cmake --build build
```
