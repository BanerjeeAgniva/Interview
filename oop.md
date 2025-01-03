# Object-Oriented Programming Concepts

## Key Features of OOP

The Object-Oriented Programming (OOP) paradigm includes the following four features:

1. **Inheritance**
2. **Encapsulation**
3. **Polymorphism**
4. **Data Abstraction**

---

## Pure Object-Oriented Language

A programming language is considered pure object-oriented when it treats everything as an object. The requirements for a pure object-oriented language include:

- Encapsulation
- Inheritance
- Polymorphism
- Abstraction
- All predefined types are objects
- All user-defined types are objects
- All operations on objects must be performed through methods exposed by the objects

### Why is Java Not Purely Object-Oriented?
Java is not a pure object-oriented programming language because it includes primitive data types (e.g., `int`, `float`, `char`, `boolean`) that are not objects. These primitives are provided for performance optimization.

### Example of Pure Object-Oriented Language: Ruby
```ruby
5.times { puts "Hello" }  # 5 is an object, and `times` is a method.
puts 7.class              # Outputs "Integer", showing 7 is an object.
```

---

## Access Specifiers

Access specifiers in OOP define the accessibility of classes, methods, and other members. Common access specifiers include:

- **Public**: Accessible from anywhere in the program.
- **Private**: Accessible only within the same class.
- **Protected**: Accessible within the same package and by subclasses.
- **Default (Java)**: Allows access within the same package.

Access specifiers are crucial for achieving encapsulation.

---

## Manipulators in OOP

Manipulators are helper functions used to modify or format input/output streams. They work with the insertion (`<<`) and extraction (`>>`) operators without altering variable values.

### Types of Manipulators:

1. **Manipulators Without Arguments**
   - `endl`: Inserts a newline character and flushes the output buffer.
   - `ws`: Ignores leading whitespaces in the input.
   - `flush`: Explicitly flushes the output buffer.
   
   **Example:**
   ```cpp
   std::cout << "Hello" << std::endl;  // Outputs "Hello" followed by a newline.
   ```

2. **Manipulators With Arguments**
   - `setw(val)`: Sets the width of the field for the next input/output.
   - `setfill(c)`: Fills unused width with a specified character.
   - `setbase(val)`: Sets the base for integer output (e.g., decimal, octal, or hexadecimal).
   - `setiosflags(flag)`: Sets specific format flags like fixed or scientific.

   **Example:**
   ```cpp
   std::cout << std::setw(10) << std::setfill('*') << 123;  // Outputs "*******123"
   ```

---

## Rules for Creating a Constructor

1. It cannot have a return type.
2. It must have the same name as the class.
3. It cannot be marked as `static`.
4. It cannot be marked as `abstract`.
5. It cannot be overridden.
6. It cannot be `final`.

---

## Differences Between Errors and Exceptions in Java

| **Aspect**                | **Exception**                                     | **Error**                               |
|---------------------------|---------------------------------------------------|-----------------------------------------|
| **Recoverable**           | Yes                                              | No                                      |
| **Type**                  | Checked and unchecked                            | Always unchecked                        |
| **Occurrence**            | Compile-time (checked) or runtime (unchecked)    | Runtime only                            |
| **Package**               | `java.lang.Exception`                            | `java.lang.Error`                       |
| **Known/Unknown**         | Known to compiler (checked exceptions)           | Unknown to compiler                     |
| **Cause**                 | Application issues (e.g., invalid input)         | Environment/system issues (e.g., OOM)  |
| **Examples**              | Checked: `SQLException`, `IOException`           | `OutOfMemoryError`, `StackOverflowError`|
|                           | Unchecked: `ArrayIndexOutOfBoundsException`      |                                         |

---

## Abstract Class

An abstract class is a class that is declared as `abstract`. It provides a common definition for its subclasses.

### Characteristics:

1. Instantiation is not allowed.
2. Must be inherited.
3. Can have both abstract and non-abstract methods.
4. Must declare at least one abstract method.
5. Declared using the `abstract` keyword.

**Example:**
```java
abstract class Animal {
    public abstract void sound();
    public void sleep() {
        System.out.println("The animal is sleeping.");
    }
}

class Dog extends Animal {
    public void sound() {
        System.out.println("The dog barks.");
    }
}

class Main {
    public static void main(String[] args) {
        Animal dog = new Dog();
        dog.sound();  // Outputs: The dog barks.
        dog.sleep();  // Outputs: The animal is sleeping.
    }
}
```

---

## Constructor Inheritance

A subclass cannot inherit the constructor of its base class. However, a subclass can call the constructor of its base class using the `super()` keyword.

**Example:**
```java
class Animal {
    public Animal(String name) {
        System.out.println("Animal name: " + name);
    }
}

class Dog extends Animal {
    public Dog(String name) {
        super(name);
        System.out.println("Dog name: " + name);
    }
}

class Main {
    public static void main(String[] args) {
        Dog dog = new Dog("Buddy");
    }
}
// Output:
// Animal name: Buddy
// Dog name: Buddy
```

---

## Runtime Polymorphism

**Scenario:** A group of 5 friends has one member who avoids contributions. When a new girl joins the group, he starts spending generously.

This represents **Runtime Polymorphism**, where a method behaves differently based on the object at runtime.

---

## Composition

Composition models a `has-a` relationship by using objects of other classes as instance variables.

### Example:
A `Car` has an `Engine`.

---

## Copy Constructor vs. Assignment Operator

| **Aspect**           | **Copy Constructor**                           | **Assignment Operator**               |
|----------------------|-----------------------------------------------|---------------------------------------|
| **Memory**           | Allocates separate memory for objects         | Shares the same memory block         |
| **Syntax**           | `class_name (const class_name &obj)`          | `obj1 = obj2;`                       |

---

## Composition vs. Inheritance

| **Aspect**               | **Inheritance**                | **Composition**               |
|--------------------------|-------------------------------|--------------------------------|
| **Memory**               | Single object in memory       | Parent holds references       |
| **Relationship**         | `is-a`                        | `has-a`                       |

---

## Constructor Chaining

Constructor chaining invokes multiple constructors in sequence during object initialization.

### Example in Java:
```java
class Example {
    public Example() {
        this("Default");
        System.out.println("Default Constructor");
    }

    public Example(String name) {
        System.out.println("Parameterized Constructor: " + name);
    }
}

class Main {
    public static void main(String[] args) {
        Example obj = new Example();
    }
}
// Output:
// Parameterized Constructor: Default
// Default Constructor
```

---