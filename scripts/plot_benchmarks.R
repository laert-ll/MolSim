# install.packages("ggplot2")
library(ggplot2)
library(data.table)

start_t = 0
end_t = 5
time_range = end_t - start_t

# Benchmarks
benchmarks <- data.table(
  delta_t = rep(c(0.0100, 0.0050, 0.0010, 0.0005)),
  time = c(0, 0, 0, 0,
           410, 842, 4452, 10733,
           0, 0, 0, 0,
           147, 329, 2079, 4499),
  group = rep(c("Without Optimization", "Distance Threshold", "Parallelization", "Both"), each = 4)
)

benchmarks[, iterations := time_range / delta_t]

# Plot
ggplot(benchmarks, aes(x = iterations, y = time, color = group, group = group)) +
  geom_line(linewidth = 1) + 
  scale_color_discrete(name = "Groups",
                       breaks = c("Without Optimization", "Distance Threshold", "Parallization", "Both")) +
  labs(x = "Iterations", y = "Time (ms)", color = "Groups",
       title = "Effects of optimizing LJCalculator",
       subtitle = "Plotted benchmark results as average values of 5 test runs.
       Used fixed values: start_t = 0, end_t = 5.
       Iterations = (end_t - start_t) / delta_t, variating delta_t") + 
  theme_minimal() + 
  theme(
    plot.title = element_text(hjust = 0.5, face = "bold", size = 18), 
    plot.subtitle = element_text(hjust = 0.5, face = "italic", size = 10),
    legend.position = "right", 
    legend.title = element_blank(),
    legend.text = element_text(size = 12),
    axis.title = element_text(size = 14),
    axis.text = element_text(size = 12),
    panel.grid.minor = element_blank() 
  ) 


