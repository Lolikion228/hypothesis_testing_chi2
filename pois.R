z <- as.numeric(readLines("./pois_res.txt"))
lambda <- z[1]
x <- z[2:length(z)]
h <- hist(x, xlim=c(0,40), freq=0)
x <- h$breaks
lines(x, dpois(x,lambda), col='red', lw=3)
