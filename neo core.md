- [1. Neo Custom Language Documentation](#1-neo-custom-language-documentation)
  - [1.1. Introduction](#11-introduction)
  - [1.2. Dependencies](#12-dependencies)
  - [1.3. Core.cpp](#13-corecpp)
    - [1.3.1. Global Variables](#131-global-variables)
    - [1.3.2. executeCustomCode Function](#132-executecustomcode-function)
      - [1.3.2.1. Print Statement](#1321-print-statement)
      - [1.3.2.2. Exit Statement](#1322-exit-statement)
      - [1.3.2.3. Variable Assignment](#1323-variable-assignment)
      - [1.3.2.4. Mathematical Operations](#1324-mathematical-operations)
      - [1.3.2.5. Clearing Variables](#1325-clearing-variables)
      - [1.3.2.6. Error Handling](#1326-error-handling)
      - [1.3.2.7. File Inclusion](#1327-file-inclusion)
      - [1.3.2.8. Unrecognized Statements](#1328-unrecognized-statements)
      - [1.3.2.9. creating arrays](#1329-creatinng-arrays)
  - [1.4. Conclusion](#14-conclusion)


# 1. Neo Custom Language Documentation

## 1.1. Introduction
Neo is a custom programming language designed to provide a simplified scripting environment. This documentation aims to describe the core functionality and features of the Neo language.


## 1.2. Dependencies<a name="dependencies"></a>
The Neo language relies on the following libraries:
- `macros.h`: Contains language-specific macros and definitions, as well as project imports

## 1.3. Core.cpp<a name="corecpp"></a>
The `core.cpp` file contains the core functionality of the Neo language.

### 1.3.1. Global Variables<a name="global-variables"></a>
- `vars`: A `std::map` that stores variables and their corresponding values.
- `hasExitValue`: A boolean flag indicating whether an exit value has been set.
- `exit_val`: An integer representing the exit value of the program.
- `<->`: indicates a comment
### 1.3.2. executeCustomCode Function<a name="executecustomcode-function"></a>
The `executeCustomCode` function processes a line of Neo code and performs the corresponding action.

#### 1.3.2.1. Print Statement<a name="print-statement"></a>
The `print` statement is used to display the value of a variable or a string on the console.

Syntax:
```
print <variable_name>
```
or
```
print "<string>"
```

- If the provided `<variable_name>` exists in the `vars` map, its value will be displayed.
- If a string enclosed in either single quotes (`'`) or double quotes (`"`) is provided, the string itself will be displayed.

Example:
```neo
print x
print "Hello, world!"
```

#### 1.3.2.2. Exit Statement<a name="exit-statement"></a>
The `exit` statement is used to set the exit value of the program.

Syntax:
```
exit <exit_value>
```

- `<exit_value>` should be an integer representing the desired exit value of the program.

Example:
```neo
exit 0
```

#### 1.3.2.3. Variable Assignment<a name="variable-assignment"></a>
The `set` statement is used to assign a value to a variable.

Syntax:
```
set <variable_name> <value>
```

- `<variable_name>` should be a valid variable name.
- `<value>` should be an integer representing the value to assign to the variable.

Example:
```neo
set x 42
```

#### 1.3.2.4. Mathematical Operations<a name="mathematical-operations"></a>
Neo supports basic mathematical operations, including addition, subtraction, division, multiplication, and modulo.

- Addition:
  ```
  add <variable_name> <value>
  ```

- Subtraction:
  ````
  dec <variable_name> <value>
  ````

- Division:
  ````
  div <variable_name> <value>
  ````

- Multiplication:
  ````
  mul <variable_name> <value>
  ````

- Modulo:
  ````
  mod <variable_name> <value>
  ````

- `<variable_name>` should be a valid variable name.
- `<value>` should be an integer representing the value to perform the operation with.

Example:
```neo
add x 5
dec y 3
div z 2
mul w 10
mod a 7
```

#### 1.3.2.5. Clearing Variables<a name="clearing-variables"></a>
The `clear` statement is used to remove a variable from the `vars` map.

Syntax:
```
clear <variable_name>
```

- `<variable_name>` should be the name of the variable to be cleared.

Example:
```neo
clear x
```

#### 1.3.2.6. Error Handling<a name="error-handling"></a>
The `err` statement is used to exit the program with an error code.

Syntax:
```
err <error_code>
```

- `<error_code>` should be an integer representing the desired error code.

Example:
```neo
err 1
```

#### 1.3.2.7. File Inclusion<a name="file-inclusion"></a>
The `uses` statement is used to include and execute the code from an external file.

Syntax:
```
uses <file_name>
```

- `<file_name>` should be the name of the file to be included.

Example:
```neo
uses "script.neo"
```

#### 1.3.2.8. Unrecognized Statements<a name="unrecognized-statements"></a>
If a line of code does not match any of the recognized statements, the entire linewill be ignored and not executed.

#### 1.2.2.9. Creating arrays<a name="creating-arrays"></a>

If you have want to make an array, do the following

```neo
arr array_name array_data(separated by ",", and no "[...]")
```

they cannot be modified, and when printed, it will print all of the items at once

## 1.4. Conclusion
This documentation provides an overview of the Neo custom language, including its core functionality and supported statements. It serves as a reference guide for developers using the Neo language for scripting purposes.