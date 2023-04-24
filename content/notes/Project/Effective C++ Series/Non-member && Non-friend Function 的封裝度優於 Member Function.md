> Non-member function 帶來更佳的封裝度、與 Packaging 彈性。


這邊說的是 Non-member 且(AND) Non-friend function (Pure function) vs. Member Function。(關於 [[Friend Function]] )

物件導向要求，資料(data) 以及操作資料的函式應該盡量綁在一起，不代表物件導向推崇 member function 是比較好的選擇。

物件導向要求資料應該盡可能地被封裝，卻與直觀相反的，non-member function 的封裝性優於  member function。為什麼? 

## 封裝為什麼封裝被推崇? 
> 封裝使得我們在改變事物時，只影響有限的客戶。

- 被封裝的東西變得不可見 -> 越多封裝就越少 client 可以 access -> 對實作方而言，有更大的彈性改變它，因為能 access 它的客戶有限，改變的影響力小。
- 還有另一個優點是: 帶來包裹彈性 (packaging flexibility)，這與 Namespace & header file 相關，後面會提及。

## 如何衡量封裝程度
這個問句可以換句話說，如何量測「有多少 function 可以看到某一塊資料?」。

> 計算能夠存取該資料的函式，越多函式存取則封裝度越低。

對於 Private Member data 而言，能存取它的就是所有的 member function。
Friend function 雖然不是 non-member function，但他和 member function 同樣擁有 access private data 的能力，所以兩者的封裝度是同樣低的。 

## 將有編譯相依的函式放在同一個 Header File
當我們遵守本頁的守則，拆出許多 Utility Function (工具箱) 之後，該考慮將 Function 依照編譯相依性拆分到不同的 Header file，在不同的 Header file 間共用同一個 namespace 即可。

書中以 `WebBrowser` 舉例，Utility Function 可能有 cookie, bookmark, core funcion (幾乎每個客戶都要的 non-member function)，cookie functions 之間有編譯相依性，放在一塊以此類推。

```cpp
// web_browser_core.hpp
namespace WebBrowserStuff {
	// core function
	class WebBrowser;
}

// cookie.hpp
namespace WebBrowserStuff {
	// cookie functions
}

// bookmark.hpp
namespace WebBrowserStuff {
	// bookmark functions
}
```

這也是 STL 的組織方式，當 User 要用 std::list 時不會去 Include 到 `<vector>` 這個 header file。

Namespace 提供一個比較寬鬆的組織方式，即使跨越 header file 仍能隸屬相同的 namespace。

甚至對 Client 而言，擴展 Utility Function 也同樣容易，只要共用 namespace 、在自己的 header file 增加客製化的 utility function 即可 -- 畢竟 Namespace 可以跨 header file! 

這是以 Namespace 組織，優於以 class 組織的另一個好處 : 對 Client 端而言，他們無法改變 Class 的定義式，但 namespace 他們可以自由共用。

## 有著繼承也無法取代的優點

當然，不能改變定義式，繼承是個解決方法。

然而 C++ 的繼承中，Child 是不能取得 Parent 的 Private Data 的。繼承可以擴充 Public 方法，這點跟 non-member && non-friend function 如出一轍，沒有佔上風，卻在 package fexility 上輸了一截。

這種程度的「擴展機能」相較共用 Namespace 能拆分 Header file 依賴度，就打了折扣。