---
title: "Modern C++ noexcept"
date: 2023-05-03 22:24
tags:
- cpp
---

[[為異常安全 (Exception-safe) 而努力是值得的]]
C++11 中新增的 `noexcept` 有如 `const` 一般，是 function signature 的一部分。


固然，在 Effective Modern C++ Item 14 當中提及將 function 標示為 noexcept 所帶來的 object file optimize 益處。仍需要切記，`noexcept` 也是 signature 的一部分，如果只是想要享受優化的好處，而沒有仔細審視 function 是否真的 exception safe，直接將 API 暴露給客戶端，而在日後發現並非 exception safe 而收回 noexcept 保證，這將嚴重影響客戶端的使用。
多數的 function 是 exception natural (中性的)，意即，不主動拋出 exception，但 exception 可能從此 func 所  invoke 的 function 中被拋出來。這就表示此 function 非 exception safe


