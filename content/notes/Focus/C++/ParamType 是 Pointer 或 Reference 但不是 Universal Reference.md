---
title: "ParamType 是 Pointer 或 Reference 但不是 Universal Reference"
date: 2023-05-18 23:46
tags:
- cpp
---

Rule: 
1. If expr(argument) has **reference**, ignore the reference part. 
2. T = ArgumentType - declared ParamType.
