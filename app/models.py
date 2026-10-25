# =====================================================
# Smart Drainage System
# Database Models
# =====================================================

from datetime import datetime

from sqlalchemy import Column, Integer, Float, String, DateTime

from app.database import Base


class SensorPrediction(Base):

    __tablename__ = "sensor_predictions"

    id = Column(Integer, primary_key=True, index=True)

    device_id = Column(String, nullable=False, index=True)

    water_level = Column(Float, nullable=False)

    pressure = Column(Float, nullable=False)

    flow_rate = Column(Float, nullable=False)

    acoustic = Column(Float, nullable=False)

    predicted_status = Column(String, nullable=False)

    created_at = Column(
        DateTime,
        default=datetime.utcnow
    )