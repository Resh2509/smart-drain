# =====================================================
# Smart Drainage System
# XGBoost Model Integration
# =====================================================

import os
import joblib
import pandas as pd


# -----------------------------------------------------
# Project paths
# -----------------------------------------------------

BASE_DIR = os.path.dirname(
    os.path.dirname(
        os.path.abspath(__file__)
    )
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


# -----------------------------------------------------
# Load trained model and encoder
# -----------------------------------------------------

print("Loading XGBoost model...")

model = joblib.load(MODEL_PATH)

print("XGBoost model loaded successfully.")

print("Loading label encoder...")

encoder = joblib.load(ENCODER_PATH)

print("Label encoder loaded successfully.")


# -----------------------------------------------------
# Feature names used during model training
# -----------------------------------------------------

FEATURES = [
    "Water_Level_cm",
    "Pressure_bar",
    "Flow_LPM",
    "Acoustic_Value"
]


# -----------------------------------------------------
# Prediction function
# -----------------------------------------------------

def predict_status(
    water_level: float,
    pressure: float,
    flow_rate: float,
    acoustic: float
):

    input_data = pd.DataFrame(
        [[
            water_level,
            pressure,
            flow_rate,
            acoustic
        ]],
        columns=FEATURES
    )

    # Model prediction
    prediction = model.predict(input_data)

    predicted_class = int(prediction[0])

    # Convert numeric class back to original label
    predicted_status = encoder.inverse_transform(
        [predicted_class]
    )[0]

    return predicted_status