using System;
using System.Collections.Generic;

namespace Statman.Engines.HM5.CustomTracking
{
    class KillData
    {
        public bool Accident { get; set; }
        public long ActorId { get; set; }
        public string ActorName { get; set; }
        public string ActorPosition { get; set; }
        public int ActorType { get; set; }
        public int BodyPartId { get; set; }
        public List<string> DamageEvents { get; set; }
        public int ExplosionType { get; set; }
        public bool Explosive { get; set; }
        public string HeroPosition { get; set; }
        public bool IsHeadshot { get; set; }
        public bool IsMoving { get; set; }
        public bool IsReplicated { get; set; }
        public bool IsTarget { get; set; }
        public string KillClass { get; set; }
        public int KillContext { get; set; }
        public string KillItemCategory { get; set; }
        public Guid KillItemInstanceId { get; set; }
        public Guid KillItemRepositoryId { get; set; }
        public string KillMethodBroad { get; set; }
        public string KillMethodStrict { get; set; }
        public int KillType { get; set; }
        public bool OutfitIsHitmanSuit { get; set; }
        public Guid OutfitRepositoryId { get; set; }
        public long PlayerId { get; set; }
        public Guid RepositoryId { get; set; }
        public long RoomId { get; set; }
        public bool Sniper { get; set; }
        public bool ThroughWall { get; set; }
        public double TotalDamage { get; set; }
        public bool WeaponSilenced { get; set; }
    }
}
