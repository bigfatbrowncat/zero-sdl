Building
--------

0. After you cloned the repository, load all the submodules:

	```
	git submodules update --init --recursive
	```
	
1. Build all the dependencies with

	```
	./build-deps-<your_os>.sh
	```
	where <em>your_os</em> is "osx" or "windows"
	
2. Go th the project folder and run the build script there

  ```
  cd helloworld
  ./build-<your_os>.sh
  ```
  
  The built binary path is: `helloworld/target-<your_os>/helloworld`