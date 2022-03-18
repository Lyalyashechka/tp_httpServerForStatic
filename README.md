# tp_httpServerForStatic

Test 
```
My server
docker build -t highload https://github.com/Lyalyashechka/tp_httpServerForStatic.git -f Dockerfile
docker run -p 80:80 -t highload
ab -n 10000 -c 10 127.0.0.1:40000/httptest/wikipedia_russia.html

Concurrency Level:      10
Time taken for tests:   23.310 seconds
Complete requests:      10000
Failed requests:        0
Total transferred:      9549819975 bytes
HTML transferred:       9548240000 bytes
Requests per second:    429.01 [#/sec] (mean)
Time per request:       23.310 [ms] (mean)
Time per request:       2.331 [ms] (mean, across all concurrent requests)
Transfer rate:          400093.68 [Kbytes/sec] received

```
``` 
Nginx 
docker build -t highloadnginx https://github.com/Lyalyashechka/tp_httpServerForStatic.git -f nginx.Dockerfile
docker run -p 40001:80 -t highloadnginx
ab -n 10000 -c 10 127.0.0.1:40001/httptest/wikipedia_russia.html

Concurrency Level:      10
Time taken for tests:   6.248 seconds
Complete requests:      10000
Failed requests:        0
Total transferred:      9550620000 bytes
HTML transferred:       9548240000 bytes
Requests per second:    1600.46 [#/sec] (mean)
Time per request:       6.248 [ms] (mean)
Time per request:       0.625 [ms] (mean, across all concurrent requests)
Transfer rate:          1492711.17 [Kbytes/sec] received
```

