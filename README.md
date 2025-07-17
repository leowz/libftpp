# Libftpp

## 1. Pool and Pool::Object (Resource Pool)

A Resource pool is a design pattern used to reuse a fixed set of resources instead of creating and destroying them repeatedly. It’s useful for optimization and managinh expensive or frequent allocations.

Pool: template class Pool

Pool::Object: Nested Object class inside Pool class

### Moving semantics, Move Constructor and RValue & LValue

Moving semantics are the typical result of a typed system.

Good for temporary data initialisation.   

To my mind, they are tightly coupled with C++'s notion of lvalues and rvalues which, if I'm not mistaken, is purely a C++ concept. A language that doesn't have lvalues, rvalues and their new C++11 friends doesn't need move semantics in the way that C++ implements them.

More generally, though, the concept of moving stuff around rather than copying is just a fundamental concept. Whenever you write a linked list and you "swap elements" by actually just swapping pointers to them, you're doing a "move". Basically.

## LVALUE VS RVALUE

- **Lvalue (Left Value)**: An object that **has a name** and **can be addressed**.
    - You can take its address using `&`.
    - Examples: variables, array elements, function calls that return references.
    - Example:
        
        ```cpp
        int x = 10;   // x is an lvalue
        int& ref = x; // ref is an lvalue reference
        ```
        
- **Rvalue (Right Value)**: A **temporary object** or a value that **does not have a persistent memory address**.
    - Cannot take its address directly.
    - Examples: literals, temporary results of expressions, function returns by value.
    - Example:
        
        ```cpp
        int&& rref = 10; // 10 is an rvalue
        ```
        

### Move Constructor

A **move constructor** enables resource transfer like this:

```cpp
Buffer(Buffer&& other) noexcept
  : size(other.size), data(other.data) { // steal other.size and other.data into new created obj
    other.data = nullptr;  // Null out source
    other.size = 0;        //explicit set the value to 0 since original value stolen
}
```

Now you **steal the resource** instead of copying it.

### 🔁 Compare:

- Copy = duplicate everything
- Move = steal pointer, null out source

## How It Works in Practice

```cpp
Buffer a(1000);              // Construct
Buffer b = std::move(a);     // Move constructor called
```

After the move:

- `b` owns the data
- `a.data == nullptr`

---

## 🔹 When Is Move Constructor Called?

- When using `std::move(obj)`
- When returning a local object by value (with optimizations)
- When storing temporary objects in containers

## 🔣 What is `...` in C++ Templates?

The `...` (three dots) in this context is called the **"pack expansion operator"**.

It is **not** a traditional operator like `+` or `-`, and it's **not a keyword** — it's a **special syntax** introduced in **C++11** that tells the compiler:

"Expand this pattern for each element in a parameter pack.”

### 🧠 Why use `Pool`?

- It avoids frequent `new` and `delete` calls.
- It's faster and more memory-efficient for high-performance apps (e.g., games, servers).
- It teaches you about memory management and ownership patterns.

## Variadic template

templates that takes a variable number of arguments

```cpp
template<typename... Values> class tuple;  // takes zero or more arguments
template<typename First, typename... Rest> class tuple; // takes one or more arguments
```

## 2 Design patterns, gangs of four

### Memento

Save and later restore the internal state of an object.

### 🛠 Responsibilities:

- Base class `Memento` provides `save()` and `load()`.
- A nested `Snapshot` class holds state (via `DataBuffer`).
- Any class that wants to be "saveable" must implement:
    - `_saveToSnapshot(...)` and `_loadFromSnapshot(...)` (private)

### Observer

void subscribe(const TEvent& event, const std::function<void()>& lambda):

### std::function

`std::function` is a **type-erased function wrapper** introduced in C++11.

It can store **any callable object** — like a function pointer, lambda, functor, or bind expression — and allows you to **call it later** through a unified interface.

Think of it like this:

> "std::function<void()> is a variable that holds a function (or lambda), which you can call like a normal function."
> 

## 🔧 Syntax: `std::function<void()>`

Let’s decode that:

```cpp
std::function<void()>
```

This means:

- Callable must **take no parameters** (`()`)
- Callable must **return void** (`void`)
- The callable can be anything: function pointer, lambda, functor, etc.

### Singleton

Ensure a class has **one global instance**, and **only one**.

### StateMachine

Define a finite state machine with transitions and actions.3. IOStream

### Thread:

### 1. **Each thread runs a function (or callable)** in parallel with the main thread and other threads.

- You create a thread with `std::thread`, thread starts on define
- It starts running immediately
- You can `join()` to wait for it, or `detach()` to run it in the background

## 🧵 Multiple Threads Example

```cpp
void work(int id) {
    std::cout << "Thread " << id << " is working\n";
}

int main() {
    std::thread t1(work, 1);
    std::thread t2(work, 2);

    t1.join();  // Wait for t1
    t2.join();  // Wait for t2
}
```

thread-local: 

`thread_local` is a **storage duration specifier** in C++ that tells the compiler:

> “Each thread gets its own separate instance of this variable.”
> 

So if **multiple threads** access a `thread_local` variable, each thread works with its **own copy**, **isolated** from others.

### mutex

In C++, to make **multithreaded code safe**, you use:

- ✅ `std::mutex` — to protect shared data
- ✅ `std::lock_guard` or `std::unique_lock` — to acquire/release mutex automatically (RAII-style)

---

All locks are on upon definition unless deferred lock.

## 🧱 Basic Building Blocks

| Feature | Purpose |
| --- | --- |
| `std::mutex` | A mutual exclusion object |
| `std::lock_guard` | Automatically locks/unlocks a mutex |
| `std::unique_lock` | Like `lock_guard` but more flexible (e.g. deferred locking, timed locking) |

## ✅ Example 1: `std::mutex` with `std::lock_guard`

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;  // Global mutex
int counter = 0;

void increment(const std::string& name) {
    for (int i = 0; i < 10000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Acquires lock and releases automatically
        ++counter;
    }
    std::cout << name << " done.\n";
}

int main() {
    std::thread t1(increment, "Thread 1");
    std::thread t2(increment, "Thread 2");

    t1.join();
    t2.join();

    std::cout << "Final counter: " << counter << std::endl;
    return 0;
}
```

### 🔐 Why `lock_guard`?

- Automatically **releases the lock** when it goes out of scope.
- Prevents bugs like forgetting to unlock.

## ✅ Example 2: `std::unique_lock` (more control)

```cpp
std::unique_lock<std::mutex> lock(mtx); // Can lock/unlock manually later
lock.unlock();   // manually unlock
lock.lock();     // lock again
```

Use this when:

- You need to **lock conditionally**
- You want to **unlock before scope ends**
- You're using `std::condition_variable`

## Thread

### thread safe queue

## 🔍 Why is `mutable` needed for `std::mutex`?

### ⚠️ The Rule

In C++, if a member function is declared `const`, it **cannot modify any non-`mutable` data members**.

## 🧠 In `ThreadSafeQueue`, will you need `mutable`?

Let's look at your class again:

```cpp
private:
    std::deque<TType> queue_;
    mutable std::mutex mutex_;  // Why mutable?
```

In **your current version**, all methods (`push_*`, `pop_*`) are **non-const**, so technically, `mutable` is **not required yet**. but methods like bool empty() const; need mutable mutex

So if you try to lock a `std::mutex` inside a `const` method, **you'll get a compile error** — unless the mutex is marked `mutabl`

### Worker Pool(pattern)

![Screenshot 2025-06-30 at 18.01.22.png](attachment:101780be-29a2-44c1-b3c6-91b67871a58e:Screenshot_2025-06-30_at_18.01.22.png)

## **Worker Pool Pattern: Core Concepts**

### 🔹 1. **Multiple worker threads**

You create `N` threads (often equal to CPU cores).

These threads all run the same loop:

```cpp
while (running) {
    auto job = jobQueue.pop_front();  // Get a job (blocking)
    job();  // Execute the job
}
```

---

### 🔹 2. **Shared job queue**

There is one central queue (`jobQueue`) where jobs are submitted:

```cpp
pool.addJob([] {
    // Do work here
});
```

---

### 🔹 3. **Thread-safe queue**

`ThreadSafeQueue` ensures:

- When multiple threads **push or pop** from the queue, they don’t interfere with each other.
- No race conditions, no data corruption.

> ✅ Ensures safety in concurrent access.
> 

---

### 🔹 4. **Blocking behavior**

If the queue is **empty**:

- `BlockingQueue::pop()` makes the thread **wait (sleep)** instead of looping or crashing.
- When a new job arrives, the queue **wakes one or more sleeping workers**.

> ✅ Ensures efficiency and perpetual readiness.
> 

### conditi variable

In C++, a **`std::condition_variable`** is a synchronization primitive used to **block a thread until a condition is met**, typically in combination with a `std::mutex`.

It’s perfect for scenarios where:

- One thread **waits** for something to happen.
- Another thread **notifies** when that thing happens.

---

## ✅ Real-World Analogy

Imagine a chef (thread) waiting for ingredients to arrive before cooking.

The chef **sleeps** (waits on a condition variable), and when the delivery arrives (condition is true), the delivery person **rings the bell** (`notify_one()`), waking up the chef.

---

## 🔧 Key Components

- `std::condition_variable` — the bell.
- `std::unique_lock<std::mutex>` — lock needed for waiting.
- `wait(lock, predicate)` — wait until `predicate == true`.
- `notify_one()` / `notify_all()` — wake up waiting threads.

---

## 🧪 Minimal Example: Producer–Consumer

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;
bool done = false;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            dataQueue.push(i);
            std::cout << "Produced: " << i << std::endl;
        }
        cv.notify_one(); // Wake up one waiting consumer
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    {
        std::lock_guard<std::mutex> lock(mtx);
        done = true;
    }
    cv.notify_one(); // Wake up consumer so it can exit
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !dataQueue.empty() || done; });

        while (!dataQueue.empty()) {
            int value = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << value << std::endl;
        }

        if (done) break;
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}
```

---

## 🔍 Breakdown of `wait`

```cpp
cv.wait(lock, [] { return condition; });
```

- Atomically:
    1. Unlocks the mutex.
    2. Waits.
    3. When notified, **relocks** the mutex and checks the condition.
    4. Repeats if condition is false (spurious wakeups!).

### 🚨 Always use the `predicate` form to avoid **spurious wakeups**:

```cpp
cv.wait(lock);       // ❌ bad — might wake up without condition being true
cv.wait(lock, cond); // ✅ good — wakes up only when cond is true
```

---

## 🧠 Summary Table

| Function | Purpose |
| --- | --- |
| `wait(lock)` | Wait until notified (unsafe alone) |
| `wait(lock, pred)` | Wait until `pred` is true |
| `notify_one()` | Wake up one waiting thread |
| `notify_all()` | Wake up all waiting threads |

### PersistentWorker

## 🧠 What Exactly Is a PersistentWorker?

It’s like a **self-looping background thread** that:

- Runs a list of tasks over and over (e.g. every frame, every tick).
- Lets users add or remove tasks by name.
- Never stops running — unless explicitly stopped (probably in destructor).
- Is useful for "always-on" processes like:
    - Polling sensors
    - Recalculating game state
    - Animating UI
    - Event dispatching

## Network

## 1. What Does “Trivially Copyable” Mean?

A type is *trivially copyable* if it:

- Can be copied with `memcpy()`
- Has no custom copy constructor/destructor
- Has a simple, contiguous binary layout

Types like `int`, `float`, `double`, `uint64_t` **are trivially copyable**.

But `std::string` is **not** — because:

- It contains a pointer to heap-allocated memory
- It has a non-trivial destructor and copy constructor
- Its data layout is not guaranteed to be linear in memory

## Typical Socket Workflow (Server Side)

### ✅ 1. `socket()`

Create a new socket.

```cpp
int sock = socket(AF_INET, SOCK_STREAM, 0);
```

- `AF_INET`: IPv4
- `SOCK_STREAM`: TCP (for UDP, use `SOCK_DGRAM`)
- Returns a file descriptor (`int`) or -1 on error

---

### ✅ 2. `bind()`

Bind the socket to an address and port.

```cpp
sockaddr_in addr{};
addr.sin_family = AF_INET;
addr.sin_port = htons(4000);               // port 4000
addr.sin_addr.s_addr = INADDR_ANY;         // accept any incoming address

bind(sock, (sockaddr*)&addr, sizeof(addr));
```

- `htons` converts to **network byte order**
- `INADDR_ANY` means “listen on all interfaces”

---

### ✅ 3. `listen()`

Start listening for incoming connections (TCP only).

```cpp
listen(sock, SOMAXCONN);  // SOMAXCONN = max pending connections
```

---

### ✅ 4. `accept()`

Accept a new connection from a client.

```cpp
sockaddr_in clientAddr{};
socklen_t clientLen = sizeof(clientAddr);
int clientSocket = accept(sock, (sockaddr*)&clientAddr, &clientLen);
```

- Returns a new socket descriptor just for this client, accept is blocking by default, use select/poll to detect network usage before accept to make it none blocking.

---

### ✅ 5. `recv()`

Receive data from a socket.

```cpp
char buffer[1024];
ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
```

- Returns number of bytes read
- Returns 0 if connection was closed
- Returns -1 on error

recv could be blocking or none blocking depends on the flag.

---

### ✅ 6. `send()`

Send data through a socket.

```cpp
const char* msg = "Hello client!";
send(clientSocket, msg, strlen(msg), 0)
```

- Returns number of bytes sent
- You may need to loop until everything is sent

---

## ✅ Client Workflow (Short Summary)

```cpp

int sock = socket(AF_INET, SOCK_STREAM, 0);

sockaddr_in serverAddr{};
serverAddr.sin_family = AF_INET;
serverAddr.sin_port = htons(4000);
inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

// then use send() and recv(
```

---


## 🧼 Cleanup

Always close sockets:

```cpp
close(sock);
```

### What is **Perlin Noise**?

**Perlin noise** is a type of **smooth, pseudo-random noise** created by Ken Perlin in 1983.

It's used to generate **natural-looking patterns** like:

- Terrain heightmaps 🌄
- Clouds ☁️
- Water waves 🌊
- Fire 🔥
- Wood, marble, and other textures 🪵

---

### 🧮 What Makes It Special?

Unlike regular random noise (which is *jumpy* and *chaotic*), **Perlin noise is smooth and continuous** — nearby points have similar values.

This makes it perfect for realistic effects in graphics, animation, and procedural generation (e.g., Minecraft world generation).

---

### 🔍 Core Idea

At a high level, Perlin noise:

1. **Divides space into a grid** (e.g., a 2D or 3D grid).
2. Assigns a random **gradient vector** (direction) at each grid point.
3. For any location in the space:
    - It computes a value based on the **influence of nearby gradients**.
    - Then **interpolates smoothly** between them using a fade function.
4. The final result is a **smooth scalar value** (usually in [-1, 1]) that changes gently across space.

---

### 📊 Example: 2D Perlin Noise

```
plaintext
CopyEdit
Imagine a bumpy terrain like this:

   /\     /\
  /  \___/  \___

Perlin noise creates those smooth bumps using math.

```

---

### 💡 Key Properties

| Property | Description |
| --- | --- |
| Smooth | Changes gradually, no sudden jumps |
| Deterministic | Same input → same output |
| Gradient-based | Uses direction vectors instead of pure randomness |
| Scalable | Works in 1D, 2D, 3D, and higher dimensions |

---

### ❓ Why Not Just Use `rand()`?

Because `rand()` gives **independent random values** — they jump all over the place.

Perlin noise gives you **controlled randomness with continuity**, which is ideal for natural patterns.