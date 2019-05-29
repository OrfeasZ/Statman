using System;

namespace Statman.Engines.HM5.CustomTracking
{
    class MurderedBodyValue
    {
        public DeadBodyData DeadBody { get; set; }
        public bool IsWitnessTarget { get; set; }
        public Guid Witness { get; set; }
    }
}
