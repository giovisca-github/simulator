## building and running docker image

1. go to the folder containing the dockerfile
2. run thi lines on a terminal

```
docker build -t simulator .
docker run -it  -v .:/root/simulator -p 10253:10253 -p 10254:10254 --name simulator_container simulator

```