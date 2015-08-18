using System;
using System.Threading;
using System.Threading.Tasks;

namespace Statman.Network.Threading
{
    class Worker
    {
        private readonly TaskScheduler m_CallbackThread;

        private static TaskScheduler CurrentTaskScheduler
        {
            get
            {
                return (SynchronizationContext.Current != null
                    ? TaskScheduler.FromCurrentSynchronizationContext()
                    : TaskScheduler.Default);
            }
        }

        public event WorkerSucceededEventHandler Succeeded;
        public event WorkerExceptionEventHandler Error;

        public Worker() : 
            this(CurrentTaskScheduler)
        {
        }

        public Worker(TaskScheduler p_CallbackThread)
        {
            m_CallbackThread = p_CallbackThread;
        }

        public void DoWork(Action p_Action)
        {
            new Task(DoWorkImpl, p_Action, CancellationToken.None, TaskCreationOptions.LongRunning).Start();
        }

        private void DoWorkImpl(object p_Action)
        {
            var s_Action = (Action) p_Action;

            try
            {
                s_Action();
                Callback(Succeed);
            }
            catch (Exception s_Exception)
            {
                Callback(() => Fail(s_Exception));
            }
        }

        private void Succeed()
        {
            if (Succeeded != null)
                Succeeded();
        }

        private void Fail(Exception p_Exception)
        {
            if (Error != null)
                Error(p_Exception);
        }

        private void Callback(Action p_Action)
        {
            Task.Factory.StartNew(p_Action, CancellationToken.None, TaskCreationOptions.None, m_CallbackThread);
        }
    }

    internal delegate void WorkerSucceededEventHandler();
    internal delegate void WorkerExceptionEventHandler(Exception p_Exception);
}