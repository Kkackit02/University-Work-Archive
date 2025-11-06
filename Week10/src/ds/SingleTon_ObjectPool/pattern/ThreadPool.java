package ds.SingleTon_ObjectPool.pattern;

import java.util.LinkedList;

public class ThreadPool extends ThreadGroup {
    private static ThreadPool threadPool = new ThreadPool();
    private LinkedList<Runnable> taskQueue;
    private boolean isAlive;
    private int threadID;
    private int numThreads = 5;

    private ThreadPool() {
        super("ThreadPool");
        isAlive = true;
        taskQueue = new LinkedList<Runnable>();
        for (int i = 0; i < numThreads; i++) {
            new PooledThread().start();
        }
    }

    public static ThreadPool getPool() {
        return threadPool;
    }

    public synchronized void runTask(Runnable task) {
        if (task != null) {
            taskQueue.add(task);
            notify();
        }
    }

    protected synchronized Runnable getTask() throws InterruptedException {
        while (taskQueue.size() == 0) {
            if (!isAlive) {
                return null;
            }
            wait();
        }
        return (Runnable) taskQueue.removeFirst();
    }

    public void join() {
        synchronized (this) {
            isAlive = false;
            notifyAll();
        }

        Thread[] threads = new Thread[activeCount()];
        int count = enumerate(threads);
        for (int i = 0; i < count; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException ex) {
            }
        }
    }

    private class PooledThread extends Thread {
        public PooledThread() {
            super(ThreadPool.this, "PooledThread-" + (threadID++));
        }

        public void run() {
            while (!isInterrupted()) {
                Runnable task = null;
                try {
                    task = getTask();
                } catch (InterruptedException ex) {
                }

                if (task == null)
                    return;

                try {
                    task.run();
                } catch (Throwable t) {
                    t.printStackTrace();
                }
            }
        }
    }
}
