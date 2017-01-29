# Concurrent Execution


## Single-threaded - EventLoop and Tasks

```
thread = import('thread')

loop = thread.EventLoop()

main_task = thread.Task(loop)
    .init((self) -> {
        self = (self.values = [])
        self = (self.senders = [])
        self = (self.result = nil)
        self
    })
    .recv((self, sender, v) -> {
        self = self.values.append(v)
        self = self.senders.append(sender)

        ? {
            len(self.values) == 10 -> {
                self = (self.result = sum(self.values))
                self.senders -> s @ s.send(self, nil)
                self.done()
                self
            }
            _ -> self
        }
    })

threads = [range(10) -> i @ {
    thread.Task(loop)
        .init((self) -> {
            self = (self.value = 1)
            self
        })
        .call((self) -> {
            main_task.send(self, self.value)
        })
        .recv((self, sender, v) -> {
            ? {
                sender == main_task && v == nil -> self.done()
                _ -> self
            }
        })
}]

main_task = main_task.start()
tasks = map(tasks, (t) -> t.start())
result = main_task.join().result
```


## Multi-threaded - EventLoop, Task and Threads

```
thread = import('thread')

loop = thread.EventLoop()

main_task = thread.Task(loop)
    .init((self) -> {
        self = (self.values = [])
        self = (self.senders = [])
        self = (self.result = nil)
        self
    })
    .recv((self, sender, v) -> {
        self = self.values.append(v)
        self = self.senders.append(sender)

        ? {
            len(self.values) == 10 -> {
                self = (self.result = sum(self.values))
                self.senders -> s @ s.send(self, nil)
                self.done()
                self
            }
            _ -> self
        }
    })

threads = [range(10) -> i @ {
    thread.Thread(loop)
        .init((self) -> {
            self = (self.value = 1)
            self
        })
        .call((self) -> {
            main_task.send(self, self.value)
        })
        .recv((self, sender, v) -> {
            ? {
                sender == main_task && v == nil -> self.done()
                _ -> self
            }
        })
}]

main_task = main_task.start()
threads = map(threads, (t) -> t.start())
result = main_task.join().result
```
