# =====================================================
# Smart Drainage System
# Alert Logic
# =====================================================


def get_alert(status: str):

    if status == "Normal":

        return {
            "severity": "NORMAL",
            "alert": False,
            "message": "Drainage condition is normal."
        }

    elif status == "Partial Blockage":

        return {
            "severity": "WARNING",
            "alert": True,
            "message": "Partial blockage detected. Inspection recommended."
        }

    elif status == "Full Blockage":

        return {
            "severity": "CRITICAL",
            "alert": True,
            "message": "Full blockage detected. Immediate attention required."
        }

    elif status == "Flood Risk":

        return {
            "severity": "CRITICAL",
            "alert": True,
            "message": "Flood risk detected. Immediate monitoring required."
        }

    else:

        return {
            "severity": "UNKNOWN",
            "alert": True,
            "message": "Unknown drainage condition."
        }