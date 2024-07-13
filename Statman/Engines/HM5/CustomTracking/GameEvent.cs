using System;
using Newtonsoft.Json.Linq;

namespace Statman.Engines.HM5.CustomTracking
{
    class GameEvent
    {
        public Guid ContractId { get; set; }
        public string ContractSessionId { get; set; }
        public Guid Id { get; set; }
        public string Name { get; set; }
        public string Origin { get; set; }
        public string SessionId { get; set; }
        public double Timestamp { get; set; }
        public Guid UserId { get; set; }
        public JToken Value { get; set; }
    }
}
