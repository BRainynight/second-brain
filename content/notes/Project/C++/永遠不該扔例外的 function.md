---
title: 永遠不該扔例外的 function
date: 2024-01-14 21:35
tags:
  - cpp
---
The following types of functions should never throw: destructors (see the section Failing Destructor in Chapter 5), swap functions, move operations, and default constructors.