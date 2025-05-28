# 個人的勉強用メモ


## C++

- [cppreference](https://en.cppreference.com/w/)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [vcpkg](https://github.com/microsoft/vcpkg)
  - [Manifest mode](https://learn.microsoft.com/en-us/vcpkg/concepts/manifest-mode)
  - [vcpkg.json](https://learn.microsoft.com/en-us/vcpkg/reference/vcpkg-json)
- GoogleTest
- sanitizer


### test

```sh
git submodule update --init --recursive
cd vcpkg && ./bootstrap-vcpkg.sh
cd cppreference
cmake -S tests -B build --preset=default
```


## CMake

- [CMake](https://cmake.org/cmake/help/latest/index.html)


## Docker

- [dockerdocs/manual](https://docs.docker.com/manuals/)


## GitLab

- [GitLab Docs](https://docs.gitlab.com/user/get_started/)
  - [Runner](https://docs.gitlab.com/runner/)
  - [CI/CD](https://docs.gitlab.com/topics/build_your_application/)
