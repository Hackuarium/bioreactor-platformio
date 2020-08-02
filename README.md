

Using VSCode:

* Install extension `PlatformIO IDE`

Take care that `C/C++ intellisense` and `C/C++ Clang Command Adapter
` are not installed as this plugin already includes them.

## Autoformat cpp files

In vscode settings change the parameter `C_Cpp: Clang_format_style` and set as value: `{BasedOnStyle: 'Chromium'}`

This will format the code like:

```cpp
void test() {}

void test2() {
  int a = 1;
  for (int b = 0; b < 10; b++) {
    a += b;
  }
}
```