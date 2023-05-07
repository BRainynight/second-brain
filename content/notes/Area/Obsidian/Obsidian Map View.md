---
title: "Obsidian Map View"
date: 2023-05-01 16:32
tags:
- obsidian
locations: 
---
[Github: Obsidian Map View](https://github.com/esm7/obsidian-map-view)

## 紀錄

### 導入已記錄在 Map 的地點
1. 開啟命令面板 ->  "Map View: add inline geolocation link"，文字 `[](geo:)` 會被插入。
2. 在中括號中輸入地點，像是: `[台北101]`，會跳出下拉選單，點選之後經緯度位置會自動填在 `(geo:)` 當中。

### 從 Command 上新增地點

1. 開啟命令面板 ->"Map View: New geolocation note"。
2. 跳出一個 Dialog，貼上連結、或是 Search 地點都可以。
	- 網址連結分析的規則: [URL parsing rules](https://github.com/esm7/obsidian-map-view#url-parsing-rules)
	- Search 地點會受到選擇哪一個地點資訊提供者所影響: [configured geocoding provider](https://github.com/esm7/obsidian-map-view#changing-a-geocoding-provider) 

### 從既有的筆記新增地點
### Inline geolocation link
如前面「從 Command 新增地點」，在文章中以 `[](geo:)` 標示地點。

### 以 Metadata 標註本文是一個地點

1. 開啟命令面板 ->"Add geolocation (front matter) to current note"。


## Changing a Geocoding Provider
1. 去 Google 申請 Googla Map API
2. 在 Obsidian Map View 的設定當中把 Provider 改成 Google，貼上 API Key.
https://github.com/esm7/obsidian-map-view#changing-a-geocoding-provider


Google API 可以設權限 Query 哪些內容，其中 [Places API](https://developers.google.com/maps/documentation/places/web-service/cloud-setup) 可以讓我們在 Command Line 直接搜尋 Google 地點。花費會比較高，但如果是作為筆記軟體，應該會是在 Google 的免費額度 200美金之內。

## 把 Map Source 切換成 Google 
參考 : https://github.com/esm7/obsidian-map-view/issues/51
在 Map source 中新增一個 Google Map 選項，Url: `https://mts1.google.com/vt/lyrs=m@186112443&hl=x-local&src=app&x={x}&y={y}&z={z}&s=Galile`
