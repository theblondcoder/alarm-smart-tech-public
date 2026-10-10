let previousState = null;

let previousValues = {
  temperature: null,
  humidity: null,
  smoke: null,
  flame: null
};


async function updateDashboard() {

  try {

    const response =
      await fetch("/api/status");

    if (!response.ok) {
      throw new Error(
        "API request failed"
      );
    }


    const data =
      await response.json();


    updateConnection(data);

    updateSystem(data.system);

    updateState(data.state);

    updateSensorValue(
      "temperature",
      data.temperature
    );

    updateSensorValue(
      "humidity",
      data.humidity
    );

    updateSensorValue(
      "smoke",
      data.smoke
    );

    updateSensorValue(
      "flame",
      data.flame
    );

    updateLastUpdate(
      data.lastUpdate
    );

  }
  catch (error) {

    console.error(error);

    setConnectionStatus(
      "SERVER ERROR",
      false
    );

  }
}


// --------------------
// CONNECTION
// --------------------

function updateConnection(data) {

  if (!data.lastUpdate) {

    setConnectionStatus(
      "WAITING",
      false
    );

    return;
  }


  const lastUpdate =
    new Date(
      data.lastUpdate
    );

  const now =
    new Date();


  const secondsSinceUpdate =
    (now - lastUpdate) / 1000;


  if (secondsSinceUpdate <= 20) {

    setConnectionStatus(
      "CONNECTED",
      true
    );

  }
  else {

    setConnectionStatus(
      "CONNECTION LOST",
      false
    );

  }
}


function setConnectionStatus(
  text,
  connected
) {

  const badge =
    document.getElementById(
      "connection-badge"
    );

  const label =
    document.getElementById(
      "connection-status"
    );


  label.textContent =
    text;


  badge.classList.remove(
    "connected",
    "disconnected"
  );


  badge.classList.add(
    connected
      ? "connected"
      : "disconnected"
  );
}


// --------------------
// SYSTEM
// --------------------

function updateSystem(system) {

  const element =
    document.getElementById(
      "system-status"
    );


  element.textContent =
    system ?? "UNKNOWN";
}


// --------------------
// STATE
// --------------------

function updateState(state) {

  const stateElement =
    document.getElementById(
      "alarm-state"
    );

  const card =
    document.getElementById(
      "state-card"
    );

  const description =
    document.getElementById(
      "state-description"
    );


  const safeState =
    state ?? "UNKNOWN";


  stateElement.textContent =
    safeState;


  card.classList.remove(
    "state-normal",
    "state-warning",
    "state-critical",
    "state-off",
    "state-unknown"
  );


  switch (safeState) {

    case "NORMAL":

      card.classList.add(
        "state-normal"
      );

      description.textContent =
        "No dangerous conditions detected";

      break;


    case "WARNING":

      card.classList.add(
        "state-warning"
      );

      description.textContent =
        "Elevated sensor levels detected";

      break;


    case "CRITICAL":

      card.classList.add(
        "state-critical"
      );

      description.textContent =
        "Critical condition detected";

      break;


    case "OFF":

      card.classList.add(
        "state-off"
      );

      description.textContent =
        "Sensors are currently disabled";

      break;


    default:

      card.classList.add(
        "state-unknown"
      );

      description.textContent =
        "Waiting for system state";

      break;
  }


  if (
    previousState !== null &&
    previousState !== safeState
  ) {

    showStateChange(
      safeState
    );
  }


  previousState =
    safeState;
}


// --------------------
// STATE CHANGE ANIMATION
// --------------------

function showStateChange(state) {

  const overlay =
    document.getElementById(
      "state-overlay"
    );

  const content =
    document.getElementById(
      "overlay-content"
    );

  const title =
    document.getElementById(
      "overlay-title"
    );

  const text =
    document.getElementById(
      "overlay-text"
    );

  const icon =
    document.getElementById(
      "overlay-icon"
    );


  content.classList.remove(
    "overlay-normal",
    "overlay-warning",
    "overlay-critical",
    "overlay-off"
  );


  switch (state) {

    case "NORMAL":

      content.classList.add(
        "overlay-normal"
      );

      icon.textContent =
        "✓";

      title.textContent =
        "System Normal";

      text.textContent =
        "The alarm returned to normal conditions.";

      break;


    case "WARNING":

      content.classList.add(
        "overlay-warning"
      );

      icon.textContent =
        "!";

      title.textContent =
        "Warning";

      text.textContent =
        "One or more sensor values are elevated.";

      break;


    case "CRITICAL":

      content.classList.add(
        "overlay-critical"
      );

      icon.textContent =
        "!";

      title.textContent =
        "Critical Alert";

      text.textContent =
        "A critical alarm condition has been detected.";

      break;


    case "OFF":

      content.classList.add(
        "overlay-off"
      );

      icon.textContent =
        "○";

      title.textContent =
        "System Off";

      text.textContent =
        "Sensor monitoring has been disabled.";

      break;
  }


  overlay.classList.add(
    "visible"
  );


  clearTimeout(
    window.stateOverlayTimer
  );


  window.stateOverlayTimer =
    setTimeout(() => {

      overlay.classList.remove(
        "visible"
      );

    }, 3000);
}


// --------------------
// SENSOR VALUES
// --------------------

function updateSensorValue(
  id,
  value
) {

  const element =
    document.getElementById(id);


  const displayValue =
    value ?? "--";


  if (
    previousValues[id] !== null &&
    previousValues[id] !== value
  ) {

    element.classList.remove(
      "value-changed"
    );


    void element.offsetWidth;


    element.classList.add(
      "value-changed"
    );
  }


  element.textContent =
    displayValue;


  previousValues[id] =
    value;
}


// --------------------
// LAST UPDATE
// --------------------

function updateLastUpdate(
  lastUpdate
) {

  const element =
    document.getElementById(
      "last-update"
    );


  if (!lastUpdate) {

    element.textContent =
      "--";

    return;
  }


  const date =
    new Date(
      lastUpdate
    );


  element.textContent =
    date.toLocaleString();
}


// --------------------
// START
// --------------------

updateDashboard();


setInterval(
  updateDashboard,
  1000
);