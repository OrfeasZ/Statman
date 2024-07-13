using System;
using Newtonsoft.Json;

namespace Statman.Engines.HM5.CustomTracking
{
    class SetPieceValue
    {
        [JsonProperty("Item_triggered_metricvalue")]
        public string ItemTriggered { get; set; }

        public string Position { get; set; }

        public Guid RepositoryId { get; set; }

        [JsonProperty("name_metricvalue")]
        public string Name { get; set; }

        [JsonProperty("setpieceHelper_metricvalue")]
        public string SetPieceHelper { get; set; }

        [JsonProperty("setpieceType_metricvalue")]
        public string SetPieceType { get; set; }

        [JsonProperty("toolUsed_metricvalue")]
        public string ToolUsed { get; set; }
    }
}
