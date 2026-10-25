# =====================================================
# AI-Based Smart Drainage Monitoring System
# XGBoost Model Training
# =====================================================

# Import Required Libraries
import pandas as pd
import joblib

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import (
    accuracy_score,
    classification_report,
    confusion_matrix
)

from xgboost import XGBClassifier

# =====================================================
# STEP 1 : Load the Cleaned Dataset
# =====================================================

print("Loading dataset...")

data = pd.read_csv("datasets/dataset.csv")

print("Dataset Loaded Successfully!\n")

# =====================================================
# STEP 2 : Display Dataset Information
# =====================================================

print(data.head())

print("\nDataset Shape :", data.shape)

# =====================================================
# STEP 3 : Separate Features and Target
# =====================================================

X = data.drop("Status", axis=1)

y = data["Status"]

# =====================================================
# STEP 4 : Convert Labels into Numbers
# =====================================================

encoder = LabelEncoder()

y = encoder.fit_transform(y)

# Save Label Encoder

joblib.dump(encoder, "models/label_encoder.pkl")

print("\nLabel Encoding Completed")

# =====================================================
# STEP 5 : Split Dataset
# =====================================================

X_train, X_test, y_train, y_test = train_test_split(
    X,
    y,
    test_size=0.20,
    random_state=42,
    shuffle=True
)

print("\nTraining Samples :", len(X_train))
print("Testing Samples :", len(X_test))

# =====================================================
# STEP 6 : Create XGBoost Model
# =====================================================

model = XGBClassifier(

    n_estimators=100,

    max_depth=5,

    learning_rate=0.1,

    objective="multi:softmax",

    num_class=len(set(y)),

    random_state=42

)

print("\nXGBoost Model Created")

# =====================================================
# STEP 7 : Train Model
# =====================================================

print("\nTraining Started...")

model.fit(X_train, y_train)

print("Training Completed Successfully!")

# =====================================================
# STEP 8 : Make Predictions
# =====================================================

predictions = model.predict(X_test)

# =====================================================
# STEP 9 : Calculate Accuracy
# =====================================================

accuracy = accuracy_score(y_test, predictions)

print("\nModel Accuracy :", round(accuracy*100,2), "%")

# =====================================================
# STEP 10 : Display Classification Report
# =====================================================

print("\nClassification Report\n")

print(classification_report(y_test, predictions))

# =====================================================
# STEP 11 : Display Confusion Matrix
# =====================================================

cm = confusion_matrix(y_test, predictions)

print("\nConfusion Matrix\n")

print(cm)

# =====================================================
# STEP 12 : Save the Trained Model
# =====================================================

joblib.dump(model, "models/blockage_model.pkl")

print("\nModel Saved Successfully!")

print("\nLocation : models/blockage_model.pkl")

print("\nPhase 5 Completed Successfully")