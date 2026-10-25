# SmartDrain: AI-Based Smart Drainage Detection and Automatic Safety System for Urban Flooding

**An IoT, Machine Learning, and Digital Twin–Based Smart Drainage Monitoring System**

## 🌊 Project Overview

SmartDrain is an intelligent drainage monitoring and safety system designed to identify abnormal drainage conditions, detect potential blockages, support automated control, and improve drainage-system visibility.

The system combines IoT sensors, an ESP32 microcontroller, an XGBoost machine learning model, a FastAPI backend, and a Unity 3D digital twin. A modular biofilter is also proposed to help capture selected particles and support wastewater treatment.

SmartDrain aims to support early identification of drainage problems, reduce dependence on manual inspections, and provide useful information for maintenance and flood-risk management.

> **Project status:** This README describes the complete project concept and intended architecture. Individual features should be marked as implemented only after they have been integrated and tested.

---

## 🚨 Problem Statement

Conventional drainage systems face several challenges:

- Blockages caused by solid waste, leaves, and sediment.
- Water accumulation and overflow due to restricted drainage.
- Limited real-time visibility into underground drainage conditions.
- Time-consuming manual inspection and maintenance.
- Difficulty identifying abnormal flow and trapped-air conditions.
- Limited integration between physical drainage infrastructure and digital monitoring tools.

SmartDrain addresses these challenges through sensor-based monitoring, machine learning–assisted classification, automated control, and 3D visualization.

## 💡 Proposed Solution

SmartDrain uses sensor readings to monitor drainage conditions and identify abnormal patterns.

The ESP32 collects data from the connected sensors and transmits it to a FastAPI backend. The backend validates the incoming data, stores readings, and uses a trained XGBoost model to classify drainage conditions when the appropriate model and input features are available.

A monitoring dashboard and Unity 3D digital twin can present sensor readings, predicted conditions, and potential problem locations. A servo-operated Smart Auto-Vent and pump-control mechanism can support predefined safety actions.

A separate biofilter module is proposed for selected wastewater filtration and biological treatment applications.

## 🎯 Project Objectives

1. Monitor drainage conditions using IoT sensors.
2. Identify abnormal water-level and flow patterns.
3. Develop machine learning–based drainage-condition classification.
4. Enable communication between the ESP32 and FastAPI backend.
5. Provide a dashboard for readings, predictions, and alerts.
6. Visualize the drainage network through a Unity 3D digital twin.
7. Develop a servo-controlled Smart Auto-Vent mechanism for managing trapped air under suitable operating conditions.
8. Explore a modular biofilter for selected wastewater treatment applications.
9. Support safer maintenance decisions through early warnings and system monitoring.

---

## 🏗️ System Architecture

```text
        PHYSICAL DRAINAGE PROTOTYPE
                   |
       +-----------+-----------+
       |           |           |
   Flow Sensor  Water-Level  Acoustic
                  Sensor      Sensor
       |           |           |
       +-----------+-----------+
                   |
           Pressure Sensor
                   |
                  ESP32
                   |
             Wi-Fi / HTTP
                   |
            FastAPI Backend
                   |
       +-----------+-----------+
       |           |           |
   XGBoost      SQLite      Validation
   Prediction   Database    and Alerts
       |           |           |
       +-----------+-----------+
                   |
          Monitoring Dashboard
                   |
          Unity 3D Digital Twin
                   |
          Control Command Layer
                   |
                  ESP32
                   |
        +----------+----------+
        |                     |
    Servo Motor           Water Pump
        |                     |
    Smart Auto-Vent      Water Circulation

  Separate module: Biofilter chamber
  for selected particle capture and
  potential biological wastewater treatment.
```

The architecture represents the intended system flow. The sensor interfaces, database, prediction pipeline, dashboard, Unity integration, and actuator-control path must be implemented and tested before they can be considered fully operational.

---

## 🔌 Hardware Components

| Component | Purpose |
|---|---|
| ESP32 DevKit V1 | Reads sensor signals, communicates with the backend, and controls supported actuators |
| Flow sensor | Measures water flow through its installation point |
| Water-level sensor | Measures water height in the drainage chamber or tank |
| Acoustic sensor | Captures sound or vibration patterns associated with drainage activity |
| BMP280 pressure sensor | Measures atmospheric pressure |
| Servo motor | Operates the Smart Auto-Vent mechanism |
| DC water pump | Circulates water through the physical prototype |
| LM2596 buck converter | Steps down the supply voltage for compatible components |
| PVC/uPVC pipes and fittings | Form the main drainage line and branch network |
| Reservoir or water tank | Supports controlled water circulation |
| Biofilter chamber | Houses the selected filter media |

**Hardware note:** Confirm the exact servo model and acoustic sensor model in your final build. The BMP280 measures barometric pressure, not direct water pressure. The flow sensor measures flow only at its installed location.

### Sensor Monitoring

**1. Flow Sensor**

Measures flow through the pipe section where it is installed. Unexpected flow reductions may indicate an obstruction, a pump problem, or another hydraulic change.

**2. Water-Level Sensor**

Measures the water height inside the monitored chamber or tank. Rising levels can indicate restricted flow or insufficient drainage capacity.

**3. Acoustic Sensor**

Captures sound and vibration patterns. Unusual patterns may help identify abnormal flow, turbulence, or mechanical activity when validated against test conditions.

**4. BMP280 Pressure Sensor**

Measures atmospheric pressure. It can provide environmental measurements, but it cannot determine toxic-gas concentration or directly measure the pressure of the water in the pipe.

---

## 🤖 Machine Learning: XGBoost

SmartDrain uses XGBoost as the proposed machine learning model for drainage-condition classification.

The model can learn patterns from labelled sensor datasets and classify drainage conditions when the training data and input features support the intended classes.

### Proposed classification classes

- **Normal:** Readings are within the defined normal operating range.
- **Partial Blockage:** Sensor patterns are consistent with a partial obstruction.
- **Critical Blockage:** Sensor patterns indicate a severe obstruction or an abnormal drainage condition.

The final class names must match the labels used to train the model.

### Machine Learning Workflow

1. Collect sensor readings under controlled operating conditions.
2. Label the observations using known test conditions.
3. Clean and prepare the dataset.
4. Select the sensor features used by the model.
5. Split the dataset into training and testing sets.
6. Train the XGBoost classifier.
7. Evaluate the model using appropriate classification metrics.
8. Integrate the trained model into the FastAPI backend.
9. Compare predictions with observed test conditions and improve the model.

**Important:** The model should not be described as detecting toxic gases or guaranteeing flood prediction unless it has suitable labelled data and has been validated for those specific tasks. Drainage blockage classification and city-scale flood prediction are different problems.

---

## 🌬️ Smart Auto-Vent and Servo Motor

The Smart Auto-Vent is a proposed mechanical feature designed to manage trapped air within the drainage prototype.

A servo motor positions the vent mechanism according to configured control rules. The system may use validated sensor conditions to trigger an inspection warning or a controlled vent operation.

### Intended functionality

- Identify selected abnormal drainage patterns.
- Apply configured control conditions.
- Operate the servo mechanism when permitted.
- Provide status information to the monitoring system.
- Support manual override and safe shutdown.

### Safety considerations

- The vent must be mechanically secured.
- The servo must use a suitable power supply.
- The vent must not create an unsafe release path.
- Control logic should include safe operating limits.
- A vent operation must not be treated as proof that a blockage or hazardous gas has been removed.

The Auto-Vent is not a substitute for a gas detector, a blockage-removal mechanism, or professional drainage maintenance.

---

## 🧪 Biofilter Module

The biofilter is a separate module intended to support selected wastewater filtration and treatment processes.

Wastewater passes through a chamber containing selected filter media. A preliminary screen can capture larger debris, while suitable media can retain some suspended particles and provide a surface for beneficial microorganisms.

### Proposed biofilter components

- Removable coarse screen.
- Filter-media chamber.
- Suitable gravel or support media, where appropriate.
- Biological carrier media.
- Perforated media-support plate.
- Inlet and outlet connections.
- Removable cartridge for cleaning and maintenance.

### Intended benefits

- Capture selected solid particles.
- Provide a modular treatment stage.
- Support biological treatment under appropriate conditions.
- Enable controlled filtration experiments.
- Complement the drainage-monitoring prototype.

### Biofilter limitations

A basic biofilter does not automatically remove all pollutants, pathogens, dissolved chemicals, or toxic gases. Treatment performance depends on the media, flow rate, contact time, oxygen availability, and wastewater characteristics.

Performance should be evaluated using suitable water-quality measurements. Visible particle removal alone does not prove biological treatment effectiveness.

---

## ☣️ Indirect Drainage-Hazard Monitoring

SmartDrain currently does not include a dedicated gas sensor. Therefore, the available sensors cannot directly confirm the presence or concentration of hydrogen sulfide (H₂S), methane, or another toxic or combustible gas.

The flow and acoustic sensors can help identify abnormal drainage conditions. Water-level readings can provide additional context, while the BMP280 provides atmospheric-pressure information.

These measurements may support a **drainage anomaly or inspection warning**, but they cannot reliably establish that toxic gas has formed or accumulated.

### Proposed warning workflow

1. Collect readings from the connected sensors.
2. Check for invalid, missing, or abnormal measurements.
3. Compare readings against validated operating conditions.
4. Flag suspicious drainage patterns.
5. Notify the operator that inspection may be required.
6. Use suitable gas-monitoring equipment to determine whether hazardous gas is present.

Direct gas detection requires an appropriate, calibrated gas sensor or gas-monitoring instrument for the target gas. The Smart Auto-Vent must not be triggered on the assumption that toxic gas has been confirmed by indirect readings.

---

## 🌐 FastAPI Backend

FastAPI is the proposed backend framework for receiving sensor data, running predictions, storing records, and providing information to the dashboard and Unity application.

### Intended backend responsibilities

- Receive sensor readings from the ESP32.
- Validate incoming JSON payloads.
- Process supported sensor features.
- Load and invoke the trained XGBoost model.
- Store readings and prediction records in SQLite.
- Generate alerts based on configured conditions.
- Provide API endpoints for the dashboard and digital twin.
- Receive permitted actuator commands and coordinate their delivery to the ESP32.

### Suggested API structure

| Endpoint | Purpose |
|---|---|
| `POST /api/sensor/data` | Receive sensor readings |
| `POST /api/prediction/` | Request a drainage-condition prediction |
| `GET /api/system/latest` | Retrieve the latest system readings |
| `GET /api/system/history` | Retrieve historical readings |
| `GET /api/alerts/` | Retrieve stored alerts |
| `GET /api/device/` | Retrieve registered device information |
| `POST /api/device/command` | Submit an actuator command, if implemented |

These are suggested endpoints. The actual routes depend on the backend implementation.

### Suggested development environment

- Python
- FastAPI
- Uvicorn
- Pydantic
- SQLAlchemy
- SQLite
- XGBoost
- Scikit-learn, where required by the model pipeline

---

## 📊 Monitoring Dashboard

The proposed dashboard provides a central view of drainage conditions and system activity.

### Suggested dashboard features

- Current sensor readings.
- Latest drainage-condition prediction.
- Flow and water-level trends.
- Active and historical alerts.
- Device communication status.
- Auto-Vent and pump status.
- Historical monitoring records.
- Filter-maintenance notifications, where supported.

The dashboard should distinguish measured readings from model predictions and configured warnings.

---

## 🌍 Unity 3D Digital Twin

Unity 3D is intended to provide a visual representation of the SmartDrain physical prototype.

### Proposed visualization features

- Main drainage pipe and branch network.
- Drainage chamber and water reservoir.
- Sensor locations.
- Water-flow animation.
- Visual indicators for normal and abnormal conditions.
- Smart Auto-Vent status.
- Biofilter chamber.
- Live readings and model predictions, when connected to the backend.

### Integration workflow

1. Build the drainage scene in Unity.
2. Configure the FastAPI backend to expose the required data.
3. Retrieve readings using HTTP and JSON.
4. Map the incoming data to Unity scene objects.
5. Update visual indicators based on validated readings.
6. Synchronize actuator status where communication is implemented.

Unity should communicate with the backend rather than connecting directly to the physical sensors.

---

## 🔄 System Workflow

1. **Sense:** Sensors collect drainage measurements.
2. **Process:** The ESP32 reads and packages supported sensor data.
3. **Transmit:** The ESP32 sends the data to the backend.
4. **Validate:** FastAPI checks incoming data.
5. **Predict:** XGBoost classifies drainage conditions using its trained features.
6. **Store:** The backend records measurements and predictions.
7. **Alert:** The system flags configured abnormal conditions.
8. **Visualize:** The dashboard and Unity digital twin present the available information.
9. **Control:** Supported commands are delivered to the ESP32 for permitted actuator operations.
10. **Evaluate:** Testing results are used to improve the hardware, model, and control rules.

---

## 🛠️ Installation and Setup

The following steps describe a proposed Python backend setup. They assume the backend application has been implemented and the required files are present.

### Prerequisites

- Python 3.10 or another version supported by the project's dependencies.
- Visual Studio Code or another Python IDE.
- Git.
- ESP32 development environment.
- Unity, if the digital twin is being developed.
- Trained XGBoost model and its required preprocessing files, if model inference is enabled.

### Step 1: Clone the repository

Replace the placeholder URL with your actual GitHub repository URL.

```bash
git clone <YOUR_GITHUB_REPOSITORY_URL>
cd <YOUR_REPOSITORY_FOLDER>
```

### Step 2: Create a virtual environment

**Windows PowerShell**

```powershell
python -m venv .venv
.\.venv\Scripts\Activate.ps1
```

If PowerShell blocks activation, use the appropriate environment-activation method for your system or activate the environment from your IDE.

### Step 3: Install dependencies

If the repository contains `requirements.txt`:

```bash
pip install -r requirements.txt
```

If the backend dependencies have not yet been defined, create a requirements file that matches the actual code and model dependencies. Do not install arbitrary packages without checking compatibility.

### Step 4: Configure environment variables

If your application uses environment variables, create a local `.env` file containing the required settings.

Example configuration:

```env
DATABASE_URL=sqlite:///./data/smartdrain.db
```

This is an example only. Use the exact variable names expected by your implementation. Do not commit API keys, credentials, or other secrets.

### Step 5: Start the backend

For an application whose FastAPI instance is located at `app.main:app`, run:

```bash
uvicorn app.main:app --reload
```

If your entry point differs, adjust the module path accordingly.

### Step 6: Open the API documentation

When the server is running locally, open:

```text
http://127.0.0.1:8000/docs
```

Use the interactive API documentation to inspect and test the endpoints implemented in your backend.

### Step 7: Test the system

- Send a valid sample sensor payload.
- Confirm that the backend validates the request.
- Check whether readings are stored successfully.
- Test prediction endpoints with valid model features.
- Verify the alert rules.
- Connect the ESP32 after the API has been tested independently.
- Connect the dashboard and Unity visualization when their integrations are ready.

---

## 🧪 Testing and Validation

The project should be evaluated in controlled conditions before claims about accuracy or safety are made.

### Hardware tests

- Verify individual sensor readings.
- Check wiring, voltage compatibility, and power stability.
- Test the servo mechanism.
- Verify pump operation and water circulation.
- Inspect pipe joints for leakage.
- Test the biofilter with a controlled test medium.

### Software tests

- Validate incoming sensor payloads.
- Check API error handling.
- Confirm database storage.
- Verify that model features match the training pipeline.
- Test invalid and missing sensor values.
- Check communication interruptions.
- Confirm that actuator commands obey safety rules.

### Machine learning evaluation

Evaluate the model using appropriate metrics, including:

- Accuracy.
- Precision.
- Recall.
- F1-score.
- Confusion matrix.

Use a held-out test dataset that is separate from the training data. Report measured results rather than assumed or estimated values.

### Biofilter evaluation

Compare suitable inlet and outlet water-quality measurements under controlled conditions. Track flow reduction, particle capture, and maintenance requirements.

### Safety evaluation

Test the pump, servo, enclosure, and control logic under safe, controlled operating conditions. Never use the absence of a sensor warning as proof that a drainage environment is safe.

---

## ⚠️ Safety and Limitations

- Protect electronics from water and accidental contact.
- Use suitable fuses, power regulation, and actuator driver circuits.
- Do not power high-current actuators directly from an ESP32 GPIO.
- Provide manual override and emergency shutdown where applicable.
- Avoid unsafe pressure buildup in the drainage prototype.
- Do not enter drains or enclosed spaces based on SmartDrain readings.
- Flow, water-level, acoustic, and atmospheric-pressure sensors cannot confirm toxic-gas presence.
- Use suitable gas-monitoring equipment and qualified procedures where hazardous gases may be present.
- A biofilter is not a substitute for complete wastewater treatment.
- Do not claim flood-prediction accuracy, toxic-gas detection, or water-treatment performance without appropriate validation.

---

## 🚀 Future Enhancements

- Add a suitable gas sensor for direct monitoring of selected hazardous gases.
- Improve model performance using more diverse, labelled drainage-condition data.
- Add a validated flood-risk forecasting module using appropriate rainfall, water-level, and drainage data.
- Integrate real-time dashboard notifications.
- Improve device-health monitoring and communication recovery.
- Add filter-maintenance indicators.
- Evaluate biofilter performance using appropriate water-quality measurements.
- Improve Unity digital-twin synchronization.
- Add secure device authentication and access control.
- Validate the system through longer-duration prototype testing.

---

## 🌱 Expected Impact

SmartDrain aims to support:

- Earlier identification of abnormal drainage conditions.
- More informed maintenance planning.
- Better visibility into drainage-system behaviour.
- Integration of physical monitoring with AI-assisted analysis.
- Visualization of drainage infrastructure through a digital twin.
- Safer and more structured prototype testing.

These are intended benefits. Actual improvements must be demonstrated through measured prototype results.

---

## 📚 References and Documentation

- **ESP32 — Espressif Systems:** https://documentation.espressif.com/esp32_datasheet_en.html
- **BMP280 — Bosch Sensortec:** https://www.bosch-sensortec.com/
- **XGBoost Documentation:** https://xgboost.readthedocs.io/
- **FastAPI Documentation:** https://fastapi.tiangolo.com/
- **Python Documentation:** https://docs.python.org/3/
- **Unity Documentation:** https://docs.unity.com/
- **Scikit-learn Documentation:** https://scikit-learn.org/stable/

Consult the exact manufacturer datasheets for the ultrasonic, flow, acoustic, servo, and pump models used in the final prototype.

---

## 👥 Contributors

Add your project team members, roles, and GitHub profile links here.

- **Project Lead:** [Name]
- **Hardware and IoT:** [Name]
- **Machine Learning:** [Name]
- **Backend Development:** [Name]
- **Unity Digital Twin:** [Name]

Replace the placeholders with the actual contributor details.

## 📄 License

Choose an appropriate open-source license before publishing the repository. If you intend to use the MIT License, add a `LICENSE` file containing the full license text and update this section accordingly.

---

## ⭐ Conclusion

SmartDrain combines IoT sensing, machine learning, backend services, automated mechanisms, and 3D visualization to explore a smarter approach to drainage monitoring and maintenance.

By integrating sensor-based condition monitoring with AI-assisted classification and a digital twin, the project aims to provide a practical foundation for developing more responsive drainage-management systems.

**SmartDrain — Monitor smarter. Detect earlier. Manage drainage more safely.**
