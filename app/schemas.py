# =====================================================
# Smart Drainage System
# Pydantic Schemas
# =====================================================

from pydantic import BaseModel, Field


class SensorData(BaseModel):

    device_id: str = Field(
        ...,
        description="Unique ESP32 device ID"
    )

    water_level: float = Field(
        ...,
        description="Water level in cm"
    )

    pressure: float = Field(
        ...,
        description="Pressure in bar"
    )

    flow_rate: float = Field(
        ...,
        description="Flow rate in L/min"
    )

    acoustic: float = Field(
        ...,
        description="Acoustic sensor value"
    )