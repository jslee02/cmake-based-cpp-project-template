### Introduction
The following protocol are mandatory when you develop code for the libraries. It is important that we keep a consistent format through out the entire code base.

====
### Indenting

#### The number of columns to indent per level.
```c++
// Good
int foo()
{
  return 0;
}

// Bad
int bar()
{
    return 0;
}
```

#### Don't indent `namespace` body.
```c++
namespace dart {

// Good
int foo()
{
  return 0;
}

  // Bad
  int bar()
  {
    return 0;
  }

} // namespace dart
```

====
### Code alignment (not left column spaces/tabs)

#### The span for aligning on '=' in assignments is 1.
```C++
int main()
{
  // Good
  int age1    = 20;
  int height1 = 180;
  
  // Bad
  int age2 = 20;
  int height2 = 180;
}
```

#### The span for aligning single-line typedefs is 1.
```C++
// Good
typedef double Scalar;
typedef int    Index;

// Bad
typedef double Scalar;
typedef int Index;
```
