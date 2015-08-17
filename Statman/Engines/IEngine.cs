using System;

namespace Statman.Engines
{
    interface IEngine : IDisposable
    {
        bool Active { get; }
        string Name { get; }

        void Update();
        void OnMessage(string p_Type, string p_Data);
    }
}
