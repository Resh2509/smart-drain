# =====================================================
# AI-Based Smart Drainage Monitoring System
# Single Sensor Reading Prediction
# =====================================================

import os
import joblib
import pandas as pd


# =====================================================
# STEP 1 : Define Project Root Path
# =====================================================

BASE_DIR = os.path.dirname(
    os.path.dirname(
        os.path.dirname(
            os.path.abspath(__file__)
        )
    )
)


# =====================================================
# STEP 2 : Define Model Paths
# =====================================================

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
# STEP 3 : Display Project Information
# =====================================================

print("=" * 60)
print("SMART DRAINAGE - SINGLE SENSOR PREDICTION")
print("=" * 60)

print("\nProject Directory:")
print(BASE_DIR)


# =====================================================
# STEP 4 : Load Trained XGBoost Model
# =====================================================

print("\nLoading trained XGBoost model...")

model = joblib.load(
    MODEL_PATH
)

print("Model loaded successfully.")


# =====================================================
# STEP 5 : Load Label Encoder
# =====================================================

print("\nLoading label encoder...")

encoder = joblib.load(
    ENCODER_PATH
)

print("Label encoder loaded successfully.")


# =====================================================
# STEP 6 : Display Label Mapping
# =====================================================

print("\nLabel Mapping:")

for index, label in enumerate(encoder.classes_):
    print(index, "->", label)


# =====================================================
# STEP 7 : Enter Sensor Values
# =====================================================

# Sample sensor reading from the dataset

water_level = 59.0

pressure = 0.58

flow_rate = 15.0

acoustic = 295.0


# =====================================================
# STEP 8 : Create Input DataFrame
# =====================================================

input_data = pd.DataFrame(
    [[
        water_level,
        pressure,
        flow_rate,
        acoustic
    ]],
    columns=[
        "Water_Level_cm",
        "Pressure_bar",
        "Flow_LPM",
        "Acoustic_Value"
    ]
)


# =====================================================
# STEP 9 : Display Sensor Input
# =====================================================

print("\n" + "=" * 60)
print("SENSOR INPUT")
print("=" * 60)

print(
    "Water Level :",
    water_level,
    "cm"
)

print(
    "Pressure    :",
    pressure,
    "bar"
)

print(
    "Flow Rate   :",
    flow_rate,
    "L/min"
)

print(
    "Acoustic    :",
    acoustic
)


# =====================================================
# STEP 10 : Generate Prediction
# =====================================================

print("\nGenerating prediction...")

prediction = model.predict(
    input_data
)


# =====================================================
# STEP 11 : Convert Numeric Prediction to Status
# =====================================================

predicted_class = int(
    prediction[0]
)

predicted_status = encoder.inverse_transform(
    [predicted_class]
)[0]


# =====================================================
# STEP 12 : Display Prediction Result
# =====================================================

print("\n" + "=" * 60)
print("ML PREDICTION")
print("=" * 60)

print(
    "Numeric Class :",
    predicted_class
)

print(
    "Status        :",
    predicted_status
)

print("=" * 60)


# =====================================================
# STEP 13 : Prediction Completed
# =====================================================

print("\nPrediction completed successfully.")