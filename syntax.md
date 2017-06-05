
# Syntax of Cosmos


## Simple Values

```
a = nil             // nil
b = true || false   // bool
c = -1 + 0.333      // int and float
d = 'some string'   // str
```


## Collections

```
a = [0, 1, nil] + []                    // list
b = {-2, true, false} + {/}             // set
c = {'a': a, 'b': b, 'c': nil} + {}     // dict
```

## Functions

Using `return` keyword:
```
f = (x, y) -> {
    return x + y
}
```

Last expressions is return value:
```
f = (x, y) -> {x + y}
```

Or:
```
f = (x, y) -> x + y
```

Function call:
```
a = f(10, 20)
```


## Objects

Setting attribute, instead of modifying initial object, creates new object with
attribute set inside of it, so initial object is unmodified.

```
a = {
    x = 10,
    y = [],
    z = {},
}

x = a.x
a = (a.x = 10)
a = setattr(a, 'x', 10)

b = {
    x = {
        y = {
            z = 10
        }
    }
}

b = b.x = b.x.y = {z = 20}
b = setattr(b, 'x', setattr(b.x, 'y', {z = 20}))
```


## Conditional - if, else, match

If/else:
```
x = 10

a = x % 2 ? true : nil
```

Match:
```
a = ? {x % 2 -> true; _ -> nil}

a = ? {
    x % 2 -> {
        true
    }
    
    _ -> {
        nil
    }
}
```


## Loops - while, for-in

There is no way to explicitly break/continue or return from inside loop.
```
a = 0

a < 10 @ {
    a = a + 1
}
```

Generator:
```
range = (b, e, s) -> {
  ? {
    b < e -> [b, (_) -> range(b + s, e, s)]}
    _ -> [nil, nil]
  }
}

range = (b, e, s) -> ? {
    b < e -> [b, (_) -> range(b + s, e, s)]}
    _ -> [nil, nil]
}

range = (b, e, s) -> b < e ? [b, (_) -> range(b + s, e, s)] : [nil, nil]
```

Manual loop iteration:
```
i, next = range(0, 10, 2)

next != nil @ {
  i, next = g()
}
```

Auto loop iteration - for-in:
```
range(0, 10, 2) -> i @ {
    i
}
```


## List, Set and Dict comprehension

```
a = [range(0, 10, 2) -> i @ i]              # list
b = {range(0, 10, 2) -> i @ i}              # set
c = {range(0, 10, 2) -> i @ [str(i), i]}    # dict
```


## map, filter, reduce

```
items = [range(0, 10, 2) -> i @ i]
items = map(items, (n) -> n / 2)
items = filter(items, (n) -> n % 2)
result = reduce(items, 0, (accu, n) -> accu + n)
```
