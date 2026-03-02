f <- function(n){
    z <- as.numeric(readLines(paste("./txt/pois",as.character(n),"_res.txt", sep="")))
    lambda <- z[1]
    x <- z[2:length(z)]
    png(paste("./pics/pois",as.character(n),".png", sep=""), width = 1920, height = 1080, res = 120)
    h <- hist(x, xlim=c(0,40), freq=0)
    x <- h$breaks
    lines(x, dpois(x,lambda), col='red', lw=3)
    dev.off()
}
f(0)
f(1)