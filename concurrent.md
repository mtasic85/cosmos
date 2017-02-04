# Concurrent Execution


## Single-threaded - Concurrent Tasks

```
thread = import('thread')

main_task = thread.Task()
    .init((self) -> {
        self = (self.values = [])
        self = (self.senders = [])
        self = (self.result = nil)
    })
    .recv((self, sender, v) -> {
        self = (self.values = self.values.append(v))
        self = (self.senders = self.senders.append(sender))

        ? {
            len(self.values) == 10 -> {
                self = (self.result = sum(self.values))
                self.senders -> s @ s.send(self, nil)
                self = self.done()
            }
            _ -> self
        }
    })

tasks = [range(10) -> i @ {
    thread.Task()
        .init((self) -> {
            self = (self.value = 1)
        })
        .resume((self) -> {
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


## Multi-threaded - Concurrent Task and Threads

```
thread = import('thread')

main_task = thread.Task()
    .init((self) -> {
        self = (self.values = [])
        self = (self.senders = [])
        self = (self.result = nil)
    })
    .recv((self, sender, v) -> {
        self = (self.values = self.values.append(v))
        self = (self.senders = self.senders.append(sender))

        ? {
            len(self.values) == 10 -> {
                self = (self.result = sum(self.values))
                self.senders -> s @ s.send(self, nil)
                self = self.done()
            }
            _ -> self
        }
    })

threads = [range(10) -> i @ {
    thread.Thread()
        .init((self) -> {
            self = (self.value = 1)
        })
        .resume((self) -> {
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


## Multi-threaded - Concurrent Task and Tasks-in-Threads

```
thread = import('thread')

main_task = thread.Task()
    .init((self) -> {
        self = (self.values = [])
        self = (self.senders = [])
        self = (self.result = nil)
    })
    .recv((self, sender, v) -> {
        self = (self.values = self.values.append(v))
        self = (self.senders = self.senders.append(sender))

        ? {
            len(self.values) == 10 -> {
                self = (self.result = sum(self.values))
                self.senders -> s @ s.send(self, nil)
                self = self.done()
            }
            _ -> self
        }
    })

threads = [range(10) -> i @ {
    thread.Thread()
        .init((self) -> {
            task = thread.Task()
                .init((self) -> {
                    self = (self.value = 1)
                })
                .resume((self) -> {
                    main_task.send(self, self.value)
                    self
                })
                .recv((self, sender, v) -> {
                    ? {
                        sender == main_task && v == nil -> self.done()
                        _ -> self
                    }
                })

            self = (self.task = task)
        })
        .resume((self) -> {
            self = (self.task = self.task.start())
        })
        .recv((self, sender, v) -> {
            self = (self.task = self.task.send(sender, v))

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
