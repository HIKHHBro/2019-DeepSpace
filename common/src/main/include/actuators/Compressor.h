#pragma once

#include <frc/Compressor.h>

#include "actuators/BinaryActuator.h"

namespace curtinfrc {
  namespace actuators {
    class Compressor : public BinaryActuator, protected frc::Compressor {
      public:
      Compressor(BinaryActuatorState initialState = actuators::kReverse) : frc::Compressor(), BinaryActuator(initialState) {};
      Compressor(int pcmID, BinaryActuatorState initialState = actuators::kReverse) : frc::Compressor(pcmID), BinaryActuator(initialState) {};

      virtual void Update(double dt) override;
      virtual void Stop() final {};
      virtual bool IsDone() override;
    };
  } // ns actuators
} // ns curtinfrc

