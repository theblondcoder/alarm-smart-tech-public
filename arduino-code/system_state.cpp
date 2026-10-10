#include "system_state.h"


// --------------------
// DETERMINE STATE
// --------------------

SystemState determineState(SensorData data) {

  // CRITICAL if any parameter is clearly dangerous

  if (
    data.temperature >= TEMP_CRITICAL || data.smokeValue >= SMOKE_CRITICAL || data.flameValue < FLAME_CRITICAL
  ) {

    return CRITICAL;

  }


  // WARNING if any parameter is moderately elevated

  if ( data.temperature >= TEMP_WARNING || data.smokeValue >= SMOKE_WARNING || data.flameValue < FLAME_WARNING
  ) {

    return WARNING;

  }


  return NORMAL;
}