
## 在 Ctor / Dtor 呼叫 virtual function
![[Itm10_TranscationUML.png]]

在這裡，Transcation 的 Constructor 呼叫的會是 `Transcation::logTranscation`。
又，該 function 為 Pure virtural function，若它沒被定義，則當編譯器呼叫時會引發錯誤，而若有.... 就會 Link 到該 base class function。Related: [[Item34 Differentiate between inheritance of interface and inheritance of implementation]]
一個不正式的講法: Base Calss 建構期間，所呼叫的 virtual function 不是 virtual function。  

> [!important] 
> 在 Drived Class Object 執行 Based Class Constructor 期間，物件的型別實際上是 Base Class。

這是根本的原因，由於在 Based Class Constructor 物件是 Base Class，呼叫 Base Class 的 function 也是自然的事。
不只是 virtual function 會被決議(resolve to) 至 Base Class，如果使用 `dynamic_cast` (Runtime type infomation)，也會把物件視為 Base Class! [[少做轉型動作(Minimize casting)]]

相同的問題也存在於 Destructor，在 Destructor 中 Drived Class 的部分會先被消滅，一旦進入 Base Class Destructor ，C++ 就會看待它為一個 Base Class。

## 以傳遞參數給 non-virtual function，取代使用 Virtual function
將 virtual function 從 con/desturctor 中移除! 說來容易，卻不易察覺。Constructor 可能 call 別的 function，而 virtual 可能藏身在其中! 並且，很難確保 Child Class 也會服從這項規定。

替代方案是，使用 non-virtual function，把 Log 以 string 的方式傳給 Base Class 的 non-virtual Log function。
