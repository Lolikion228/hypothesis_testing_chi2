plot_hist_with_chisq_base <- function(data, k, breaks = 30,
                                       main = "Гистограмма и плотность χ²",
                                       xlab = "Значения", 
                                       ylab = "Плотность") {
  
  # Проверка данных
  data <- data[!is.na(data)]
  
  if (length(data) == 0) {
    stop("Нет данных для построения графика")
  }
  
  # Параметры графика
  x_min <- min(0, min(data))
  x_max <- max(data, qchisq(0.999, df = k)) * 1.05
  
  # Гистограмма
  hist_info <- hist(data, 
                    breaks = breaks,
                    freq = FALSE,  # плотность, а не частоты
                    col = "skyblue",
                    border = "black",
                    main = main,
                    xlab = xlab,
                    ylab = ylab,
                    xlim = c(x_min, x_max),
                    ylim = c(0, max(dchisq(seq(0, x_max, length.out = 100), df = k)) * 1.1))
  
  # Добавляем теоретическую плотность χ²
  x_curve <- seq(0, x_max, length.out = 200)
  y_curve <- dchisq(x_curve, df = k)
  lines(x_curve, y_curve, col = "red", lwd = 2)
  
  # Легенда
  legend("topright", 
         legend = c("Эмпирические данные", 
                   paste0("Теоретическая χ²(", k, ")")),
         fill = c("skyblue", NA),
         col = c(NA, "red"),
         lty = c(NA, 1),
         lwd = c(NA, 2),
         border = c("black", NA),
         bg = "white")
  
  # Статистика
  mtext(paste0("n = ", length(data), 
               ", среднее = ", round(mean(data), 2),
               ", медиана = ", round(median(data), 2)),
        side = 1, line = 4, adj = 0.5, cex = 0.9)
  
  # Невидимо возвращаем информацию о гистограмме
  invisible(hist_info)
}

z <- as.numeric(readLines("./txt/chi2.txt"))
k <- z[1]
y <- z[2:length(z)]
y <- na.omit(y)
y <- y
png("./pics/chi2.png", width = 1920, height = 1080, res = 120)
plot_hist_with_chisq_base(y, k)
dev.off()