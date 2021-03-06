library(e1071) #library required for the naiveBayes function
library(caTools) #library required for the sample.split function
library(caret)
#library(caret)
diabetes <- read.table("diabetes.csv",header = TRUE, sep=",") #reading dataset
diabetes_split <- sample.split(diabetes,SplitRatio = 0.9) #splitting it into training and test data in ratio 0.9
diabetes_train <- subset(diabetes,diabetes_split==TRUE)
diabetes_test <- subset(diabetes,diabetes_split==FALSE)

nb_default <- naiveBayes(Outcome~.,data=diabetes_train) #training the model with training data to predict the class lable taking all other attributes into consideration
nb_predict <- predict(nb_default,newdata=diabetes_test,"raw") #applying the trained model on test data

highestprob=as.factor(colnames(nb_predict)[apply(nb_predict,1,which.max)]) #applying appropriate label based on predicted values
table(highestprob,diabetes_test[,9]) #displaying table of predicted outcome vs actual outcome
table(highestprob)
table(diabetes_test[,9])
png(file="trypie.png")
labs <- c("No diabetes","Diabetes")
pie(table(highestprob),labels = labs)
dev.off()

confusionMatrix(highestprob,as.factor(diabetes_test[,9]))