# Простая версия с базовой графикой
read_and_plot_base <- function(filename) {
  # Чтение файла
  lines <- readLines(filename)
  
  # Первая строка - k
  k <- as.numeric(lines[1])
  
  # Чтение данных
  data <- read.table(text = lines[-1], header = FALSE)
  colnames(data) <- c("x", "y")
  
  # Создание графика
  plot(data$x, data$y, 
       type = "b",  # точки и линии
       col = "blue",
       pch = 19,
       xlab = "x",
       ylab = "y / плотность",
       main = paste("График y(x) и плотность χ²(k =", k, ")"))
  

  x_vals <- seq(0, max(data$x, pchisq(0.999, k)), length.out = 1000)
  lines(x_vals, pchisq(x_vals, df = k), 
        col = "red", 
        lwd = 2)
  
  # Легенда
  legend("topright", 
         legend = c("Данные", paste("χ²(k =", k, ")")),
         col = c("blue", "red"),
         lty = c(1, 1),
         pch = c(19, NA))
  
}

# Использование
png("./pics/pchi.png", width = 1920, height = 1080, res = 120)
read_and_plot_base("./txt/pchisq_res.txt")
dev.off()