library(rpart)
library(caTools)
library(e1071)
library(rattle)
library(rpart.plot)
library(RColorBrewer)

#install.packages("rattle", dependencies = TRUE, repos='http://cran.rstudio.com/')

data <- read.csv('201805-capitalbikeshare-tripdata.csv')

# To display number of rows and columns in data
dim(data)

set.seed(123)

my_sample <- sample.split(data, SplitRatio = 0.8)

biker_train <- data[my_sample, c(1,4,6,9)]
biker_test <- data[!my_sample, c(1,4,6,9)]

summary(biker_test)
summary(biker_train)

fit <- rpart(biker_train$Member.type~., data = biker_train, method = "class")

fit

fancyRpartPlot(fit)

rpart.plot(fit)
rpart.plot(fit,type=4,extra=101)

pred <- predict(fit, newdata = biker_test[,-4], type = ("class"))
tab <- table(biker_test[,4], pred)
tab