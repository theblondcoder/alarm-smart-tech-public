require("dotenv").config();

const express = require("express");

const app = express();

app.disable("x-powered-by");

const PORT = process.env.PORT || 5000;

const API_KEY = process.env.ALARM_API_KEY;

if (!API_KEY) {
  console.error("ERROR: ALARM_API_KEY is not defined");
  process.exit(1);
}

// --------------------
// MIDDLEWARE
// --------------------

app.use(express.json());

app.use(express.static("public"));

// --------------------
// LAST RECEIVED DATA
// --------------------

let latestData = {
  system: "UNKNOWN",
  state: "UNKNOWN",
  temperature: null,
  humidity: null,
  smoke: null,
  flame: null,
  lastUpdate: null
};


// --------------------
// HOME
// --------------------




// --------------------
// RECEIVE ESP32 STATUS
// --------------------

app.post("/api/status", (req, res) => {

  // --------------------
  // CHECK API KEY
  // --------------------

  const receivedKey = req.headers["x-api-key"];

  if (receivedKey !== API_KEY) {
    return res.status(401).json({
      error: "Unauthorized"
    });
  }


  // --------------------
  // CHECK JSON BODY
  // --------------------

  const data = req.body;

  if (!data) {
    return res.status(400).json({
      error: "Invalid or missing JSON body"
    });
  }


  // --------------------
  // VALIDATE SYSTEM / STATE
  // --------------------

  const validSystems = [
    "RUNNING",
    "OFF"
  ];

  const validStates = [
    "NORMAL",
    "WARNING",
    "CRITICAL",
    "OFF"
  ];


  if (
    typeof data.system !== "string" ||
    !validSystems.includes(data.system)
  ) {
    return res.status(400).json({
      error: "Invalid system value"
    });
  }


  if (
    typeof data.state !== "string" ||
    !validStates.includes(data.state)
  ) {
    return res.status(400).json({
      error: "Invalid state value"
    });
  }


  // --------------------
  // SYSTEM OFF
  // --------------------

  if (data.system === "OFF") {

    latestData.system = "OFF";
    latestData.state = "OFF";
    latestData.lastUpdate = new Date().toISOString();

    console.log("System OFF received");

    return res.status(200).json({
      message: "OFF status received"
    });
  }


  // --------------------
  // VALIDATE SENSOR TYPES
  // --------------------

  if (
    typeof data.temperature !== "number" ||
    typeof data.humidity !== "number" ||
    typeof data.smoke !== "number" ||
    typeof data.flame !== "number"
  ) {
    return res.status(400).json({
      error: "Invalid sensor data types"
    });
  }


  // --------------------
  // VALIDATE SENSOR RANGES
  // --------------------

  if (
    data.temperature < -40 ||
    data.temperature > 100 ||
    data.humidity < 0 ||
    data.humidity > 100 ||
    data.smoke < 0 ||
    data.smoke > 4095 ||
    data.flame < 0 ||
    data.flame > 4095
  ) {
    return res.status(400).json({
      error: "Sensor value out of range"
    });
  }


  // --------------------
  // SAVE RUNNING DATA
  // --------------------

  latestData = {
    system: data.system,
    state: data.state,
    temperature: data.temperature,
    humidity: data.humidity,
    smoke: data.smoke,
    flame: data.flame,
    lastUpdate: new Date().toISOString()
  };


  console.log("New alarm data received:");
  console.log(latestData);


  return res.status(200).json({
    message: "Status received"
  });

});


// --------------------
// GET CURRENT STATUS
// --------------------

app.get("/api/status", (req, res) => {

  res.json(latestData);

});


// --------------------
// Error Handling
// --------------------
app.use((err, req, res, next) => {

  console.error("Internal server error:");
  console.error(err);

  res.status(500).json({
    error: "Internal server error"
  });

});

// --------------------
// START SERVER
// --------------------

app.listen(PORT, "0.0.0.0", () => {
  console.log(`Alarm server running on port ${PORT}`);
});
