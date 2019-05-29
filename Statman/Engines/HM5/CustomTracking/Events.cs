using System;

namespace Statman.Engines.HM5.CustomTracking
{
    [AttributeUsage(AttributeTargets.Field)]
    class RatingEventAttribute : Attribute
    {
        public int Points { get; set; }

        public string Description { get; set; }

        public RatingEventAttribute(int p_Points, string p_Description)
        {
            Points = p_Points;
            Description = p_Description;
        }
    }

    public enum EventType
    {
        [RatingEvent(-6, "Recordings Destroyed")]
        RecordingsDestroyed,
        
        [RatingEvent(-2, "Witness Killed (Accident)")]
        WitnessAccident,
        
        [RatingEvent(-1, "Witness Killed")]
        WitnessMurder,
        
        [RatingEvent(1, "Character Pacified")]
        Pacification,
        
        [RatingEvent(2, "Caught Trespassing")]
        CaughtTrespassing,
        
        [RatingEvent(3, "Gunshot Heard")]
        GunshotHeard,
        
        [RatingEvent(3, "Bullet Impact Noticed")]
        BulletImpactNoticed,
        
        [RatingEvent(4, "Unconscious Body Found")]
        UnconsciousBodyFound,
        
        [RatingEvent(6, "Dead Body Found")]
        DeadBodyFound,
        
        [RatingEvent(5, "Alarm Triggered")]
        AlarmTriggered,
        
        [RatingEvent(5, "Guards Alerted")]
        GuardsAlerted,
        
        [RatingEvent(6, "Guard Killed")]
        GuardKilled,

        [RatingEvent(8, "Civilian Killed")]
        CivilianKilled,
        
        [RatingEvent(6, "Caught on Camera")]
        CaughtOnCamera,
        
        [RatingEvent(7, "Caught Commiting Crime")]
        CommitingCrime,
    }
}
