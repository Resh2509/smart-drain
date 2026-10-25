# =====================================================
# Smart Drainage System
# FastAPI Main Application
# =====================================================

from fastapi import FastAPI
from sqlalchemy.orm import Session

from app.database import engine, SessionLocal, Base
from app.models import SensorPrediction
from app.ml_model import predict_status
from app.schemas import SensorData
from app.alerts import get_alert


# -----------------------------------------------------
# Create database tables
# -----------------------------------------------------

Base.metadata.create_all(bind=engine)


# -----------------------------------------------------
# Create FastAPI application
# -----------------------------------------------------

app = FastAPI(
    title="Smart Drainage Monitoring API",
    description="AI-based drainage blockage detection using XGBoost",
    version="1.0.0"
)


# -----------------------------------------------------
# Root endpoint
# -----------------------------------------------------

@app.get("/")
def root():

    return {
        "message": "Smart Drainage API is running"
    }


# -----------------------------------------------------
# Health check
# -----------------------------------------------------

@app.get("/health")
def health():

    return {
        "status": "healthy"
    }


# -----------------------------------------------------
# GET prediction endpoint
# -----------------------------------------------------

@app.get("/predict")
def predict(
    water_level: float,
    pressure: float,
    flow_rate: float,
    acoustic: float
):

    status = predict_status(
        water_level,
        pressure,
        flow_rate,
        acoustic
    )

    return {
        "water_level": water_level,
        "pressure": pressure,
        "flow_rate": flow_rate,
        "acoustic": acoustic,
        "predicted_status": status
    }


# -----------------------------------------------------
# POST prediction + database storage
# -----------------------------------------------------

@app.post("/api/predict")
def predict_sensor_data(data: SensorData):

    # -----------------------------------------------
    # Run XGBoost prediction
    # -----------------------------------------------

    status = predict_status(
        data.water_level,
        data.pressure,
        data.flow_rate,
        data.acoustic
    )

    alert_info = get_alert(status)

    # -----------------------------------------------
    # Open database session
    # -----------------------------------------------

    db: Session = SessionLocal()

    try:

        # Create database record
        record = SensorPrediction(
            device_id=data.device_id,
            water_level=data.water_level,
            pressure=data.pressure,
            flow_rate=data.flow_rate,
            acoustic=data.acoustic,
            predicted_status=status
        )

        # Save record
        db.add(record)
        db.commit()

        # Refresh to get generated ID/timestamp
        db.refresh(record)

        return {
            "message": "Sensor data stored successfully",

            "id": record.id,

            "sensor_data": {
                "device_id": record.device_id,
                "water_level": record.water_level,
                "pressure": record.pressure,
                "flow_rate": record.flow_rate,
                "acoustic": record.acoustic
            },

            "predicted_status": record.predicted_status,

            "alert": alert_info,

            "created_at": record.created_at
        }

    finally:

        # Close database connection
        db.close()
# -----------------------------------------------------
# Prediction History
# -----------------------------------------------------

@app.get("/api/history")
def get_history():

    db: Session = SessionLocal()

    try:

        records = (
            db.query(SensorPrediction)
            .order_by(SensorPrediction.created_at.desc())
            .all()
        )

        return {
            "count": len(records),
            "history": [
                {
                    "id": record.id,
                    "water_level": record.water_level,
                    "pressure": record.pressure,
                    "flow_rate": record.flow_rate,
                    "acoustic": record.acoustic,
                    "predicted_status": record.predicted_status,
                    "created_at": record.created_at
                }
                for record in records
            ]
        }

    finally:

        db.close()
# -----------------------------------------------------
# Latest Prediction
# -----------------------------------------------------

@app.get("/api/latest")
def get_latest():

    db: Session = SessionLocal()

    try:

        record = (
            db.query(SensorPrediction)
            .order_by(SensorPrediction.created_at.desc())
            .first()
        )

        if record is None:
            return {
                "message": "No sensor data available"
            }

        return {
            "id": record.id,
            "water_level": record.water_level,
            "pressure": record.pressure,
            "flow_rate": record.flow_rate,
            "acoustic": record.acoustic,
            "predicted_status": record.predicted_status,
            "created_at": record.created_at
        }

    finally:

        db.close()