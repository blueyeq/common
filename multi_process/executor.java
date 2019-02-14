private List<Future> submitRequest() {
	ExecutorService executorService = Executors.newFixedThreadPool(10);
	List<Future> futureList = new ArrayList<Future>();
	for(int i = 1; i <= 10; ++i){
		Future future = executorService.submit(getCall(i));
		futureList.add(future);
	}
	return futureList;
}

@Test
public void testException(){
	List<Future> futureList = submitRequest();
	int i = 1;
	for(Future f:futureList){
		System.out.println("i="+i);
		try {
			f.get();
		}catch (InterruptedException e){
			System.out.println(e);
		}catch (ExecutionException e){
			System.out.println(e);
			System.out.println(e.getCause());
			if(e.getCause() instanceof FailureExitException){
				System.out.println("exit ...");
			}
		}
		i++;
	}
}
