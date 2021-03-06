# CPTG Docs
Simple XML-based language created for Competetive Programmers to quickly generate random tests for competitions
<br>


### Table of contents
1. [Document structure](#document-structure)
2. [Variables and constants](#variables-and-constants)
3. [Sequences](#sequences)
4. [Tags and Parameters documentation](#tags-and-parameters-documentation)
    - [**`var`**](#var)
    - [**`const`**](#const)
    - [**`seq`**](#seq)
    - [**`br`**](#br)
5. [Examples](#examples)


<br>

# Document Structure

Every `.cptg` file should **start** with `<test>` tag and **end** with `</test>` tag

<br>

```XML
<test>
    <!-- variables, sequences, etc -->
</test>
```

<br> 

# Variables and constants

`<var/>` <br>
- Variable is used to display various types of randomly generated data.
By default, a variable is a `Number` in the range of `0-9`, but it can be modified with [parameters](#tags-and-parameters-documentation).

<br>

`<const/>` <br>
- Constant is similar to variable, but the only parameter it
supports is `value` which is used to specify their... **value** and unlike variable, constant is **static**


<br> 

# Sequences
`<seq/>`<br>
- Sequence is used to repeat a group of tags without copying and pasting (you can think of it as a loop)
- you can specify different [parameters](#tags-and-parameters-documentation) to make it work differently
- sequences can be nested e.g.
```xml
<test>
    <seq times="3">
        <seq times="2">
            <const value="1"/>
        </seq>
    </seq>
</test>
<!-- Output: 1 1 1 1 1 1 -->
```


<br> 

# Tags and Parameters documentation

<br>

## `<var>`

available parameters
- `type` 
    - default: **`Number`**
    - used to specify the type of data that will be generated 
    - available values: 
        - **`Char`**
        - **`Number`**
        - **`Float`**
        - **`String`**
- `range` 
    - default: 
        - for **`Number`** and **`Float`**:
            - **`0:9`** 
        - for **`String`** and **`Char`**:
            - **`abc`** 
    - used to specify variable generator range
    - available values:
        - for **`Number`** and **`Float`**:
            - **`n1:n2`** (random numbers from n1 to n2)
                - e.g: `<var type="Number" range="-900:900" />` 
                random number in the range of `[-900;900]`
        - for **`String`** and **`Char`**:
            - **`abc`** generates random lowercase Latin alphabet letter
            - **`ABC`** generates random uppercase Latin alphabet letter
            - **`special`** generates random "special character"
                - list of special characters: 
                    - `! @ # $ % ^ & * ( ) - _ + = { } [ ] : ; " ' < > , . ? / | \ ~`
            - **`all`** generates random lowercase Latin alphabet letter, uppercase Latin alphabet letter or random special character
- `length`
    - default: **`3`**
    - only avaliable fo **`String`** and **`Float`**
        - for **`String`** it specifies the number of characters
        - for **`Float`** it specifies the number of places after the decimal point


<br>
<br>

## `<const>`
available parameters
- `value`
    - default: `None`, must be specified
    - specifies **constant** value

<br>
<br>


## `<seq>`
available parameters
- `times`
    - default: **`1`**
    - specifies how many times sequence will repeat

<br>
<br>

## `<br>`
- adds a breakpoint (`\n`)
- nothing else

<br> 
<br>

# Examples

<br> 

*Code*
```XML
<test>
    <!-- just putting <var/> here without any parameters will
    generate a random number from 0 to 9 -->
    <var/> 
</test>
```
*Example Output*
```
2
```
___
<br> 

*Code*
```XML
<test>
    <!-- sequence example  -->
    <seq times="5">
        <var/>
    </seq>
</test>
```
*Example Output*
```
2 3 1 5 6
```
___

*Code*
```XML
<test>
    <seq times="6">
        <seq times="5"> 
            <var/>
        </seq>
        <br/>
    </seq>
</test>
```
*Example Output*
```
2 3 1 5 6
7 9 1 2 3
0 9 8 2 9
2 0 3 1 9
4 0 9 2 8
9 0 2 1 3
```
___


*Code*
```XML
<test>
    <!-- variables can be of different types -->
    <seq times="3">
        <var type="Char" range="abc" />
        <var type="Char" range="ABC" />
        <var type="Char" range="special" />
        <var type="Char" range="all" />
        <var type="String" range="all" length="5" />
        <br/>
    </seq>
</test>
```
*Example Output*
```
a B & # b$%cA
b D ^ $ sdnD@
p L ( w wdaio
```
___

*Code*
```XML
<test>
    <!-- you can also define constants -->
    <const value="5"/>
    <const value="test"/>
    <const value="123"/>
</test>
```
*Example Output*
```
5 test 123
```
___

*Code*
```XML
<test>
    <!-- you can also add breaks -->
    <const value="5"/>
    <const value="test"/>
    <br/>
    <const value="123"/>
</test>
```
*Example Output*
```
5 test 
123
```
___


@ maintained by [github/foealke](#https://github.com/foealke)
