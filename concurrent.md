# Concurrent Execution


## Single-threaded - Concurrent Tasks

```
thread = import('thread')

tasks = [
    thread.Task('main')
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
]

tasks += [
    range(10) -> i @ thread.Task(i)
        .init((self) -> {
            self = (self.value = 1)
        })
        .resume((self) -> {
            main_task.send(self, self.value)
        })
        .recv((self, sender, v) -> {
            ? {
                sender.name == 'main' && v == nil -> self.done()
                _ -> self
            }
        })
]

loop = thread.Loop(tasks)
tasks_map = loop.exec()
main_task = tasks_map['main']
result = main_task.result
```


## Multi-threaded - Concurrent Task and Threads

```
thread = import('thread')

tasks = [
    thread.Task('main')
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
]

tasks += [
    range(10) -> i @ thread.Thread(i)
        .init((self) -> {
            self = (self.value = 1)
        })
        .resume((self) -> {
            main_task.send(self, self.value)
        })
        .recv((self, sender, v) -> {
            ? {
                sender.name == 'main' && v == nil -> self.done()
                _ -> self
            }
        })
]

loop = thread.Loop(tasks)
tasks_map = loop.exec()
main_task = tasks_map['main']
result = main_task.result
```
