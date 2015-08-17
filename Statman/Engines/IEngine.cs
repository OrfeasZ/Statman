namespace Statman.Engines
{
    interface IEngine
    {
        bool Active { get; }

        void Update();
    }
}
