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
  

  x_vals <- seq(0, max(data$x, qchisq(0.999, k)), length.out = 1000)
  lines(x_vals, dchisq(x_vals, df = k), 
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
read_and_plot_base("./chisq_res.txt")
