#pragma once

namespace auton {
  namespace selection {
    enum class Positons { r1,
                          r2,
                          r3,
                          l1,
                          l2,
                          l3,
                          r4,
                          NONE };
    enum class Shoots { FAR,
                        MID,
                        NONE };
    enum class Flags { BOTH,
                       TOP,
                       MID,
                       HOLD,
                       NONE };
    enum class Options { PARK,
                         NPARK,
                         NONE };

    void screenInit();
    void execute();
  } // namespace selection
} // namespace auton
