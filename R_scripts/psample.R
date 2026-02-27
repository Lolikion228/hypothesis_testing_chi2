library(stringr)

# Версия с базовой графикой
plot_ecdf_base <- function(params_file, file_h0, file_h1, step = 0.05) {
  
  z <- as.numeric(strsplit(readLines(params_file), split=" ")[[1]])
  lambda1 <- z[1]
  lambda2 <- z[2]
  main_sample_size <- z[3]
  psample_size <- z[4]

  # Чтение файлов
  pvals_h0 <- scan(file_h0, quiet = TRUE)
  pvals_h1 <- scan(file_h1, quiet = TRUE)
  
  # Создание последовательности x
  x_vals <- seq(0, 1, by = step)
  
  # Вычисление эмпирических функций распределения
  ecdf_h0 <- ecdf(pvals_h0)
  ecdf_h1 <- ecdf(pvals_h1)
  
  y_h0 <- ecdf_h0(x_vals)
  y_h1 <- ecdf_h1(x_vals)
  
  desc = str_interp("lambda1 = ${lambda1}     lambda2 = ${lambda2}
    main_sample_size = ${main_sample_size}    psample_size = ${psample_size}")
  # Создание графика  
  plot(x_vals, y_h0, type = "s", 
       col = "blue", lwd = 2,
       xlim = c(0, 1), ylim = c(0, 1),
       xlab = "alpha", 
       ylab = "Эмпирическая функция распределения F(x)",
       main = paste("Эмпирические функции распределения p-value",desc,sep="\n"))
  
  # Добавление второго графика
  lines(x_vals, y_h1, type = "s", col = "red", lwd = 2)
  
  # Добавление точек
  points(x_vals, y_h0, col = "blue", pch = 19, cex = 0.7)
  points(x_vals, y_h1, col = "red", pch = 19, cex = 0.7)
  
  # Добавление линии y=x
  abline(0, 1, col = "gray50", lty = 2)
  
  # Легенда
  legend("bottomright", 
         legend = c("p-value при H0", "p-value при H1", "y = x"),
         col = c("blue", "red", "gray50"),
         lty = c(1, 1, 2),
         pch = c(19, 19, NA),
         lwd = c(2, 2, 1))
  
  # Вывод статистики
  cat("H0: n =", length(pvals_h0), ", среднее =", mean(pvals_h0), "\n")
  cat("H1: n =", length(pvals_h1), ", среднее =", mean(pvals_h1), "\n")
}

png("./pics/my_plot.png", width = 800, height = 600, res = 120)
plot_ecdf_base("./txt/psample_params.txt", "./txt/psample_h0.txt", "./txt/psample_h1.txt")
dev.off()