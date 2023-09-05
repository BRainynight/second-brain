---
title: "One Definition Rule"
date: 2023-09-05 21:46
tags:
- cpp
---
Source: https://en.cppreference.com/w/cpp/language/definition
Source: https://en.wikipedia.org/wiki/One_Definition_Rule

1. 在一個 translation unit 當中，template, type, function, object 只能一份 definition (一份實作)。
2. 在整個 program 當中，一個 object 或 non-inline function 不能有多於一個 definition
3. Some things, like types, templates, and [extern](https://en.wikipedia.org/wiki/Extern "Extern") inline functions, can be defined in more than one translation unit. For a given entity, each definition must have the same sequence of [tokens](https://en.wikipedia.org/wiki/Lexical_analysis "Lexical analysis"). Non-extern objects and functions in different translation units are different entities, even if their names and types are the same.