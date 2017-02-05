# Concurrent Execution (INCOMPLETE)

## Task Implementation

```
Task = Type + {
    __call__ = (cls, loop, name) -> {
        self = cls + {
            loop = loop
            name = name
            result = nil
            alive = false
            is_done = false
        }
    }

    init = (self) -> {self}                     # default implementation
    resume = (self) -> {self}                   # default implementation
    recv = (self, sender, message) -> {self}    # default implementation
    send = (self, sender, message) -> {self}    # default implementation
}
```


## Loop Implementation

```
Loop = Type + {
    __call__ = (cls) -> {
        self = cls + {
            tasks = []
            tasks_map = {}
        }
    }

    add_tasks = (self, tasks) -> {
        self = (self.tasks += tasks)
        self = (self.tasks_map += {tasks -> task @ task.name: task})
    }

    get_task = (self, task_name) -> {
        task = self.tasks_map[task_name]
    }

    start = (self) -> {
        not_alive_tasks = filter(self.tasks, (t) -> !t.alive)
        alive_tasks = map(not_alive_tasks, (t) -> {t = (t.alive = true)})
        done_tasks = 
        done_tasks_n = 0

        done_tasks < len(alive_tasks) @ {
            ? {
                task.is_done -> task
                _ -> task
            }

            task.resume()
        }

        self
    }

    recv = (self, sender, receiver, message) -> {
        # ?
        receiver.recv(sender, message)
        self
    }

    send = (self, sender, recevier, message) -> {
        # ?
        sender.send(recevier, message)
        self
    }
}

loop = Loop()
tasks = [Task(loop, 'main')] # list of Task/Thread objects
loop = loop.add_tasks(tasks)
loop = loop.start()
main_task = loop.get_task('main')
result = main_task.result
```


## Single-threaded - Concurrent Tasks

```
thread = import('thread')

loop = thread.Loop()

tasks = [
    thread.Task(loop, 'main')
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
            # ?
            # main_task.send(self, self.value)
        })
        .recv((self, sender, v) -> {
            ? {
                sender.name == 'main' && v == nil -> self.done()
                _ -> self
            }
        })
]

result = loop.start().find_task('main').result
```


## Multi-threaded - Concurrent Task and Threads

```

```
