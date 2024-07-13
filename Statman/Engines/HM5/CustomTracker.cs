using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using Newtonsoft.Json;
using Statman.Engines.HM5.CustomTracking;

namespace Statman.Engines.HM5
{
    public class CustomTracker
    {
        private HM5Engine m_Engine;
        private readonly Dictionary<string, Action<GameEvent>> m_EventHandlers = new Dictionary<string, Action<GameEvent>>();

        private long m_CurrentNotoriety;
        private HashSet<Guid> m_Witnesses = new HashSet<Guid>();
        private HashSet<Guid> m_PacifiedBodies = new HashSet<Guid>();
        private HashSet<Guid> m_DeadBodies = new HashSet<Guid>();
        private List<EventType> m_Events = new List<EventType>();
        private bool m_AlarmTriggered;
        private Queue<Guid> m_PendingBodies = new Queue<Guid>();

        public CustomTracker(HM5Engine p_Engine)
        {
            m_Engine = p_Engine;

            // Register our event handlers.
            RegisterEventHandler("ContractStart", OnContractStart);
            RegisterEventHandler("ContractLoad", OnContractStart);
            RegisterEventHandler("47_FoundTrespassing", OnFoundTrespassing);
            RegisterEventHandler("Spotted", OnSpotted);
            RegisterEventHandler("AmbientChanged", OnAmbientChange);
            RegisterEventHandler("Pacify", OnPacify);
            RegisterEventHandler("BodyFound", OnBodyFound);
            RegisterEventHandler("DisguiseBlown", OnDisguiseBlown);
            RegisterEventHandler("Witnesses", OnWitnesses);
            RegisterEventHandler("Kill", OnKill);
            RegisterEventHandler("BrokenDisguiseCleared", OnBrokenDisguiseCleared);
            RegisterEventHandler("Unnoticed_Kill", OnUnnoticedKill);
            RegisterEventHandler("setpieces", OnSetPieces);
            RegisterEventHandler("SecuritySystemRecorder", OnSecuritySystemRecorder);
        }

        private void RegisterEventHandler(string p_Event, Action<GameEvent> p_Handler)
        {
            m_EventHandlers.Add(p_Event.ToLowerInvariant(), p_Handler);
        }

        public void OnGameEvent(string p_EventData)
        {
            // Parse the event.
            var s_Event = JsonConvert.DeserializeObject<GameEvent>(p_EventData);

            Debug.WriteLine($"Got event: {s_Event.Name}");
            
            // We only care about gameclient events.
            if (s_Event.Origin != "gameclient")
                return;

            // Get the handler for this event, if one exists.
            if (!m_EventHandlers.TryGetValue(s_Event.Name.ToLowerInvariant(), out var s_Handler))
                return;

            // Call the handler!
            s_Handler(s_Event);
        }

        public void Update()
        {
            while (m_PendingBodies.Count > 0)
            {
                var s_Body = m_PendingBodies.Dequeue();

                // Trigger an event based on whether this is an unconscious or dead body.
                if (m_PacifiedBodies.Contains(s_Body))
                    OnEvent(EventType.UnconsciousBodyFound);
                else
                    OnEvent(EventType.DeadBodyFound);
            }
        }

        private void OnEvent(EventType p_Event)
        {
            // Get the attribute for this value.
            var s_Type = typeof(EventType);
            var s_Name = Enum.GetName(s_Type, p_Event);

            var s_Attribute = s_Type.GetField(s_Name)
                .GetCustomAttributes(false)
                .OfType<RatingEventAttribute>()
                .FirstOrDefault();

            if (s_Attribute == null)
                return;
            
            // Add the event to the list.
            m_Events.Add(p_Event);

            // Update the notoriety.
            m_CurrentNotoriety += s_Attribute.Points;

            if (m_CurrentNotoriety < 0)
                m_CurrentNotoriety = 0;

            // Update the UI.
            m_Engine.Control.OnRatingEvent(p_Event);
            m_Engine.Control.SetNotoriety(m_CurrentNotoriety);
        }

        private void OnContractStart(GameEvent p_Event)
        {
            // Reset everything.
            m_AlarmTriggered = false;
            m_CurrentNotoriety = 0;
            m_DeadBodies.Clear();
            m_PacifiedBodies.Clear();
            m_Witnesses.Clear();
            m_Events.Clear();
            m_PendingBodies.Clear();

            // And update the UI.
            m_Engine.Control.ResetAdvancedRating();
        }

        private void OnFoundTrespassing(GameEvent p_Event)
        {
            OnEvent(EventType.CaughtTrespassing);
        }

        private void OnSpotted(GameEvent p_Event)
        {
            // TODO: This isn't accurate.
            //OnEvent(EventType.CommitingCrime);
        }

        private void OnAmbientChange(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<AmbianceValue>();
            Debug.WriteLine($"Ambiance changed to {s_Value.AmbientValue}");

            /*
            EGT_Undefined = 0,
	        EGT_Ambient = 1,
	        EGT_Agitated = 2,
	        EGT_Searching = 3,
	        EGT_AlertedLow = 4,
	        EGT_AlertedHigh = 5,
	        EGT_Hunting = 6,
	        EGT_Arrest = 7,
	        EGT_Combat = 8,
            */

            if (s_Value.AmbientValue >= 5 && s_Value.PreviousAmbientValue < 5)
                OnEvent(EventType.GuardsAlerted);
        }

        private void OnPacify(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<KillData>();
            Debug.WriteLine($"Got pacification of actor with type {s_Value.ActorType}");

            // Trigger pacification event.
            OnEvent(EventType.Pacification);

            // Add the npc to the list of unconscious bodies.
            m_PacifiedBodies.Add(s_Value.RepositoryId);
        }

        private void OnKill(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<KillData>();
            Debug.WriteLine($"Got kill of actor with type {s_Value.ActorType}");

            /*
            eAT_Civilian = 0,
	        eAT_Guard = 1,
	        eAT_Hitman = 2,
	        eAT_Last = 3,
            */

            var s_Civilian = s_Value.ActorType == 0;

            // Trigger kill event.
            // TODO: Do we still subtract points if it's an accident?
            OnEvent(s_Civilian ? EventType.CivilianKilled : EventType.GuardKilled);

            // If this was a witness then trigger appropriate events.
            if (m_Witnesses.Contains(s_Value.RepositoryId))
                OnEvent(s_Value.Accident ? EventType.WitnessAccident : EventType.WitnessMurder);

            // Add the npc to the list of dead bodies.
            // TODO: Do we still need to add if it's an accident?
            m_DeadBodies.Add(s_Value.RepositoryId);

            // Remove from the list of witnesses.
            m_Witnesses.Remove(s_Value.RepositoryId);
        }

        private void OnBodyFound(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<BodyFoundValue>();

            // Since a body could be found before we receive the kill event, queue it for later processing.
            m_PendingBodies.Enqueue(s_Value.DeadBody.RepositoryId);
        }

        private void OnDisguiseBlown(GameEvent p_Event)
        {

        }

        private void OnWitnesses(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<List<Guid>>();

            // If there were not witnesses before then we were caught doing something illegal!
            // TODO: Maybe we need some better logic here, instead using a cooldown mechanism in combination with checking for NPCs that have never witnessed you before.
            if (m_Witnesses.Count == 0)
                OnEvent(EventType.CommitingCrime);

            foreach (var s_Witness in s_Value)
                m_Witnesses.Add(s_Witness);
        }

        private void OnBrokenDisguiseCleared(GameEvent p_Event)
        {

        }

        private void OnUnnoticedKill(GameEvent p_Event)
        {

        }

        private void OnSetPieces(GameEvent p_Event)
        {
            var s_Value = p_Event.Value.ToObject<SetPieceValue>();

            if (s_Value.Name == "FireAlarm" && !m_AlarmTriggered)
            {
                m_AlarmTriggered = true;
                OnEvent(EventType.AlarmTriggered);
            }
        }

        private void OnSecuritySystemRecorder(GameEvent p_Event)
        {

        }
    }
}
