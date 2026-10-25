# =====================================================
# AI-Based Smart Drainage Monitoring System
# XGBoost Model Evaluation
# =====================================================

import os
import pandas as pd
import joblib

from sklearn.model_selection import train_test_split
from sklearn.metrics import (
    accuracy_score,
    classification_report,
    confusion_matrix
)


# =====================================================
# STEP 1 : Define Paths
# =====================================================

BASE_DIR = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__)
    )
)

DATASET_PATH = os.path.join(
    BASE_DIR,
    "datasets",
    "dataset.csv"
)

MODEL_PATH = os.path.join(
    BASE_DIR,
    "models",
    "blockage_model.pkl"
)

ENCODER_PATH = os.path.join(
    BASE_DIR,
    "models",
    "label_encoder.pkl"
)


# =====================================================
# STEP 2 : Check Required Files
# =====================================================

print("=" * 60)
print("SMART DRAINAGE ML MODEL EVALUATION")
print("=" * 60)

print("\nChecking required files...")

if not os.path.exists(DATASET_PATH):
    print("ERROR: dataset.csv not found!")
    print(DATASET_PATH)
    exit()

if not os.path.exists(MODEL_PATH):
    print("ERROR: blockage_model.pkl not found!")
    print(MODEL_PATH)
    exit()

if not os.path.exists(ENCODER_PATH):
    print("ERROR: label_encoder.pkl not found!")
    print(ENCODER_PATH)
    exit()

print("All required files found.")


# =====================================================
# STEP 3 : Load Dataset
# =====================================================

print("\nLoading dataset...")

data = pd.read_csv(DATASET_PATH)

print("Dataset loaded successfully!")

print("\nDataset Shape:")
print(data.shape)

print("\nDataset Columns:")
print(data.columns.tolist())


# =====================================================
# STEP 4 : Separate Features and Target
# =====================================================

X = data.drop(
    "Status",
    axis=1
)

y = data["Status"]


print("\nInput Features:")
print(X.columns.tolist())

print("\nTarget:")
print("Status")


# =====================================================
# STEP 5 : Load Label Encoder
# =====================================================

print("\nLoading label encoder...")

encoder = joblib.load(
    ENCODER_PATH
)

print("Label encoder loaded successfully.")

print("\nClass Mapping:")

for number, label in enumerate(
    encoder.classes_
):
    print(
        number,
        "->",
        label
    )


# =====================================================
# STEP 6 : Encode Target
# =====================================================

y_encoded = encoder.transform(y)


print("\nTarget encoding completed.")


# =====================================================
# STEP 7 : Split Dataset
# =====================================================

X_train, X_test, y_train, y_test = train_test_split(

    X,

    y_encoded,

    test_size=0.20,

    random_state=42,

    shuffle=True
)


print("\nTraining Samples:")
print(len(X_train))

print("\nTesting Samples:")
print(len(X_test))


# =====================================================
# STEP 8 : Load Trained XGBoost Model
# =====================================================

print("\nLoading trained XGBoost model...")

model = joblib.load(
    MODEL_PATH
)

print("Model loaded successfully!")

print("\nModel Type:")
print(type(model))


# =====================================================
# STEP 9 : Generate Predictions
# =====================================================

print("\nGenerating predictions...")

predictions = model.predict(
    X_test
)

print("Predictions generated successfully.")


# =====================================================
# STEP 10 : Calculate Accuracy
# =====================================================

accuracy = accuracy_score(
    y_test,
    predictions
)


print("\n" + "=" * 60)
print("MODEL ACCURACY")
print("=" * 60)

print(
    "Accuracy :",
    round(
        accuracy * 100,
        2
    ),
    "%"
)


# =====================================================
# STEP 11 : Classification Report
# =====================================================

print("\n" + "=" * 60)
print("CLASSIFICATION REPORT")
print("=" * 60)

report = classification_report(

    y_test,

    predictions,

    target_names=encoder.classes_,

    zero_division=0
)

print(report)


# =====================================================
# STEP 12 : Confusion Matrix
# =====================================================

print("\n" + "=" * 60)
print("CONFUSION MATRIX")
print("=" * 60)

cm = confusion_matrix(
    y_test,
    predictions
)

print(cm)


# =====================================================
# STEP 13 : Convert Predictions Back to Status
# =====================================================

actual_status = encoder.inverse_transform(
    y_test
)

predicted_status = encoder.inverse_transform(
    predictions.astype(int)
)


# =====================================================
# STEP 14 : Create Prediction Results
# =====================================================

results = X_test.copy()

results["Actual_Status"] = actual_status

results["Predicted_Status"] = predicted_status


print("\n" + "=" * 60)
print("SAMPLE PREDICTIONS")
print("=" * 60)

print(
    results.head(20).to_string(
        index=False
    )
)


# =====================================================
# STEP 15 : Create Evaluation Folder
# =====================================================

OUTPUT_DIR = os.path.join(

    BASE_DIR,

    "outputs",

    "evaluation"

)

os.makedirs(
    OUTPUT_DIR,
    exist_ok=True
)


# =====================================================
# STEP 16 : Save Prediction Results
# =====================================================

prediction_file = os.path.join(

    OUTPUT_DIR,

    "prediction_results.csv"

)

results.to_csv(

    prediction_file,

    index=False

)


print(
    "\nPrediction results saved to:"
)

print(
    prediction_file
)


# =====================================================
# STEP 17 : Save Evaluation Report
# =====================================================

report_file = os.path.join(

    OUTPUT_DIR,

    "classification_report.txt"

)

with open(
    report_file,
    "w"
) as file:

    file.write(
        "AI-BASED SMART DRAINAGE MONITORING SYSTEM\n"
    )

    file.write(
        "XGBoost Model Evaluation\n"
    )

    file.write(
        "============================================\n\n"
    )

    file.write(
        f"Dataset Shape: {data.shape}\n"
    )

    file.write(
        f"Training Samples: {len(X_train)}\n"
    )

    file.write(
        f"Testing Samples: {len(X_test)}\n\n"
    )

    file.write(
        f"Accuracy: {accuracy * 100:.2f}%\n\n"
    )

    file.write(
        "Classification Report\n"
    )

    file.write(
        "---------------------\n"
    )

    file.write(
        report
    )

    file.write(
        "\n\nConfusion Matrix\n"
    )

    file.write(
        "----------------\n"
    )

    file.write(
        str(cm)
    )


print(
    "\nEvaluation report saved to:"
)

print(
    report_file
)


# =====================================================
# STEP 18 : Completed
# =====================================================

print("\n" + "=" * 60)
print("EVALUATION COMPLETED SUCCESSFULLY")
print("=" * 60)