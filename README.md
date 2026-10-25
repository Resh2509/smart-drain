# SmartDrain: AI-Based Smart Drainage Detection and Automatic Safety System for Urban Flooding

## 🌧️ Project Overview

**SmartDrain** is an AI-powered smart drainage monitoring and control system designed to identify drainage abnormalities, classify blockage severity, monitor water levels and flow conditions, and support early warnings for potential urban flooding.

The system integrates IoT sensors, an ESP32 microcontroller, an XGBoost machine learning model, a FastAPI backend, a monitoring dashboard, and a Unity-based 3D digital twin. These components work together to provide real-time monitoring, data-driven predictions, and automated responses under configured operating conditions.

SmartDrain aims to improve drainage visibility, reduce dependence on manual inspections, and support faster maintenance decisions through intelligent monitoring.

## 🎯 Problem Statement

Urban drainage systems frequently experience blockages caused by accumulated waste, leaves, and sediment. Restricted drainage flow can increase water accumulation and contribute to localized flooding, especially during heavy rainfall.

Traditional inspection methods may not provide continuous monitoring or timely information about changing drainage conditions. SmartDrain addresses these challenges by combining sensor-based monitoring, machine learning, automated control, and digital visualization in one integrated platform.

## 💡 Proposed Solution

SmartDrain collects readings from sensors installed in a physical drainage prototype. An ESP32 processes the sensor inputs and transmits the data to a FastAPI backend.

The backend stores monitoring records and uses a trained XGBoost model to classify drainage conditions based on the selected input features. Results are made available to the monitoring dashboard and Unity digital twin for visualization.

A servo-operated Smart Auto-Vent and a water circulation pump support controlled prototype operation according to the configured control logic.

### Key Objectives

- Monitor drainage flow and water-level changes continuously.
- Identify abnormal operating conditions using sensor readings.
- Classify drainage blockage severity using machine learning.
- Provide timely alerts for detected drainage abnormalities.
- Demonstrate controlled actuator operation in a prototype.
- Visualize drainage conditions through a 3D digital twin.
- Maintain historical monitoring data for analysis and evaluation.

## 🏗️ System Architecture

```text
          PHYSICAL DRAINAGE PROTOTYPE
                       |
        +--------------+--------------+
        |              |              |
    Flow Sensor   Water-Level     Acoustic
                    Sensor        Sensor
        |              |              |
        +--------------+--------------+
                       |
                  BMP280 Sensor
                       |
                       v
                ESP32 DevKit V1
                       |
                  Wi-Fi / HTTP
                       |
                       v
                FastAPI Backend
                       |
          +------------+------------+
          |                         |
          v                         v
    XGBoost Model              SQLite Database
          |                         |
          v                         v
  Blockage Classification    Historical Records
          |
          v
   Monitoring Dashboard
          |
          v
    Unity 3D Digital Twin
          |
          v
   Configured Control Logic
          |
          v
    ESP32 Actuator Control
          |
          +---- Servo Auto-Vent
          |
          +---- Water Circulation Pump
```

*The diagram represents the intended end-to-end architecture. Individual connections and control flows should match the implementation available in the repository.*

## 🔧 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 DevKit V1 | Microcontroller for sensor acquisition and device communication |
| YF-S201 Flow Sensor | Measures water flow at its installation point |
| JSN-SR04T Ultrasonic Sensor | Measures water-level distance in the prototype |
| Acoustic Sensor | Captures sound and vibration patterns associated with drainage conditions |
| BMP280 Sensor | Measures atmospheric pressure |
| Servo Motor | Operates the prototype's Smart Auto-Vent mechanism |
| 12V DC Mini Submersible Pump | Circulates water through the prototype |
| LM2596 Buck Converter | Steps down DC voltage for compatible components |
| PVC/uPVC Pipes and Fittings | Form the physical drainage network |
| Water Reservoir and Hoses | Support water circulation through the prototype |

*Use the exact sensor and actuator models listed in the actual hardware setup when finalizing the repository documentation.*

## 💻 Software and Technologies

| Technology | Application |
|---|---|
| Python | Backend development and machine learning |
| ESP32 / Arduino-compatible firmware | Sensor acquisition and hardware control |
| FastAPI | Backend API and data communication |
| XGBoost | Drainage blockage classification |
| SQLite | Monitoring data storage |
| HTML and CSS | Dashboard interface |
| JavaScript | Dashboard interactions, if implemented |
| Unity 6 | 3D drainage visualization and digital twin |
| Git and GitHub | Version control and project collaboration |

## 🤖 Machine Learning Model

SmartDrain uses **XGBoost**, a gradient-boosted decision-tree algorithm, to classify drainage conditions using selected sensor features.

The model receives numerical readings from the configured sensor inputs and produces a predicted class representing the drainage condition.

### Classification Categories

The following labels can be used if they match the classes in the trained model:

| Class | Description |
|---|---|
| Normal | Readings indicate normal drainage operation |
| Minor Obstruction | Readings suggest a minor restriction |
| Partial Blockage | Readings suggest a significant flow restriction |
| Critical Blockage | Readings indicate a severe drainage abnormality |

The final class names, feature order, and preprocessing steps must match the actual training dataset and saved model.

### Model Development Workflow

1. Collect sensor readings under controlled prototype conditions.
2. Prepare and validate the dataset.
3. Clean the data and handle missing or invalid readings.
4. Select the input features used for classification.
5. Train the XGBoost classifier.
6. Evaluate the model on data not used during training.
7. Save the trained model and load it in the backend.
8. Generate predictions from incoming sensor data.
9. Display the predicted condition on the dashboard.

### Model Evaluation

Model performance should be evaluated using:

- Accuracy
- Precision
- Recall
- F1-score
- Confusion matrix

Evaluation values should be reported only after testing the trained model on a suitable held-out dataset.

## 🌐 IoT Monitoring and Backend

The ESP32 collects sensor readings and communicates with the backend over Wi-Fi. FastAPI provides the interface for receiving sensor data, processing predictions, and making monitoring information available to other application components.

### Backend Responsibilities

- Receive sensor readings from the ESP32.
- Validate incoming data.
- Process the inputs required by the trained model.
- Generate drainage-condition predictions.
- Store monitoring records in SQLite.
- Provide data to the dashboard and digital twin.
- Support configured actuator commands where implemented.

### Suggested API Structure

The following endpoints are an example of a proposed API structure. Keep only endpoints that exist in the actual codebase.

| Method | Endpoint | Purpose |
|---|---|---|
| POST | `/api/sensor/data` | Submit sensor readings |
| POST | `/api/prediction/` | Request a drainage-condition prediction |
| GET | `/api/system/latest` | Retrieve the latest monitoring data |
| GET | `/api/system/history` | Retrieve historical readings |
| GET | `/api/alerts/` | Retrieve recorded alerts |
| POST | `/api/device/command` | Submit a configured device command |

FastAPI's interactive API documentation is normally available at `/docs` while the backend is running locally.

## 📊 Monitoring Dashboard

The SmartDrain dashboard provides a centralized view of the prototype's operating conditions.

### Intended Dashboard Features

- Live sensor readings.
- Water-flow and water-level information.
- Predicted drainage-condition category.
- Current system status.
- Abnormal-condition alerts.
- Historical monitoring records.
- Actuator status, where available.

The dashboard helps users understand changing drainage conditions without depending entirely on manual inspection.

## 🌐 Unity 3D Digital Twin

The Unity-based digital twin provides a visual representation of the physical drainage prototype.

### Intended Features

- 3D visualization of the main drainage pipe and branch network.
- Representation of drainage chambers and connected structures.
- Visual indication of flow conditions.
- Color-coded representation of predicted blockage severity.
- Display of relevant sensor values and system status.
- Visualization of configured actuator states.
- Updates based on backend data, when the integration is enabled.

The digital twin is intended to connect physical monitoring data with a visual model of the drainage system. The actual update frequency depends on the implemented communication and refresh mechanism.

## ⚙️ Working Methodology

1. **Sensor Acquisition:** Sensors collect water-flow, water-level, acoustic, and atmospheric-pressure readings.
2. **Microcontroller Processing:** The ESP32 reads the sensor signals and prepares the data for transmission.
3. **Data Transmission:** Sensor readings are sent to the FastAPI backend over the configured communication connection.
4. **Data Validation:** The backend checks incoming values and prepares the model inputs.
5. **AI Classification:** The XGBoost model predicts the drainage condition using its trained features.
6. **Data Storage:** Monitoring records and predictions are stored in the database when database integration is enabled.
7. **Dashboard Updates:** The application displays the latest available readings and predictions.
8. **Digital Twin Visualization:** Unity presents the corresponding drainage state using the received data.
9. **Controlled Operation:** Configured control logic can operate the prototype's servo and water circulation pump under defined conditions.

## 🚀 Getting Started

### Prerequisites

Install the software required by the components you intend to run:

- Python 3
- Git
- Visual Studio Code or another Python-compatible IDE
- ESP32-compatible development environment
- Unity 6, if running the digital twin
- Required hardware drivers and libraries

### 1. Clone the Repository

Replace the example URL with the actual repository URL.

```bash
git clone https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git
cd YOUR_REPOSITORY
```

### 2. Create a Python Virtual Environment

```bash
python -m venv venv
```

Activate it on Windows:

```powershell
.\venv\Scripts\Activate.ps1
```

If PowerShell activation is unavailable, use Command Prompt:

```bat
venv\Scripts\activate.bat
```

### 3. Install Dependencies

If the repository contains `requirements.txt`, run:

```bash
pip install -r requirements.txt
```

Otherwise, install the packages specified by the actual backend implementation.

### 4. Start the Backend

Use the entry point defined in your project. For example, if the application object is `app` in `app/main.py`:

```bash
uvicorn app.main:app --reload
```

Open the following address in your browser:

```text
http://127.0.0.1:8000/docs
```

### 5. Connect the ESP32

- Configure the Wi-Fi credentials in the firmware.
- Set the backend address to an address reachable from the ESP32.
- Verify the GPIO assignments against the actual circuit.
- Confirm that the incoming sensor values are valid.
- Test the data connection before enabling automatic actuator control.

When using a physical ESP32, `127.0.0.1` refers to the device making the request. It does not refer to the computer hosting the backend. Use the host computer's reachable local network address or the configured deployment address.

### 6. Run the Dashboard

Follow the instructions for the dashboard framework and entry point present in the repository. Confirm that it can retrieve current readings and predictions from the backend.

### 7. Open the Unity Project

Open the Unity project using a compatible Unity Editor version. Configure the backend address and data update mechanism according to the scripts included in the project.

## 🧪 Testing and Validation

The system should be tested in stages before full integration.

### Hardware Testing

- Verify each sensor independently.
- Compare readings against suitable reference measurements.
- Check the stability of the ESP32 power supply.
- Test actuator movement with the mechanism disconnected from any unsafe load.
- Check pipe joints and water circulation for leaks.

### Backend Testing

- Submit valid sample sensor data.
- Confirm that invalid or missing fields are handled appropriately.
- Verify model loading and prediction output.
- Check that database records are created correctly.
- Test error handling for communication failures.

### Machine Learning Testing

- Confirm that model features match the training configuration.
- Evaluate performance using held-out test data.
- Review the confusion matrix and per-class metrics.
- Test readings from different controlled blockage scenarios.
- Check for incorrect classifications under noisy sensor conditions.

### Integration Testing

- Confirm ESP32-to-backend communication.
- Verify that the dashboard shows the latest available information.
- Confirm that Unity displays the correct system state.
- Test configured control commands and actuator feedback.
- Verify safe behavior when data becomes unavailable.

## 🔒 Safety and Reliability

- Use suitable electrical insulation and protected connections around water.
- Select an enclosure appropriate for the prototype's operating environment.
- Provide suitable power supplies and overcurrent protection for connected hardware.
- Do not power a servo motor directly from an ESP32 GPIO pin.
- Validate incoming readings before using them for automated control.
- Define safe operating limits for actuators.
- Provide a manual override and a safe shutdown procedure.
- Test the prototype under controlled conditions before extended operation.
- Treat machine learning outputs as decision-support information rather than a guarantee of real-world drainage conditions.

## ⚠️ Project Scope and Limitations

- Sensor readings depend on installation, calibration, and operating conditions.
- A flow sensor measures conditions at its installation point and does not independently identify flow in every branch.
- The BMP280 measures atmospheric pressure; it is not a direct water-pressure measurement device.
- Acoustic readings can vary with pipe materials, mounting, pump noise, and environmental conditions.
- Classification performance depends on the quality and coverage of the training data.
- Prototype results may not directly represent full-scale municipal drainage networks.
- Automated actions should be enabled only after the control logic and hardware have been tested.

## 🔮 Future Enhancements

Potential improvements to SmartDrain include:

- Improved sensor calibration and data-quality checks.
- Expanded training datasets covering more drainage conditions.
- Better per-class model evaluation and model retraining workflows.
- Historical trend analysis and maintenance reports.
- More detailed 3D visualization of drainage network conditions.
- Improved device connectivity and recovery from temporary network failures.
- Configurable alert thresholds and maintenance notifications.
- Integration with larger drainage network monitoring platforms.

## 🌍 Expected Impact

SmartDrain aims to support:

- Earlier identification of abnormal drainage conditions.
- More consistent monitoring of drainage prototypes.
- Faster review of possible blockage events.
- Better visibility into sensor readings and predicted conditions.
- More informed maintenance planning.
- Clearer communication of drainage status through a digital twin.

These benefits should be validated through prototype testing and measured results before being reported as achieved performance improvements.

## 📚 References and Documentation

- **ESP32 Documentation:** https://docs.espressif.com/projects/esp-idf/en/stable/esp32/
- **Bosch Sensortec:** https://www.bosch-sensortec.com/
- **XGBoost Documentation:** https://xgboost.readthedocs.io/
- **FastAPI Documentation:** https://fastapi.tiangolo.com/
- **Python Documentation:** https://docs.python.org/3/
- **Unity Documentation:** https://docs.unity.com/
- **scikit-learn Documentation:** https://scikit-learn.org/stable/

Refer to the manufacturer documentation for the exact sensor and actuator models used in the physical prototype.

## 👥 Contributors

Add the names and GitHub profiles of the project contributors here.

## 📄 License

Add the license selected for this repository. If you intend to publish the project for reuse, choose an appropriate open-source license and include its license file.

## 🏁 Conclusion

SmartDrain integrates IoT-based drainage monitoring, machine learning, backend data processing, automated prototype control, and 3D visualization into a unified system. By combining real-time sensor readings with AI-assisted classification and a digital twin, the project aims to improve awareness of drainage conditions and support more timely maintenance decisions.

**SmartDrain — Intelligent Monitoring for Safer, Smarter Drainage Systems.**
