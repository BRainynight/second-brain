# Asyncio 

在 [Asyncio](https://brainynight.github.io/posts/2022-10-23-python-asyncio) 這篇簡介的文章中，有一個簡單的例子如下。本文將針對此例仔細探討。

```python
import asyncio

async def single_process(cmd):
    proc = await asyncio.create_subprocess_shell(
        cmd,
        stdout=asyncio.subprocess.PIPE,
        stderr=asyncio.subprocess.PIPE)
    try:
        await asyncio.wait_for(proc.communicate(), timeout=2)
        print(cmd, "complete")
    except asyncio.TimeoutError:
        print(cmd, "timeout")
        
async def run_all(cmds):
    lt = []
    for cmd in cmds:
        lt.append(single_process(cmd))
    await asyncio.gather(*lt)

if __name__ == "__main__":
    cmds = [
        "sleep 1 && echo hello",
        "sleep 1.5",
        "echo world",
        "sleep 500",        
    ]
    asyncio.run(run_all(cmds))
```

## Asyncio 

main page: https://docs.python.org/zh-tw/3/library/asyncio.html

接下來只會介紹 main page 當中高階 API 的部分內容。

- [`asyncio.Runner`](https://docs.python.org/zh-tw/3/library/asyncio-runner.html): 是一個 context manager (使用 `with` 語句)，使我們不用管資源關閉或釋放的問題。
- [協程與任務 (coroutines and tasks)](https://docs.python.org/zh-tw/3/library/asyncio-task.html): 這兩者是 high level API 使用者主要會使用到的類別，建議可詳讀。
- [Debug mode](https://docs.python.org/zh-tw/3/library/asyncio-dev.html)
- [Synchronization Primitives](https://docs.python.org/zh-tw/3/library/asyncio-sync.html): asyncio 提供了一些和 threading 模組相似的物件，像是 Lock, Semaphore。不過要注意，asyncio 模組的內容大多都是 non-thread-safe 的。
- [High Level API Index](https://docs.python.org/zh-tw/3/library/asyncio-api-index.html)




## Coroutine

官對"Coroutine" 這個詞彙的說明，我不打算仔細解釋。

在官方文件中，coroutine 很反覆的被提及，有時指的是 coroutine object ，有時是 coroutine function。

- coroutine function: 被以 `async def` 宣告的 function
- coroutine object: 呼叫 coroutine function 時所回傳的物件。

詳見 [PEP 492](https://peps.python.org/pep-0492/)。

> 協程 coroutine[¶](https://docs.python.org/3/glossary.html#term-coroutine)
>
> Coroutines are a more generalized form of subroutines. Subroutines are entered at one point and exited at another point. Coroutines can be entered, exited, and resumed at many different points. They can be implemented with the [`async def`](https://docs.python.org/3/reference/compound_stmts.html#async-def) statement. See also [**PEP 492**](https://peps.python.org/pep-0492/).
>
> 協程函數 coroutine function
>
> A function which returns a [coroutine](https://docs.python.org/3/glossary.html#term-coroutine) object. A coroutine function may be defined with the [`async def`](https://docs.python.org/3/reference/compound_stmts.html#async-def) statement, and may contain [`await`](https://docs.python.org/3/reference/expressions.html#await), [`async for`](https://docs.python.org/3/reference/compound_stmts.html#async-for), and [`async with`](https://docs.python.org/3/reference/compound_stmts.html#async-with) keywords. These were introduced by [**PEP 492**](https://peps.python.org/pep-0492/).



一個協程通常透過協程函數取得，如下例 `cfunc` function ，會回傳一個 coroutine object。

```python
import asyncio

async def cfunc():
    print('hello')
    await asyncio.sleep(1)
    print('world')
```

何以得知? 如果使用 ipython 這類的互動 console，直接看 `cfunc()` 物件是什麼東西，會看到這樣的內容:

```python
>>> cfunc()
<coroutine object cfunc at 0x7fe9094b2650>
>>> type(cfunc())
<class 'coroutine'>
```

這表示，此 function 回傳的內容會是一個 coroutine object! 要注意，coroutine object 必須使用一些支援異步執行的函式/語法來正確的運行，例如 `asyncio.run`， `cfunc()` 實質上的功能，就只是回傳一個 coroutine object 而已。

## Awaitable object 

指的是可以用在 `await` expression 的物件，主要的三種 awaitable object 是 coroutines, Tasks, 和 Futures，另外就是擁有 `__await__()` 方法的物件。`await` 只能被使用在 coroutine function 內。三種 type 當中，Future 屬於比較底層的 API，將不說明。

### coroutine object

前例的 `asyncio.sleep(1)` ，本質上也是透過一個 coroutine function 取得 coroutine object，因此必須以關鍵字  `await` 接住這個 coroutine object。

若 coroutine function 內還會呼叫另一個 coroutine function，被呼叫的 coroutine function 前必須加 `await`，因為它回傳的是個 coroutine object。

```python
import asyncio
import time

async def say_after(delay, what):
    await asyncio.sleep(delay)
    print(what)

async def main():
    print(f"started at {time.strftime('%X')}")
    # needs to add `await` when call a coroutine function, but not directly execute.
    await say_after(1, 'hello') 
    await say_after(2, 'world')
    print(f"finished at {time.strftime('%X')}")

# The method for directly execute is asyncio.run
asyncio.run(main())
```

-  `asyncio.run` 才會真正執行被給予的 coroutine object

### asyncio.Task

`create_task` 回傳一個 `asyncio.Task` 物件，我們得以提前創造 task，等到需要想要執行這個 task 的地方，再以 `await` 呼叫。

同樣的，這裡的「執行」並不是真的「跑」下去，比較像是標示「我想再這裡執行這個 function」。真正的執行依然是交給 `run`。


```python
async def main():
    task1 = asyncio.create_task(say_after(1, 'hello'))
    task2 = asyncio.create_task(say_after(2, 'world'))
    
    print(f"started at {time.strftime('%X')}")
    # Wait until both tasks are completed (should take around 2 seconds.)
    await task1
    await task2
    print(f"finished at {time.strftime('%X')}")
asyncio.run(main())
```

[`TaskGroup`](https://docs.python.org/3/library/asyncio-task.html#asyncio.TaskGroup) 是另外一種創建 task 並執行的方法，可以不用寫 `await` (隱性的在 `with` 結束時呼叫 await 把 tasks call 一遍)，不過這個 API 只在 Python3.11 起提供，就不多提。



## asyncio.gather

```python
asyncio.gather(*aws, return_exceptions=False)
```

- 接收多個 awaitable 物件，如果 awaitable 物件當中有 coroutine，gather 會把它當作 Task 調度 (scheduled as a `Task`)。
- 回傳值: 當所有的 awaitable object 都完成任務後，`asyncio.gather` 會把這些任務的回傳值放在一個 list 裡面回傳結果。結果的順序與放進 `gather` 的順序相同。
- `return_exception` 
    - 預設是 false，當任務執行中發生 exception，會及時 raise exception，並取消 gather (剩下的任務將不會跑到)
    - 若為 true，則不會 raise exception，而是將 exception 的內容 (?) 當作執行成功的結果，一起在 `gather` 的回傳清單中。

## asyncio.wait

```python
asyncio.wait(aws, *, timeout=None, return_when=ALL_COMPLETED)
```

- 接收一個 list，內含多個 awaitable 物件。
- 程式會停在這裡執行同時所有的任務



## Subproccess

https://docs.python.org/zh-tw/3/library/asyncio-subprocess.html







## A

`asyncio.create_subprocess_shell` 是一個 coroutine function，回傳的是 `asyncio.subprocess.Process` 物件。[doc](https://docs.python.org/zh-tw/3/library/asyncio-subprocess.html#asyncio.create_subprocess_shell) 







