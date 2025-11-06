package ds.SingleTon_ObjectPool.pattern;

public class Client {
    private static Runnable createTask(final int taskID) {
        return new Runnable() {
            public void run() {
                System.out.println("Task " + taskID + ": start");
                try {
                    Thread.sleep(500);
                } catch (InterruptedException ex) {
                }
                System.out.println("Task " + taskID + ": end");
            }
        };
    }

    public static void main(String args[]) {
        int numTasks = 8;
        ThreadPool threadPool = ThreadPool.getPool();
        for (int i = 0; i < numTasks; i++) {
            threadPool.runTask(createTask(i));
        }
        threadPool.join();
    }
}
